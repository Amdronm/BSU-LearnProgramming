package GraphicsInterface;

import javax.swing.*;
import java.awt.*;

public class MyPanel extends JPanel {
    private JLabel label;
    private JTextField textField;

    public MyPanel() {
        setLayout(new GridLayout(1, 2));
        label = new JLabel();
        label.setHorizontalAlignment(JLabel.CENTER);
        label.setFont(new Font(Font.MONOSPACED, Font.BOLD, 23));
        add(label);
        textField = new JTextField(10);
        textField.setFont(new Font(Font.DIALOG, Font.TRUETYPE_FONT, 23));
        add(textField);
    }

    String getText() {
        return textField.getText();
    }

    public void setLabelText(String text) {
        label.setText(text);
    }

    public void setFieldText(String text) {
        textField.setText(text);
    }
}
