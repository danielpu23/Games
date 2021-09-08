import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;

/**
 * Class that represents a stump obstacle that the user must jump over to not collide with it
 * Represents one of the Models in the MVC design pattern
 */
public class Stump implements Obstacle {
	private int x;
	private int y;

	/**
	 * Constructs the Stump object
	 */
	public Stump() {
		x = 680;
		y = 210;
	}



	/**
	 * Checks to see if Stump is offscreen
	 *
	 * @return if the Stump is out of bounds
	 */
	@Override
	public boolean outOfBounds() {
		if (x < -20) {		// If most of the stump is offscreen, it is out of bounds
			return true;
		}
		return false;
	}

	/**
	 * Draws the Stump
	 *
	 * @param g Graphics object that draws the stump
	 */
	@Override
	public void draw(Graphics g) {
		Image stumpImage = new ImageIcon(this.getClass().getResource("stump.png")).getImage();
		g.drawImage(stumpImage, x, y, null);
	}

	/**
	 * Updates the x-position of the Stump
	 */
	@Override
	public void update() {
		x -= 28;
	}

	/**
	 * Checks if Player's x and y-coordinates are approximately at the Stumps x and y-coordinates to check and return if they collided
	 *
	 * @param playerX the Player's x-coordinate
	 * @param playerY the Player's y-coordinate
	 */
	public boolean checkCollision(int playerX, int playerY) {
		if ((Math.abs(playerX - x)) <= 24 && (playerY > y)) { // If player's model is in the hitbox of stump,
			return true;									  // they collided
		}
		return false;
	}

	// Note: The following three methods are used for JUnit testing purposes
	/**
	 * Returns the x-coordinate of Stump
	 *
	 * @return x-coordinate of Stump
	 */
	public int getX(){ return x;}

	/**
	 * Returns the y-coordinate of Stump
	 *
	 * @return y-coordinate of Stump
	 */
	public int getY(){ return y;}

	/**
	 * Sets x-coordinate of Stump to parameter's x
	 *
	 * @param x x-coordinate to set Stump's x-coordinate to
	 */
	public void setX(int x){ this.x = x;}
}
