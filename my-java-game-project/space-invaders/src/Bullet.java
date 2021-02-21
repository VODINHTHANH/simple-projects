import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class Bullet  extends Rectangle{

	int yVelocity;
	
	Bullet(int x, int y, int WIDTH, int HEIGHT) {
		super(x, y, WIDTH, HEIGHT);
		yVelocity = 5;
	}
	
	public void move() {
		y -= yVelocity;
	}
	
	public void draw(Graphics g) {
		g.setColor(Color.red);
		g.fillRect(x, y, width, height);
	}
}
