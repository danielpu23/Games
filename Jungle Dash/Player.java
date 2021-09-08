import java.awt.Graphics;
import java.awt.Image;


import javax.swing.ImageIcon;

/**
 * Class that represents the Player of our game
 * Represents one of the Models in the MVC design pattern
 */
public class Player {
	private int x;
	private int y;
	private boolean running;
	private boolean dead;
	private boolean ducking;
	private boolean jumping;
	private int animationIndex;  // keeps track of what running animation we currently have
	Image runPlayer1 = new ImageIcon(this.getClass().getResource("Woodcutter/woodcutter_run1.png")).getImage();
	Image runPlayer2 = new ImageIcon(this.getClass().getResource("Woodcutter/woodcutter_run2.png")).getImage();
	Image runPlayer3 = new ImageIcon(this.getClass().getResource("Woodcutter/woodcutter_run3.png")).getImage();
	Image runPlayer4 = new ImageIcon(this.getClass().getResource("Woodcutter/woodcutter_run4.png")).getImage();
	Image jumpPlayer1 = new ImageIcon(this.getClass().getResource("Woodcutter/woodcutter_jump.png")).getImage();
	Image deadPlayer = new ImageIcon(this.getClass().getResource("Woodcutter/woodcutter_death.png")).getImage();
	Image duckPlayer = new ImageIcon(this.getClass().getResource("Woodcutter/woodcutter_duck.png")).getImage();

	/**
	 * Constructs Player
	 */
	public Player() {
		running = true;
		dead = false;
		jumping = false;
		ducking = false;
		x = 10;
		y = 213;
		animationIndex = 1;
	}

	/**
	 *
	 * @return x-coordinate of player
	 */
	public int getX() {
		return x;
	}

	/**
	 *
	 * @return y-coordinate of player
	 */
	public int getY() {
		return y;
	}

	/**
	 * Sets player to dead state
	 */
	public void die() { dead = true; }

	/**
	 * Sets player to alive state
	 */
	public void revive() { dead = false; }	// Added this so user can restart the game

	/**
	 *
	 * @return whether the player is in the dead state or not
	 */
	public boolean isDead() { return dead; }

	// These are used for our JUnit testing

	/**
	 *
	 * @return The players running state
	 */
	public boolean isRunning(){return running;}

	/**
	 *
	 * @return The players ducking state
	 */
	public boolean isDucking(){return ducking;}

	/**
	 *
	 * @return The players jumping state
	 */
	public boolean isJumping(){return jumping;}

	/**
	 * Makes the Player jump by switching the states of
	 * running and jumping and changing the Y-coordinate
	 */
	public void jump() {
		running = false;
		jumping = true;
		y = 180;				// After jumping, change the player's height
	}

	/**
	 * Sets the Player back to the default running position
	 * Resets the running, jumping and ducking states back to its original values
	 * Changes the Y-coordinate back to normal
	 */
	public void defaultPosition() {
		running = true;
		jumping = false;
		ducking = false;
		y = 213;				// After player finishes jumping, set y coordinate back to normal
	}

	/**
	 * Makes the player duck by switching the states of
	 * running and ducking and also changes the Y-coordinate
	 */
	public void duck(){
		running = false;
		ducking = true;
		y = 220;				// After ducking, change players height
	}


	/**
	 * Draws the Player and changes the Image shown depending on
	 * what current state our player is in
	 * @param g Graphics
	 *
	 */
	public void draw(Graphics g) {
		if(running) {
			if(animationIndex == 1) {
			g.drawImage(runPlayer1, getX(), getY() , null);
			}
			else if (animationIndex == 2) {
			g.drawImage(runPlayer2, getX(), getY() , null);
			}
			else if (animationIndex == 3) {
				g.drawImage(runPlayer3, getX(), getY() , null);
			}
			else {
				g.drawImage(runPlayer4, getX(), getY() , null);
			}
			animationIndex++;			// increment animationIndex to get the next animation next time we call draw
			if(animationIndex == 5) {	// if animationIndex is 5, reset it back to 1
				animationIndex = 1;
			}
		}
		else if (dead) {
			g.drawImage(deadPlayer, getX(), getY() , null);
		}
		else if(jumping) {
			g.drawImage(jumpPlayer1, getX(), getY(), null);				// if player is not dead or running, they are jumping
		}
		else if(ducking){
			g.drawImage(duckPlayer, getX(), getY(), null);
		}
		
	}

}
