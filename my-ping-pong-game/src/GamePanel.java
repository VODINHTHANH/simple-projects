import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.Timer;

import GamePanel.MyKeyAdapter;

public class GamePanel extends JPanel implements ActionListener{
	
	static Random random;
	static Timer timer;
	static char direction ='R';
	static boolean running = false;
	static boolean isCreatEnemy = false;
	static final int SCREEN_WIDTH = 600;
	static final int SCREEN_HEIGHT = 600;
	static final int UNIT_SIZE = 100;
	static final int GAME_UNIT = (SCREEN_WIDTH*SCREEN_HEIGHT)/UNIT_SIZE;
	static final int DELAY = 200;
	
	public GamePanel() {
		random = new Random();
		this.setPreferredSize(new Dimension(SCREEN_WIDTH, SCREEN_HEIGHT));
		this.setBackground(Color.black);
		this.setFocusable(true);
		this.addKeyListener(new MyKeyAdapter());
		startGame();
	}
	private void startGame() {
		running = true;
		timer = new Timer(DELAY, this);
		timer.start();
	}
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		draw(g);
	}
	
	private void checkEnemyDestroy() {
		
	}
	
	private void checkCollisions() {
		
	}
	
	private void move() {
		
	}
	
	private void gameOver() {
		
	}
	
	public class MyKeyAdapter extends KeyAdapter {
		@Override
		public void keyPressed(KeyEvent e) {
			switch(e.getKeyCode()) {
			case KeyEvent.VK_A:
				direction = 'L';
				break;
			case KeyEvent.VK_D:
				direction = 'R';
				break;
			case KeyEvent.VK_W:
				direction = 'U';
				break;
			case KeyEvent.VK_S:
				direction = 'D';
				break;
			}
		}
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if(running) {
			
		}
	}
	
}