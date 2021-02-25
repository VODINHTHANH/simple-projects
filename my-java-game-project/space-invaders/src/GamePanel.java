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
	static final int NEnemy_WIDTH = 25;
	static final int NEnemy_HEIGHT = 25;
	public static int BOSS_WIDTH = 100;
	public static int BOSS_HEIGHT = 100;
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
	MenuSystem menu;
	private Boss boss;

	GamePanel() {
		boss = new Boss((GAME_WIDTH - BOSS_WIDTH)/2, -BOSS_HEIGHT, BOSS_WIDTH, BOSS_HEIGHT);
		menu = new MenuSystem();
		random = new Random();
		state = State.Menu;
		normalEnemyList = new ArrayList<NormalEnemy>();
		enemyBulletList = new ArrayList<EnemyBullet>();
		newShip();
		for (int i = 0; i < GAME_WIDTH; i++) {
			if (i % 60 == 0) {
				normalEnemyList.add(newNormalEnemy(i, 20));
				normalEnemyList.add(newNormalEnemy(i, 60));
				normalEnemyList.add(newNormalEnemy(i, 100));
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
			//move ship and ship bullet
			ship.move();
			for (int i = 0; i < ship.arr.size(); i++) {
				ship.arr.get(i).move();
			}
			//normal enemy move
			if (!normalEnemyList.isEmpty()) {
				for (NormalEnemy nor : normalEnemyList) {
					nor.move();
				}
			}
			//normal enemy bullet move
			if (!enemyBulletList.isEmpty()) {
				for (EnemyBullet enemyBullet : enemyBulletList) {
					enemyBullet.move();
				}
			}
			//boss move
			
			boss.move();
		}
	}

	public void paint(Graphics g) {
		image = createImage(getWidth(), getHeight());
		graphics = image.getGraphics();
		draw(graphics);
		g.drawImage(image, 0, 0, this);
	}

	public void checkCollision() {
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
		// ship bullet collide with normal enemy
		if (!normalEnemyList.isEmpty()) {
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
		//if normal Enemy move out of screen
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
		//check boss collisions
		if(boss.x == 0 || boss.x == GAME_WIDTH-BOSS_WIDTH) {
			boss.changeDirection();
		}
	}

	public void draw(Graphics g) {
		if (state == State.Game) {
			//draw ship and ship bullet
			ship.draw(g);
			for (int i = 0; i < ship.arr.size(); i++) {
				ship.arr.get(i).draw(g);
			}
			//draw normal enemy
			for (NormalEnemy nor : normalEnemyList) {
				nor.draw(g);
			}
			//create bullet at random enemy
			if (timerForEnemy % 20 == 0) {
				if (!normalEnemyList.isEmpty()) {
					NormalEnemy temp = normalEnemyList.get(random.nextInt(normalEnemyList.size()));
					enemyBulletList.add(new EnemyBullet(temp.x + BULLET_WIDTH / 2, temp.y + BULLET_HEIGHT / 2,
							BULLET_WIDTH, BULLET_HEIGHT));
				}
			}
			//draw boss 
			//normalEnemyList.clear();
			if(normalEnemyList.isEmpty() == true) {
				boss.appear();
				boss.draw(g);
				if(timerForEnemy % 20 == 0) {
					//enemyBulletList.add(new EnemyBullet(boss.x, boss.y + BOSS_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT));
					enemyBulletList.add(new EnemyBullet(boss.x+BOSS_WIDTH/2, boss.y + BOSS_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT));
					//enemyBulletList.add(new EnemyBullet(boss.x+BOSS_WIDTH, boss.y + BOSS_HEIGHT, BULLET_WIDTH, BULLET_HEIGHT));
				}
			}
			//draw enemy bullet
			for (EnemyBullet enemyBullet : enemyBulletList) {
				enemyBullet.draw(g);
			}
		} else if (state == State.GameOver) {
			gameOver();
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
			//play button
			g.drawString("Play", GAME_WIDTH / 2 - 70, 200);
			// top line
			g.drawLine(200, 150, 380, 150);
			// bottom line
			g.drawLine(200, 220, 380, 220);
			// left line
			g.drawLine(200, 150, 200, 220);
			// right line
			g.drawLine(380, 150, 380, 220);
			//Exit button
			g.drawString("Exit", GAME_WIDTH / 2 - 70, 400);
			int x1 = 200;// x1
			int x2 = 350;// y1
			int y1 = 380;// x2
			int y2 = 420;// y2
			//top line
			g.drawLine(x1, x2, y1, x2);
			// bottom line
			g.drawLine(x1, y2, y1, y2);
			// left line
			g.drawLine(x1, x2, x1, y2);
			// right line
			g.drawLine(y1, x2, y1, y2);
		} 
	}

	public void gameOver() {
		normalEnemyList.clear();
		enemyBulletList.clear();
		ship.arr.clear();
		
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
