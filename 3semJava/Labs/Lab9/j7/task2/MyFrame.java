package task2;

import javax.swing.*;
import java.awt.event.*;;

public class MyFrame extends JFrame {

    private JButton yesButton;
    private JButton noButton;
    private JLabel label;

    public MyFrame() {
        setLayout(null);

        label = new JLabel("Is your scholarship enough to live?");
        label.setBounds(150, 50, 300, 30);
        add(label);

        yesButton = new JButton("Yes");
        yesButton.setBounds(150, 100, 100, 50);
        yesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(null, "That is alright. It will get worse)");
            }
        });
        add(yesButton);

        noButton = new JButton("No");
        noButton.setBounds(300, 100, 100, 50);
        noButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                int x = (int) (Math.random() * (getWidth() - noButton.getWidth()));
                int y = (int) (Math.random() * (getHeight() - noButton.getHeight()));
                noButton.setLocation(x, y);
            }
        });
        add(noButton);
    }

    public static void main(String[] args) {
        MyFrame frame = new MyFrame();
        frame.setTitle("Are you happy...");
        frame.setBounds(600, 400, 600, 450);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}