import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.Timer;

public class GamePanel extends JPanel implements ActionListener {

	static final int SCREEN_WIDTH = 600;
	static final int SCREEN_HEIGHT = 600;
	static final int UNIT_SIZE = 25;
	static final int ROW_UNIT = SCREEN_WIDTH / UNIT_SIZE;
	static final int COL_UNIT = SCREEN_HEIGHT / UNIT_SIZE;
	static final int GAME_UNIT = (SCREEN_WIDTH * SCREEN_HEIGHT) / UNIT_SIZE;
	static final int DELAY = 75;
	final int x[] = new int[4];
	final int y[] = new int[4];
	int enemyParts = 98;
	final int u[] = new int[enemyParts];
	final int z[] = new int[enemyParts];
	int bodyParts = 4;
	
	int appleEaten;
	int appleX;
	int appleY;
	boolean running = false;
	Timer timer;
	Random random;
	static boolean firtTime = true;

	public GamePanel() {
		random = new Random();
		this.setPreferredSize(new Dimension(SCREEN_WIDTH, SCREEN_HEIGHT));
		this.setBackground(Color.black);
		this.setFocusable(true);
		this.addKeyListener(new MyKeyAdapter());
		startGame();
	}

	public void startGame() {
		newApple();
		running = true;
		timer = new Timer(DELAY, this);
		timer.start();
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		draw(g);
	}

	public void draw(Graphics g) {
		if (firtTime) {
			g.setColor(Color.green);
			x[0] = Math.floorDiv(SCREEN_WIDTH / UNIT_SIZE, 2) * UNIT_SIZE;
			y[0] = (Math.floorDiv(SCREEN_WIDTH, UNIT_SIZE) - 4) * UNIT_SIZE;
			x[1] = x[0];
			x[2] = x[0] - UNIT_SIZE;
			x[3] = x[0] + UNIT_SIZE;
			y[1] = y[0] + UNIT_SIZE;
			y[2] = y[1];
			y[3] = y[1];

			for (int i = 0; i < bodyParts; i++) {
				g.fillRect(x[i], y[i], UNIT_SIZE, UNIT_SIZE);
			}
			
			int index = 0;
			for (int i = 0; i < ROW_UNIT; i++) {
				for (int j = 0; j < COL_UNIT; j++) {
					if (i < (ROW_UNIT - 4) && i > 4) {
						if (j > 0 && j < COL_UNIT / 3) {
							if (index < enemyParts) {
								u[index] = i * UNIT_SIZE;
								z[index] = j * UNIT_SIZE;
								index++;
							}
						}
					}
				}
			}
			firtTime = false;
		}
		if (running) {
			for (int i = 0; i < SCREEN_HEIGHT / UNIT_SIZE; i++) {
				g.drawLine(i * UNIT_SIZE, 0, i * UNIT_SIZE, SCREEN_HEIGHT);
				g.drawLine(0, i * UNIT_SIZE, SCREEN_WIDTH, i * UNIT_SIZE);
			}
			g.setColor(Color.cyan);
			for (int i = 0; i < enemyParts; i++) {
				g.fillRect(u[i], z[i], UNIT_SIZE, UNIT_SIZE);
			}
			for (int i = 0; i < bodyParts; i++) {
				if (i == 0) {
					g.setColor(Color.green);
					g.fillRect(x[i], y[i], UNIT_SIZE, UNIT_SIZE);
				} else {
					g.setColor(new Color(45, 180, 0));
					// g.setColor(new Color(random.nextInt(255), random.nextInt(255),
					// random.nextInt(255)));
					g.fillRect(x[i], y[i], UNIT_SIZE, UNIT_SIZE);
				}
			}
			// Display the score
			g.setColor(Color.red);
			g.setFont(new Font("Ink Free", Font.BOLD, 40));
			FontMetrics metric = getFontMetrics(g.getFont());
			g.drawString("Score: " + appleEaten, (SCREEN_WIDTH - metric.stringWidth("Score: " + appleEaten)) / 2,
					g.getFont().getSize());
		} else {
			gameOver(g);
		}
	}

	public void newApple() {
		appleX = random.nextInt((int) (SCREEN_WIDTH / UNIT_SIZE)) * UNIT_SIZE;
		appleY = random.nextInt((int) (SCREEN_HEIGHT / UNIT_SIZE)) * UNIT_SIZE;
	}

	public void checkApple() {
		if ((x[0] == appleX) && (y[0] == appleY)) {
			bodyParts++;
			appleEaten++;
			newApple();
		}
	}

	public void checkCollisions() {
		// check if head touches left border
//		if (x[0] < 0) {
//			running = false;
//		}
//		// check if head touches right border
//		if (x[0] > SCREEN_WIDTH) {
//			running = false;
//		}
//		// check if head touches top border
//		if (y[0] < 0) {
//			running = false;
//		}
//		// check if head touches bottom border
//		if (y[0] > SCREEN_HEIGHT) {
//			running = false;
//		}

		if (!running) {
			
			timer.stop();
		}
	}

	public void gameOver(Graphics g) {
		// Display the score
		g.setColor(Color.red);
		g.setFont(new Font("Ink Free", Font.BOLD, 40));
		FontMetrics metrics = getFontMetrics(g.getFont());
		g.drawString("Score: " + appleEaten, (SCREEN_WIDTH - metrics.stringWidth("Score: " + appleEaten)) / 2,
				g.getFont().getSize());
		// Display game over text
		g.setColor(Color.red);
		g.setFont(new Font("Ink Free", Font.BOLD, 75));
		FontMetrics metric = getFontMetrics(g.getFont());
		g.drawString("Game Over", (SCREEN_WIDTH - metric.stringWidth("Game Over")) / 2, SCREEN_HEIGHT / 2);
	}

	public class MyKeyAdapter extends KeyAdapter {
		@Override
		public void keyPressed(KeyEvent e) {
			switch (e.getKeyCode()) {
			case KeyEvent.VK_A:
				for (int i = 0; i < bodyParts; i++) {
					if(x[i] - UNIT_SIZE > 0) x[i] = x[i] - UNIT_SIZE;
				}
				break;
			case KeyEvent.VK_D:
				for (int i = 0; i < bodyParts; i++)
					x[i] = x[i] + UNIT_SIZE;
				break;
			case KeyEvent.VK_W:
				for (int i = 0; i < bodyParts; i++)
					y[i] = y[i] - UNIT_SIZE;
				break;
			case KeyEvent.VK_S:
				for (int i = 0; i < bodyParts; i++)
					y[i] = y[i] + UNIT_SIZE;
				break;
			}
		}

	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if (running) {
			checkApple();
			checkCollisions();
		}
		repaint();
	}

}
