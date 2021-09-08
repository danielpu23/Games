import java.awt.Graphics;

public interface Obstacle {
	boolean outOfBounds();
	void draw(Graphics g);
	void update();
	boolean checkCollision(int x, int y);
}
