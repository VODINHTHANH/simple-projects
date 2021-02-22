import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class EnemyBullet extends Rectangle {
	int yVelocity;

	EnemyBullet(int x, int y, int WIDTH, int HEIGHT) {
		super(x, y, WIDTH, HEIGHT);
		yVelocity = 5;
	}
	
	public void move() {
		y += yVelocity;
	}
	
	public void draw(Graphics g) {
		g.setColor(Color.cyan);
		g.fillRect(x, y, width, height);
	}
}
