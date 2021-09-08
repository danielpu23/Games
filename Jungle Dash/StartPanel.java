import java.awt.*;
import javax.swing.*;

/**
 * StartPanel class that creates the title screen of the game
 * This class is one of the Views in the MVC design pattern
 */
public class StartPanel extends JPanel {
    private Ground ground;  // Used to create background of title screen

    /**
     * Constructs StartPanel object
     *
     * @param ground ground that will be used as the background
     */
    public StartPanel(Ground ground) {
        this.ground = ground;
        setLayout(new GridLayout(1,1));
    }

    /**
     * Adds the background and text contents of the title screen
     *
     * @param g Graphics object that is used to add text contents
     */
    public void paint(Graphics g) {
        ground.draw(g);
        g.setColor(Color.WHITE);
        // Title
        g.setFont(new Font("Serif", Font.BOLD, 35));
        g.drawString("Jungle Dash!", 225, 90);
        // Start game
        g.setFont(new Font("Serif", Font.BOLD, 20));
        g.drawString("Click anywhere to start game", 190,150);
        // How to play
        g.setFont(new Font("Serif", Font.BOLD, 15));
        g.drawString("How to play: Press S to duck and Space to jump.",160, 200);
        g.drawString("Game is over once you collide with an obstacle.",165, 220);
    }
}
