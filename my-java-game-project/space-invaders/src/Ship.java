import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class Ship extends Rectangle {

	int xVelocity;
	int speed = 10;
	public static boolean isSuspended = false;
	public ArrayList<Bullet> arr = new ArrayList<Bullet>();
	public int zo = 0;
	public double a[] = new double[2];

	Ship(int x, int y, int SHIP_WIDTH, int SHIP_HEIGHT) {
		super(x, y, SHIP_WIDTH, SHIP_HEIGHT);
		a[0] = GamePanel.timer;
	}

	public void setXDirection(int xDirection) {
		xVelocity = xDirection;
	}

	public void keyPressed(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_A) {
			setXDirection(-speed);
			move();
		}
		if (e.getKeyCode() == KeyEvent.VK_D) {
			setXDirection(speed);
			move();
		}
		if (e.getKeyCode() == KeyEvent.VK_W) {
			a[1] = GamePanel.timer;
			if(a[1]-a[0] > 0.1) {
				newBullet();
				a[0]=a[1];
			}

		}
	}

	public void keyReleased(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_A) {
			setXDirection(0);
			move();
		}
		if (e.getKeyCode() == KeyEvent.VK_D) {
			setXDirection(0);
			move();
		}

	}

	public void newBullet() {
		arr.add(new Bullet(x + (width - GamePanel.BULLET_WIDTH) / 2, y - GamePanel.BULLET_HEIGHT,
				GamePanel.BULLET_WIDTH, GamePanel.BULLET_HEIGHT));
	}

	public void move() {
		x = x + xVelocity;
	}

	public void draw(Graphics g) {
		g.setColor(Color.green);
		g.fillRect(x, y, width, height);
	}

}
