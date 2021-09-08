import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.BlockingQueue;

/**
 * Class is the controller of MVC pattern
 * This class is responsible for controlling the flow of the game and what the Player does when it is
 * called from GamePanel.
 * It also contains a Queue of obstacles that are continually added and removed as the game progresses.
 */
public class GameManager {
	private Player p;
	GamePanel panel;
	BlockingQueue<Message> queue;

	private List<Valve> valves = new LinkedList<Valve>();


	/**
	 * Constructs a GameManager
	 *
	 * @param p Player
	 * @param panel
	 * @param queue
	 */
	public GameManager(Player p, GamePanel panel, BlockingQueue<Message> queue) {
		this.p = p;
		this.queue = queue;
		this.panel = panel;
		valves.add(new DoJumpValve(p));
		valves.add(new DoDuckValve(p));
		valves.add(new ResetGameValve(p));
	}


	/**
	 * This method is run from the mainloop
	 * It continually checks valve response and
	 * takes in messages then tells the model what to do
	 *
	 */
	public void update() {
		ValvesResponse response = ValvesResponse.EXECUTED;
		Message message = null;
		while( response != ValvesResponse.FINISH) {
			try {
				message = queue.take();
			} catch (InterruptedException exception) {}

			for (Valve valve : valves) {
				response = valve.execute(message);

				if (response != ValvesResponse.MISS)
					break;
			}
		}
	}

	/**
	 * Tells the panel the game is starting
	 */
	public void startGame(){
		panel.startGame();
	}

	/**
	 * Resets Player and tells panel to reset
	 */
	public void resetGame() {
		p.revive();
		panel.resetGame();

	}

	/**
	 * This is the controllers main loop
	 */

	public void mainLoop(){
		startGame();

		while(true){
			this.update();								//checks the BlockingQueue
			try {
				Thread.sleep(100);				// put a slight delay
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}
	}
}

