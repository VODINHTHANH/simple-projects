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

	static double timer = 0.0;
	static int timerForEnemy = 0;
	static final Dimension SCREEN_SIZE = new Dimension(GAME_WIDTH, GAME_HEIGHT);
	Thread gameThread;
	Image image;
	Graphics graphics;
	Random random;
	Ship ship;
	ArrayList<NormalEnemy> normalEnemyList;
	ArrayList<EnemyBullet> enemyBulletList;

	GamePanel() {
		random = new Random();
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
		this.setPreferredSize(SCREEN_SIZE);

		gameThread = new Thread(this);
		gameThread.start();
	}

	public NormalEnemy newNormalEnemy(int x, int y) {
		return new NormalEnemy(x, y, NEnemy_WIDTH, NEnemy_HEIGHT);
	}

	public void newShip() {
		ship = new Ship((GAME_WIDTH - SHIP_WIDTH) / 2, GAME_HEIGHT - SHIP_HEIGHT, SHIP_WIDTH, SHIP_HEIGHT);
	}

	public void move() {
		ship.move();
		for (int i = 0; i < ship.arr.size(); i++) {
			ship.arr.get(i).move();
		}
		if (!normalEnemyList.isEmpty()) {
			for (NormalEnemy nor : normalEnemyList) {
				nor.move();
			}
		}
		if (!enemyBulletList.isEmpty()) {
			for (EnemyBullet enemyBullet : enemyBulletList) {
				enemyBullet.move();
			}
		}
	}

	public class AL extends KeyAdapter {
		public void keyPressed(KeyEvent e) {
			ship.keyPressed(e);
		}

		public void keyReleased(KeyEvent e) {
			ship.keyReleased(e);
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
		for (EnemyBullet b : enemyBulletList) {
			if (b.y > GAME_HEIGHT) {
				enemyBulletList.remove(b);
				break;
			}
		}
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

	}

	public void draw(Graphics g) {
		ship.draw(g);
		for (int i = 0; i < ship.arr.size(); i++) {
			ship.arr.get(i).draw(g);
		}
		for (NormalEnemy nor : normalEnemyList) {
			nor.draw(g);
		}
		if (timerForEnemy % 20 == 0) {
			if (!normalEnemyList.isEmpty()) {
				NormalEnemy temp = normalEnemyList.get(random.nextInt(normalEnemyList.size()));
				enemyBulletList.add(new EnemyBullet(temp.x + BULLET_WIDTH / 2, temp.y + BULLET_HEIGHT / 2, BULLET_WIDTH,
						BULLET_HEIGHT));
			}
		}
		for (EnemyBullet enemyBullet : enemyBulletList) {
			enemyBullet.draw(g);
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
