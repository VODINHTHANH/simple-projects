import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class BossHealthBar extends Rectangle{
	private Boss boss;
	private int currentHealth;
	
	BossHealthBar(Boss boss) {
		this.boss = boss;
		currentHealth = 129;
	}

	public void draw(Graphics g) {
		g.setColor(Color.white);
		int x1 = 240;// x1
		int x2 = 20;// y1
		int y1 = 370;// x2
		int y2 = 40;// y2
		g.drawRect(240, 20, 130, 20);
		g.setColor(Color.green);
		if(boss.getHealth() < 5) g.setColor(Color.red);
		g.fillRect(241, 21, currentHealth, 19);
		
	}

	public int getCurrentHealth() {
		return currentHealth;
	}

	public void setCurrentHealth(int currentHealth) {
		if(currentHealth >= 0) this.currentHealth = currentHealth;
	}
	
}
