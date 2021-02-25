import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class Boss extends Rectangle {

	private int health = 10;
	private float xVel = 5.0f;
	private float yVel = 2.0f;
	private float xB;
	private float yB;
	
	Boss(int x, int y, int WIDTH, int HEIGHT) {
		super(x, y, WIDTH, HEIGHT);
		xB = x;
		yB = y;
	}

	public void appear() {
		if (yB < 20) {
			yB += yVel;
			y = (int)yB;
		}
	}
	public void move() {
		if(y == 20) {
			xB += xVel;
			x = (int)xB;
		}
	}

	public void draw(Graphics g) {
		g.setColor(Color.GRAY);
		g.fillRect(x, y, width, height);
	}
	
	void changeDirection() {
		this.xVel *= -1.0f;
	}

}
