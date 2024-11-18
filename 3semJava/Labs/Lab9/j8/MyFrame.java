import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class MyFrame extends JFrame {
    private DrawingPane drawPanel;
    private JPanel colorPanel;
    private BufferedImage image;
    private Graphics2D g2d;

    @SuppressWarnings("unused")
    public MyFrame(String title) {
        super(title);

        image = new BufferedImage(1600, 1200, BufferedImage.TYPE_INT_RGB);
        g2d = image.createGraphics();
        g2d.setColor(Color.WHITE);
        g2d.fillRect(0, 0, image.getWidth(), image.getHeight());

        drawPanel = new DrawingPane(image);

        JScrollPane scrollPane = new JScrollPane(drawPanel);
        scrollPane.setPreferredSize(new Dimension(800, 600));

        colorPanel = new JPanel();
        JButton redButton = new JButton("Red");
        JButton greenButton = new JButton("Green");
        JButton blueButton = new JButton("Blue");

        redButton.addActionListener(e -> drawPanel.setColor(Color.RED));
        greenButton.addActionListener(e -> drawPanel.setColor(Color.GREEN));
        blueButton.addActionListener(e -> drawPanel.setColor(Color.BLUE));

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
        drawPanel.saveImage();
    }

    private void openImage() {
        drawPanel.openImage();
    }

    public static void main(String[] args) {
        MyFrame app = new MyFrame("Paint 2.0");
        app.setSize(800, 600);
        app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        app.setVisible(true);
    }
}
