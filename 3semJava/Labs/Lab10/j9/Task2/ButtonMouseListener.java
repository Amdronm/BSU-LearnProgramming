package j9.Task2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ButtonMouseListener extends MouseAdapter {
    private Color originalColor;
    private String originalText;

    @Override
    public void mouseEntered(MouseEvent e) {
        JButton button = (JButton) e.getSource();
        originalColor = button.getBackground();
        button.setBackground(new Color(0x58f5b4));
    }

    @Override
    public void mouseExited(MouseEvent e) {
        JButton button = (JButton) e.getSource();
        button.setBackground(originalColor);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        JButton button = (JButton) e.getSource();
        originalText = button.getText();
        button.setText("Clicked!");
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        JButton button = (JButton) e.getSource();
        button.setText(originalText);
    }
}
