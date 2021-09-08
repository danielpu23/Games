import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ConcurrentModificationException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.BlockingQueue;
import javax.swing.JPanel;

/**
 * GamePanel class that creates the game screen
 * This class is one of the Views in the MVC design patteern
 */
// This class represents the view
public class GamePanel extends JPanel implements Runnable, KeyListener {
	private Player p;		// The player character
	private Ground ground;		// The ground of the game
	Queue<Obstacle> obstacles;
	Thread thread;
	private int score;			// Keeps track of game score
	private boolean displayDeath;		//Indicates whether player is dead
	BlockingQueue<Message> queue;


	/**
	 * Constructs GamePanel object
	 *
	 * @param p the player character of the game
	 * @param ground the ground of the game
	 * @param queue the queue for game messages
	 */
	public GamePanel(Player p, Ground ground, BlockingQueue<Message> queue) {
		this.p = p;
		this.ground= ground;
		this.queue = queue;
		obstacles = new LinkedList<Obstacle>();
	}

	/**
	 * add obstacles to our obstacle queue
	 */
	public void addObstacle() {
		int random = (int) (Math.random() * 2);
		if (random == 0) {
			obstacles.add(new Stump());
		} else {
			obstacles.add(new Bird());
		}
	}

	/**
	 * Checks if obstacle and player collide
	 * Also checks if an obstacle has left the game screen
	 */
	public void updateObstacles() {
		for (Obstacle obs : obstacles) {
			obs.update();
			if (obs.checkCollision(p.getX(), p.getY())) { // If player collided with object, they are dead
				p.die();
			}
		}
		if (obstacles.peek() == null) {
			// Do nothing if there's nothing in the queue
		} else if (obstacles.peek().outOfBounds()) {
			obstacles.remove();
		}
	}

	/**
	 * Start game function
	 */
	public void startGame(){
		score = 0;
		displayDeath = false;
		thread = new Thread(this);
		thread.start();
		new java.util.Timer().schedule(
				new java.util.TimerTask() {
					@Override
					public void run() {
						addObstacle();	 // Adding obstacles needs a separate delay to make sure objects are created at
					}							 // a reasonable rate

				},
				0, 1500
		);

	}

	/**
	 * Adds the game content to the game
	 *
	 * @param g Graphics object that is used to add the game content
	 */
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		ground.draw(g);
		p.draw(g);
		try {
			for (Obstacle obs : obstacles) {
				obs.draw(g);
			}
		} catch (ConcurrentModificationException e) {
			// Don't draw if we are currently iterating through the Queue
		}
	    g.setColor(Color.WHITE);
	    g.setFont(new Font("Serif", Font.BOLD, 25));
	    g.drawString("Score: " + Integer.toString(score), 500, 30);		// display score
	    if(displayDeath) {												// display death screen
	 	    g.setFont(new Font("Serif", Font.BOLD, 35));
	 	    g.drawString("You Died", 245, 90);

			g.setFont(new Font("Serif", Font.BOLD, 20));
			g.drawString("Press Enter to play again", 205, 120);
			g.drawString("or Backspace to quit", 227, 145);
	    }
	}
	/**
	 * Updates the game
	 */
	public void updateGame() {
		updateScore();
		updateObstacles();
		ground.update();
	}
	/**
	 * Updates the score of the game
	 */
	public void updateScore() {
		score++;
	}
	/**
	 * Invokes death screen
	 */
	public void deathScreen() {
		displayDeath = true;
		repaint();
	}

	/**
	 * Resets the game screen and starts a new game
	 */
	public void resetGame() {
		displayDeath = false;
		score = 0;
		obstacles = new LinkedList<Obstacle>();
		thread = new Thread(this);
		thread.start();
	}

	/**
	 * Loop to keep painting
	 */
	@Override
	public void run() {
		while(true) {
			updateGame();
			repaint();
			try {
				Thread.sleep(100);				// put a slight delay
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			if(p.isDead()) {
				deathScreen();
				break;
			}
		}

	}
	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}

	/**
	 * When a key is pressed it adds the message to the queue
	 * for the controller to use
	 * @param e
	 */
	@Override
	public void keyPressed(KeyEvent e) {				// note, there is a slight delay between space bar being press and jumping
		if(e.getKeyCode() == KeyEvent.VK_SPACE) {		// spam clicking jump doesn't work and is unpredictable
			//manager.playerJump();
			try {
				queue.put(new JumpMessage());
			}
			catch (InterruptedException exception){}

		}
		if(e.getKeyCode() == KeyEvent.VK_S){
			//manager.playerDuck();
			try {
				queue.put(new DuckMessage());
			}
			catch (InterruptedException exception){}

		}
		if(e.getKeyCode() == KeyEvent.VK_ENTER){
			/*
				Something interesting to note when the if-statement is not added: If Enter is pressed in the middle of
				the game, the game resets, but it goes faster. If you press Enter multiple times, the game goes even
				faster. The program may crash sometimes when Enter is pressed multiple times.

				The if-statement was added to keep the game consistent with its speed, but it could be taken out to
				allow the user to increase the speed (and therefore difficulty). It may be risky to do this since the
				program can crash in some cases.


			 */
			if(p.isDead()) {
				try {
					queue.put(new ResetGameMessage());
					resetGame();
				}
				catch (InterruptedException exception){}

			}
		}
		if(e.getKeyCode() == KeyEvent.VK_BACK_SPACE) {
			// Makes sure game is over before game can be exited
			if(p.isDead()) {
				System.exit(0);
			}
		}
	}
	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub

	}
}
