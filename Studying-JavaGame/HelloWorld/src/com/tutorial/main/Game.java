package com.tutorial.main;

import java.awt.*;
import java.awt.image.BufferStrategy;
import java.io.Serial;
import java.security.Key;
import java.util.Random;

public class Game extends Canvas implements Runnable {

    @Serial
    private static final long serialVersionUID = 1550691097823471818L;
    public static final int WIDTH = 640, HEIGHT = WIDTH/12 * 9;
    private Thread thread;
    private boolean running = false;
    private Handler handler;
    private Random r;
    private HUD hud;
    private Spawn spawner;
    public enum STATE {
        Menu,
        Help,
        Game,
        End
    };
    public STATE gameState = STATE.Menu;
    private Menu menu;

    public Game() {
        handler = new Handler();
        hud = new HUD();
        menu = new Menu(this, handler, hud);
        this.addKeyListener(new KeyInput(handler));
        this.addMouseListener(menu);

        spawner = new Spawn(handler, hud);

        new Window(WIDTH, HEIGHT, "Let's build a game", this);

        r = new Random();

        if(gameState == STATE.Game) {
            handler.addObject(new Player(WIDTH/2 - 32,HEIGHT/2 - 32, ID.Player, handler));
            handler.addObject(new BasicEnemy(r.nextInt(Game.WIDTH-50), r.nextInt(Game.HEIGHT-50), ID.BasicEnemy, handler));
        } else {
            for(int i = 0; i < 20; i++) {
                handler.addObject(new MenuParticle(r.nextInt(WIDTH),r.nextInt(HEIGHT), ID.MenuParticle, handler));
            }
        }


    }

    public synchronized void start() {
        thread = new Thread(this);
        thread.start();
        running = true;
    }

    public synchronized void stop() {
        try{
            thread.join();
            running = false;
        }catch (Exception e) {
            e.printStackTrace();
        }

    }

    public void run() {
        this.requestFocus();
        long lastTime = System.nanoTime();
        double amountOfTicks = 60.0;
        double ns = 1_000_000_000 / amountOfTicks;
        double delta = 0;
        long timer = System.currentTimeMillis();
        int frames = 0;
        while(running) {
            long now = System.nanoTime();
            delta += (now - lastTime) / ns;
            lastTime = now;
            while (delta >= 1) {
                tick();
                delta--;
            }
            if(running)
                render();
            frames++;

            if (System.currentTimeMillis() - timer > 1000) {
                timer += 1000;
                //System.out.println("FPS: " + frames);
                frames = 0;
            }
        }
        stop();
    }

    private void tick() {
        handler.tick();
        if(gameState == STATE.Game) {
            hud.tick();
            spawner.tick();
            if(HUD.HEALTH <= 0) {
                HUD.HEALTH = 200;
                gameState = STATE.End;
                handler.removePlayer();
                for(int i = 0; i < 20; i++) {
                    handler.addObject(new MenuParticle(r.nextInt(WIDTH),r.nextInt(HEIGHT), ID.MenuParticle, handler));
                }
            }
        } else if(gameState == STATE.Menu || gameState == STATE.End) {
            menu.tick();
        }

    }

    private void render() {
        BufferStrategy bs = this.getBufferStrategy();
        if(bs == null){
            this.createBufferStrategy(3);
            return;
        }

        Graphics g = bs.getDrawGraphics();
        g.setColor(Color.BLACK);
        g.fillRect(0,0, WIDTH, HEIGHT);

        handler.render(g);
        if(gameState == STATE.Game) {
            hud.render(g);
        } else if(gameState == STATE.Menu || gameState == STATE.Help || gameState == STATE.End){
            menu.render(g);
        }

        g.dispose();
        bs.show();
    }

    public static float clamp(float var, float min, float max) {
        if(var >= max)
            return var = max;
        else if(var <= min)
            return var = min;
        else
            return var;
    }

    public static void main(String[] args) {
        new Game();

    }
}

