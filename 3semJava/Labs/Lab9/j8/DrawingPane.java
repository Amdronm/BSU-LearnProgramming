import java.awt.*;
import java.awt.event.*;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.image.*;
import java.io.File;

public class DrawingPane extends JPanel {
    private Color penColor = Color.RED;
    private BufferedImage image;
    private Graphics2D g2d;

    public DrawingPane(BufferedImage bi) {
        image = bi;
        g2d = image.createGraphics();
        g2d.setColor(Color.WHITE);
        g2d.fillRect(0, 0, image.getWidth(), image.getHeight());
        
        setPreferredSize(new Dimension(1600, 1200));
        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                g2d.setColor(penColor);
                g2d.fillOval(e.getX(), e.getY(), 10, 10);
                repaint();
            }
        });
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(image, 0, 0, null);
    }

    public void setColor(Color color) {
        penColor = color;
    }

    public void saveImage() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(new File("3semJava/Labs/Lab9/j8"));
        if (fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            try {
                ImageIO.write(image, "png", file);
            } catch (IllegalArgumentException ex) {
                JOptionPane.showMessageDialog(this, "File error: " + ex.getMessage());
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Error: " + ex.getMessage());
            }
        }
    }

    public void openImage() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(new File("3semJava/Labs/Lab9/j8"));
        if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            try {
                image = ImageIO.read(file);
                g2d = image.createGraphics();
                repaint();
            } catch (IllegalArgumentException ex) {
                JOptionPane.showMessageDialog(this, "File error: " + ex.getMessage());
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Error: " + ex.getMessage());
            }
        }
    }
}
