package j9.Task3;

import javax.swing.*;
import java.awt.*;
import java.awt.image.*;

public class RadioButtonsApp extends JPanel {
    private JRadioButton button1;
    private JRadioButton button2;
    private JRadioButton button3;
    
    private Icon defaultIcon;
    private Icon hoverIcon;
    private Icon pressedIcon;
    private Icon selectedIcon;

    public RadioButtonsApp() {
        setLayout(new GridLayout(3, 1));

        defaultIcon = createIcon(Color.GRAY);
        hoverIcon = createIcon(Color.ORANGE);
        pressedIcon = createIcon(Color.RED);
        selectedIcon = createIcon(Color.GREEN);

        button1 = createRadioButton("Cat 1");
        button2 = createRadioButton("Cat 2");
        button3 = createRadioButton("Cat 3");

        ButtonGroup group = new ButtonGroup();
        group.add(button1);
        group.add(button2);
        group.add(button3);

        add(button1);
        add(button2);
        add(button3);
    }

    private JRadioButton createRadioButton(String text) {
        JRadioButton radioButton = new JRadioButton(text);
        radioButton.setIcon(defaultIcon);
        radioButton.setSelectedIcon(selectedIcon);
        radioButton.setRolloverIcon(hoverIcon);
        radioButton.setPressedIcon(pressedIcon);
        radioButton.setAlignmentX(CENTER_ALIGNMENT);
        return radioButton;
    }

    private Icon createIcon(Color color) {
        int width = 100;
        int height = 100;
        BufferedImage catImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = catImage.createGraphics();
        g2d.setColor(color);
        g2d.fillOval(20, 20, 60, 60);
        g2d.fillPolygon(new int[]{20, 40, 30}, new int[]{20, 20, 0}, 3);
        g2d.fillPolygon(new int[]{60, 80, 70}, new int[]{20, 20, 0}, 3);
        g2d.setColor(Color.WHITE);
        g2d.fillOval(35, 40, 10, 10);
        g2d.fillOval(55, 40, 10, 10);
        g2d.setColor(color);
        g2d.fillOval(38, 43, 5, 5);
        g2d.fillOval(58, 43, 5, 5);
        g2d.drawArc(40, 60, 20, 10, 0, -180);
        return new ImageIcon(catImage);
    }
}