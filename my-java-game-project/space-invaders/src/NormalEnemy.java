import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*; 

public class NormalEnemy extends Rectangle {

	private int health = 1;
	private int yVelocity;
	private int xVelocity;
	
	NormalEnemy(int x, int y, int WIDTH, int HEIGHT) {
		super(x,y,WIDTH,HEIGHT);
		yVelocity = 3;
	}
	public void move() {
		if(GamePanel.timerForEnemy % 20 == 0) {
			y += yVelocity;
		}
		
	}
	
	public void draw(Graphics g) {
		g.setColor(Color.blue);
		g.fillRect(x, y, width, height);
	}
}
