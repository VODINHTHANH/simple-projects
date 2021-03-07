import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class GamePanel extends JPanel implements Runnable {

	static final int GAME_WIDTH = 600;
	static final int GAME_HEIGHT = 600;
	static final int SHIP_WIDTH = 50;
	static final int SHIP_HEIGHT = 50;
	static final int BULLET_WIDTH = 10;
	static final int BULLET_HEIGHT = 25;
	static final int NEnemy_WIDTH = 25; //Normal enemy
	static final int NEnemy_HEIGHT = 25;
	public static int BOSS_WIDTH = 100;
	public static int BOSS_HEIGHT = 100;
	public static int BOSS_BULLET_WIDTH = 10;
	public static int BOSS_BULLET_HEIGHT = 10;
	static State state;

	static double timer = 0.0;
	static int timerForEnemy = 0;
	static final Dimension SCREEN_SIZE = new Dimension(GAME_WIDTH, GAME_HEIGHT);
	Thread gameThread;
	Image image;
	Graphics graphics;
	Random random;
	Ship ship;
	static ArrayList<NormalEnemy> normalEnemyList;
	static ArrayList<EnemyBullet> enemyBulletList;
	static ArrayList<Boss> bossList;
	static ArrayList<BossBullet> bossBulletList;
	MenuSystem menu;
	static BossHealthBar bossHealthBar;

	GamePanel() {
		bossList = new ArrayList<Boss>();
		bossBulletList = new ArrayList<BossBullet>();
		bossList.add(new Boss((GAME_WIDTH - BOSS_WIDTH) / 2, -BOSS_HEIGHT, BOSS_WIDTH, BOSS_HEIGHT));
		bossHealthBar = new BossHealthBar(bossList.get(0));
		menu = new MenuSystem();
		random = new Random();
		state = State.Menu;
		normalEnemyList = new ArrayList<NormalEnemy>();
		enemyBulletList = new ArrayList<EnemyBullet>();
		newShip();
		for (int i = 0; i < GAME_WIDTH; i++) {
			if (i % 60 == 0) {
				normalEnemyList.add(newNormalEnemy(i + 15, 20));
				normalEnemyList.add(newNormalEnemy(i + 15, 60));
				normalEnemyList.add(newNormalEnemy(i + 15, 100));
			}
		}

		this.setFocusable(true);
		this.addKeyListener(new AL());
		this.addMouseListener(new Mouse());
		this.setPreferredSize(SCREEN_SIZE);

		gameThread = new Thread(this);
		gameThread.start();
	}

	public static NormalEnemy newNormalEnemy(int x, int y) {
		return new NormalEnemy(x, y, NEnemy_WIDTH, NEnemy_HEIGHT);
	}

	public void newShip() {
		ship = new Ship((GAME_WIDTH - SHIP_WIDTH) / 2, GAME_HEIGHT - SHIP_HEIGHT, SHIP_WIDTH, SHIP_HEIGHT);
	}

	public void move() {
		if (state == State.Game) {
			// move ship and ship bullet
			ship.move();
			for (int i = 0; i < ship.arr.size(); i++) {
				ship.arr.get(i).move();
			}
			// normal enemy move
			if (!normalEnemyList.isEmpty()) {
				for (NormalEnemy nor : normalEnemyList) {
					nor.move();
				}
			}
			// normal enemy bullet move
			if (!enemyBulletList.isEmpty()) {
				for (EnemyBullet enemyBullet : enemyBulletList) {
					enemyBullet.move();
				}
			}
			// boss move
			if (!bossList.isEmpty())
				bossList.get(0).move();
			for(BossBullet b : bossBulletList) {
				b.move();
			}
		}
	}

	public void paint(Graphics g) {
		image = createImage(getWidth(), getHeight());
		graphics = image.getGraphics();
		draw(graphics);
		g.drawImage(image, 0, 0, this);
	}

	public void checkCollision() {
		for(BossBullet b : bossBulletList) {
			if(b.x == 0 || b.x == GAME_WIDTH-BOSS_BULLET_WIDTH) {
				b.changeDirection();
			}
			if(b.y == GAME_HEIGHT) {
				bossBulletList.remove(b);
				break;
			}
		}
		if (ship.x >= GAME_WIDTH - SHIP_WIDTH) {
			ship.x = GAME_WIDTH - SHIP_WIDTH;
		} else if (ship.x <= 0) {
			ship.x = 0;
		}
		for (Bullet b : ship.arr) {
			if (b.y < 20) {
				ship.arr.remove(b);
				break;
			}
		}
		// check ship collide with bullet
		for (EnemyBullet b : enemyBulletList) {
//			if (b.intersects(ship)) {
//				state = State.GameOver;
//				break;
//			}
			if (b.y > GAME_HEIGHT) {
				enemyBulletList.remove(b);
				break;
			}
		}
		//ship collide with boss bullet
		for(BossBullet b : bossBulletList) {
//			if(b.intersects(ship)) {
//				state= State.GameOver;
//				break;
//			}
		}
		// ship bullet collide with normal enemy
		if (normalEnemyList.isEmpty() == false) {
			OUTER: for (NormalEnemy a : normalEnemyList) {
				for (Bullet b : ship.arr) {
					if (a.intersects(b)) {
						normalEnemyList.remove(a);
						ship.arr.remove(b);
						break OUTER;
					}
				}
			}
		}

		// if normal Enemy move out of screen
		for (NormalEnemy b : normalEnemyList) {
			if (b.y > GAME_HEIGHT) {
				normalEnemyList.remove(b);
				if (normalEnemyList.isEmpty())
					state = State.GameOver;
				break;
			}
		}
		// if normal enemy collide with ship
		for (NormalEnemy b : normalEnemyList) {
			if (b.intersects(ship)) {
				state = State.GameOver;
				break;
			}
		}
		// check boss collisions
		//normalEnemyList.clear();
		if (bossList.isEmpty() == false) {
			for (Bullet b : ship.arr) {
				if(b.intersects(bossList.get(0))) {
					ship.arr.remove(b);
					int temp = bossList.get(0).getHealth() - 1;
					bossHealthBar.setCurrentHealth(bossHealthBar.getCurrentHealth()-13);
					bossList.get(0).setHealth(temp);
					if(bossList.get(0).getHealth()==0) {
						state = State.Win;
					}
					break;
				}
			}
		}
		if (!bossList.isEmpty()) {
			if (bossList.get(0).x == 0 || bossList.get(0).x == GAME_WIDTH - BOSS_WIDTH) {
				bossList.get(0).changeDirection();
			}
		}
	}

	public void draw(Graphics g) {
		if (state == State.Game) {
			// draw ship and ship bullet
			ship.draw(g);
			for (int i = 0; i < ship.arr.size(); i++) {
				ship.arr.get(i).draw(g);
			}
			// draw normal enemy
			for (NormalEnemy nor : normalEnemyList) {
				nor.draw(g);
			}
			// create bullet at random enemy
			if (timerForEnemy % 50 == 0) {
				if (!normalEnemyList.isEmpty()) {
					NormalEnemy temp = normalEnemyList.get(random.nextInt(normalEnemyList.size()));
					enemyBulletList.add(new EnemyBullet(temp.x + BULLET_WIDTH / 2, temp.y + BULLET_HEIGHT / 2,
							BULLET_WIDTH, BULLET_HEIGHT));
				}
			}
			// draw boss
			for (Boss b : bossList) {
				b.draw(g);
			}
			if(bossHealthBar != null && normalEnemyList.isEmpty()) {
				bossHealthBar.draw(g);
			}
			// draw enemy bullet
			if (normalEnemyList.isEmpty() == true) {
				if (!bossList.isEmpty()) {
					bossList.get(0).appear();
					if (timerForEnemy % 20 == 0) {
						// enemyBulletList.add(new EnemyBullet(boss.x, boss.y + BOSS_HEIGHT,
						// BULLET_WIDTH, BULLET_HEIGHT));
						enemyBulletList.add(new EnemyBullet(bossList.get(0).x + BOSS_WIDTH / 2,
								bossList.get(0).y + BOSS_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT));
						// enemyBulletList.add(new EnemyBullet(boss.x+BOSS_WIDTH, boss.y + BOSS_HEIGHT,
						// BULLET_WIDTH, BULLET_HEIGHT));
					}
				}
			}
			for (EnemyBullet enemyBullet : enemyBulletList) {
				enemyBullet.draw(g);
			}
			if(!bossList.isEmpty()) {
				if(bossList.get(0).x == 0 || bossList.get(0).x == GAME_WIDTH-BOSS_WIDTH) {
					if(bossList.get(0).x == 0) {
						bossBulletList.add(new BossBullet(bossList.get(0).x+BOSS_WIDTH, bossList.get(0).y + BOSS_WIDTH, BOSS_BULLET_WIDTH, BOSS_BULLET_WIDTH));
						enemyBulletList.add(new EnemyBullet(0, 0, BULLET_WIDTH, BULLET_HEIGHT));
					} else {
						bossBulletList.add(new BossBullet(bossList.get(0).x, bossList.get(0).y + BOSS_WIDTH, BOSS_BULLET_WIDTH, BOSS_BULLET_WIDTH));
						enemyBulletList.add(new EnemyBullet(GAME_WIDTH-BULLET_WIDTH, 0, BULLET_WIDTH, BULLET_HEIGHT));
					}
					
				}
			}
			for(BossBullet b : bossBulletList) {
				b.draw(g);
			}
		} else if (state == State.GameOver) {
			clear();
			g.setColor(Color.red);
			g.setFont(new Font("Ink Free", Font.BOLD, 40));
			g.drawString("Game Over", GAME_WIDTH / 2 - 100, GAME_HEIGHT / 2);
			// top line
			g.drawLine(200, 320, 400, 320);
			// left line
			g.drawLine(200, 320, 200, 370);
			// right line
			g.drawLine(400, 320, 400, 370);
			// bottom line
			g.drawLine(200, 370, 400, 370);
			g.setColor(Color.green);
			g.drawString("Play again", 210, 355);
		} else if (state == State.Menu) {
			g.setColor(Color.white);
			g.setFont(new Font("Ink Free", Font.BOLD, 60));
			// play button
			g.drawString("Play", GAME_WIDTH / 2 - 70, 200);
			g.drawRect(200, 150, 180, 70);
			// Exit button
			g.drawString("Exit", GAME_WIDTH / 2 - 70, 400);
			g.drawRect(200, 350, 180, 70);
		} else if (state == State.Win) {
			clear();
			g.setColor(Color.green);
			g.setFont(new Font("Ink Free", Font.BOLD, 40));
			g.drawString("You Win", GAME_WIDTH / 2 - 100, GAME_HEIGHT / 2);
			// top line
			g.drawLine(200, 320, 400, 320);
			// left line
			g.drawLine(200, 320, 200, 370);
			// right line
			g.drawLine(400, 320, 400, 370);
			// bottom line
			g.drawLine(200, 370, 400, 370);
			g.setColor(Color.green);
			g.drawString("Play again", 210, 355);
		}
	}

	public void clear() {
		normalEnemyList.clear();
		enemyBulletList.clear();
		ship.arr.clear();
		bossList.clear();
		bossBulletList.clear();
		bossHealthBar = null;
	}

	// key input
	public class AL extends KeyAdapter {
		public void keyPressed(KeyEvent e) {
			ship.keyPressed(e);
		}

		public void keyReleased(KeyEvent e) {
			ship.keyReleased(e);
		}
	}

	public class Mouse extends MouseAdapter {
		public void mousePressed(MouseEvent e) {
			menu.mousePressed(e);
		}
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		// game loop
		long lastTime = System.nanoTime();
		double amountOfTicks = 60.0;
		double ns = 1_000_000_000 / amountOfTicks;
		double delta = 0;
		while (true) {
			long now = System.nanoTime();
			delta += (now - lastTime) / ns;
			lastTime = now;
			if (delta >= 1) {
				move();
				checkCollision();
				repaint();
				delta--;
				timer += 0.01;
				timerForEnemy++;
//				 System.out.println(timer);
			}
		}
	}

}
