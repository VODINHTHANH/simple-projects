import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class BossBullet extends Rectangle {

	private float xFloat;
	private float yFloat;
	private float yVelocity;
	private float xVelocity;
	private Random r;

	BossBullet(int x, int y, int WIDTH, int HEIGHT) {
		super(x, y, WIDTH, HEIGHT);
		yVelocity = 2f;
		xFloat = (float) x;
		yFloat = (float) y;
		r = new Random();
		int randomNumber = r.nextInt(2);
		if (randomNumber == 0) {
			xVelocity = 2;
		} else if (randomNumber == 1) {
			xVelocity = -2;
		}

	}

	void changeDirection() {
		this.xVelocity *= -1.0f;
	}

	public float getyVelocity() {
		return yVelocity;
	}

	public void setyVelocity(float yVelocity) {
		this.yVelocity = yVelocity;
	}

	public float getxVelocity() {
		return xVelocity;
	}

	public void setxVelocity(float xVelocity) {
		this.xVelocity = xVelocity;
	}

	public void move() {
		yFloat += yVelocity;
		y = (int) yFloat;
		xFloat += xVelocity;
		x = (int) xFloat;

	}

	public void draw(Graphics g) {
		g.setColor(Color.GRAY);
		g.fillRect(x, y, width, height);
	}
}
