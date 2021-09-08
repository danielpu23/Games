import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;

/**
 * Class that represents the display and animation of the ground and background of the game
 * Represents one of the Models in the MVC design pattern
 */
public class Ground {
	private int x;		  // Determines how far along the screen each groundImage should be drawn
	private int y;		  // y-coordinate to draw each groundImage
	private int width;        // Represents how wide each groundImage is
	Image groundImage = new ImageIcon(this.getClass().getResource("Ground.png")).getImage();         // Image for the ground
	Image backgroundImage = new ImageIcon(this.getClass().getResource("Background.png")).getImage(); // Image for the background

	/**
	 * Constructs the Ground object
	 */
	public Ground() {
		x = 0;
		y = 240;   
		width = 384;           
	}



	/**
	 * Updates the x-position of each groundImage to be based around, in order to create the animation of the ground moving forward
	 */
	public void update() {
		x += 12;		// Add 12 to x (1/128 the size of the entire ground). The number 12 is arbitrary, and was picked to make ground animation look nice
		if (x >= 1152) {		// If x exceeds the x-coordinate of the 4th ground image, which will represent the edge of the screen, reset it to 0
			x = 0;
		}
	}

	/**
	 * Draws the background, which takes up the entire space of the screen
	 * Also draws each individual groundImage, which requires 5 to fill the entire bottom of the screen
	 * Each groundImage will be its width away from each other and be oriented along the screen by subtracting x from it
	 *
	 * @param g Graphics object that draws the background and ground
	 */
	public void draw(Graphics g) {
		g.drawImage(backgroundImage, 0, 0, null);  
		g.drawImage(groundImage, 0 - x, y, null);         
		g.drawImage(groundImage, width - x, y, null);
		g.drawImage(groundImage, width*2 - x, y, null);
		g.drawImage(groundImage, width*3 - x, y, null);
		g.drawImage(groundImage, width*4 - x, y, null);
	}
}
