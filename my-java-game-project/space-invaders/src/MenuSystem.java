import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*; 

public class MenuSystem {
	//play again buttom
	public void mousePressed(MouseEvent e) {
		if(GamePanel.state == State.GameOver || GamePanel.state == State.Win) {
			if(e.getX() >= 200 && e.getX() <= 400) {
				if(e.getY() >= 320 && e.getY() <= 370) {
					GamePanel.bossList.add(new Boss((GamePanel.GAME_WIDTH - GamePanel.BOSS_WIDTH) / 2, -GamePanel.BOSS_HEIGHT, GamePanel.BOSS_WIDTH, GamePanel.BOSS_HEIGHT));
					GamePanel.bossHealthBar = new BossHealthBar(GamePanel.bossList.get(0));
					for (int i = 0; i < GamePanel.GAME_WIDTH; i++) {
						if (i % 60 == 0) {
							GamePanel.normalEnemyList.add(GamePanel.newNormalEnemy(i+15, 20));
							GamePanel.normalEnemyList.add(GamePanel.newNormalEnemy(i+15, 60));
							GamePanel.normalEnemyList.add(GamePanel.newNormalEnemy(i+15, 100));
						}
					}
					GamePanel.state = State.Game;
				}
			}
		}
		//exit button
		if(GamePanel.state == State.Menu) {
			if(e.getX() >= 200 && e.getX() <= 380) {
				if(e.getY() >= 350 && e.getY() <= 420) {
					System.exit(1);
				}
			}
		}
		// play button
		if(GamePanel.state == State.Menu) {
			if(e.getX() >= 200 && e.getX() <= 380) {
				if(e.getY() >= 150 && e.getY() <= 220) {
					GamePanel.state = State.Game;
				}
			}
		}
	}
	
}
