import javax.swing.*;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * GameFrame class that creates the frame of the game and starts the program
 */
public class GameFrame extends JFrame {
	/**
	 * Constructs GameFrame object
	 * We have a Start Screen but as of right now it wont go to the
	 * game screen after clicking start
	 */
	public GameFrame() {
		super("Jungle Dash");
		setSize(650, 322);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(false);

		Player p = new Player();
		Ground g = new Ground();
		BlockingQueue<Message> queue = new LinkedBlockingQueue();
		GamePanel panel = new GamePanel(p, g, queue);
		GameManager m = new GameManager(p, panel, queue);
		StartPanel start = new StartPanel(g);

		// Button is added to allow user to start game
		JButton startButton = new JButton("Start game");
		startButton.setOpaque(false);
		startButton.setContentAreaFilled(false);
		startButton.setBorderPainted(false);
		start.add(startButton);
		startButton.setFocusable(false);

		startButton.addActionListener(event -> {
			startGame(start, panel, m);
		});


		add(start);
		setVisible(true);
		//startGame(start, panel, m);
	}

	/**
	 * Transitions title panel to game panel and starts the game for the user
	 *
	 * @param start the panel that contains the title screen
	 * @param panel the panel that contains the game screen
	 * @param m		the gamemanager that contains the controller
	 */
	public void startGame(StartPanel start, GamePanel panel, GameManager m) {
		start.setVisible(false);
		add(panel);
		addKeyListener(panel);
		m.mainLoop();
	}

	public static void main(String args[]) {
		new GameFrame();
	}
}
