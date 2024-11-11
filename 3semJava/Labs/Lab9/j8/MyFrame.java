import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;

import javax.imageio.ImageIO;

public class MyFrame extends JFrame {
    private JPanel drawPanel;
    private Color penColor = Color.RED;
    private BufferedImage image;
    private Graphics2D g2d;

    @SuppressWarnings("unused")
    public MyFrame(String title) {
        super(title);

        image = new BufferedImage(1600, 1200, BufferedImage.TYPE_INT_RGB);
        g2d = image.createGraphics();
        g2d.setColor(Color.WHITE);
        g2d.fillRect(0, 0, image.getWidth(), image.getHeight());

        drawPanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                g.drawImage(image, 0, 0, null);
            }
        };
        drawPanel.setPreferredSize(new Dimension(1600, 1200));
        drawPanel.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                g2d.setColor(penColor);
                g2d.fillOval(e.getX(), e.getY(), 10, 10);
                drawPanel.repaint();
            }
        });

        JScrollPane scrollPane = new JScrollPane(drawPanel);
        scrollPane.setPreferredSize(new Dimension(800, 600));

        JPanel colorPanel = new JPanel();
        JButton redButton = new JButton("Red");
        JButton greenButton = new JButton("Green");
        JButton blueButton = new JButton("Blue");

        redButton.addActionListener(e -> penColor = Color.RED);
        greenButton.addActionListener(e -> penColor = Color.GREEN);
        blueButton.addActionListener(e -> penColor = Color.BLUE);

        colorPanel.add(redButton);
        colorPanel.add(greenButton);
        colorPanel.add(blueButton);

        JButton saveButton = new JButton("Save");
        JButton openButton = new JButton("Open");

        saveButton.addActionListener(e -> saveImage());
        openButton.addActionListener(e -> openImage());

        colorPanel.add(saveButton);
        colorPanel.add(openButton);

        add(scrollPane, BorderLayout.CENTER);
        add(colorPanel, BorderLayout.SOUTH);
    }

    private void saveImage() {
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

    private void openImage() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(new File("3semJava/Labs/Lab9/j8"));
        if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            try {
                image = ImageIO.read(file);
                g2d = image.createGraphics();
                drawPanel.repaint();
            } catch (IllegalArgumentException ex) {
                JOptionPane.showMessageDialog(this, "File error: " + ex.getMessage());
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Error: " + ex.getMessage());
            }
        }
    }

    public static void main(String[] args) {
        MyFrame app = new MyFrame("Paint 2.0");
        app.setSize(800, 600);
        app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        app.setVisible(true);
    }
}
