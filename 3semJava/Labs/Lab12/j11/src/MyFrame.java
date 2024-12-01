import javax.swing.*;
import java.awt.*;

public class MyFrame extends JFrame {
    private MyListener subj;
    private MyLabel label;
    private MyLogLabel panel;

    public MyFrame(String title) {
        super(title);
        setLayout(new GridLayout(1, 2));
        label = new MyLabel();
        label.setText("I am here!");
        panel = new MyLogLabel();

        subj = new MyListener();
        subj.attach(label);
        subj.attach(panel);
        addKeyListener(subj);

        add(label);
        add(new JScrollPane(panel));
    }

    public static void main(String[] args) {
        MyFrame app = new MyFrame("Observer impl");
        app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        app.setBounds(100, 400, 600, 200);
        app.setVisible(true);
    }
}
