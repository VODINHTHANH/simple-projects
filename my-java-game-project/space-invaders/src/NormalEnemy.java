import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*; 

public class NormalEnemy extends Rectangle {
	
	private float yVelocity;
	private float yN;
	
	NormalEnemy(int x, int y, int WIDTH, int HEIGHT) {
		super(x,y,WIDTH,HEIGHT);
		yVelocity = 0.1f;
		yN = y;
	}
	public void move() {
			yN += yVelocity;
			y = (int)yN;
	}
	
	public void draw(Graphics g) {
		g.setColor(Color.blue);
		g.fillRect(x, y, width, height);
	}
 
}
