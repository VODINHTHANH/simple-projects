import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class Boss extends Rectangle {

	public int health;
	private int distance;
	private float xVel = 5.0f;
	private float yVel = 2.0f;
	private float xB;
	private float yB;

	Boss(int x, int y, int WIDTH, int HEIGHT) {
		super(x, y, WIDTH, HEIGHT);
		xB = x;
		yB = y;
		health = 10;
		distance = 50;
	}

	public int getDistance() {
		return distance;
	}
	
	public void appear() {
		if (yB < distance) {
			yB += yVel;
			y = (int) yB;
		}
	}
	

	public void move() {
		if (y == distance) {
			xB += xVel;
			x = (int) xB;
		}
	}

	public void draw(Graphics g) {
		g.setColor(Color.GRAY);
		g.fillRect(x, y, width, height);
	}

	void changeDirection() {
		this.xVel *= -1.0f;
	}

	public int getHealth() {
		return health;
	}

	public void setHealth(int health) {
		if (health >= 0)
			this.health = health;
	}

}
