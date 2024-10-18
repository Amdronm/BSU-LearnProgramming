package GraphicsInterface;

import Series.*;

import javax.swing.JFrame;

public class MyFrame extends JFrame {
    public MyFrame(String title) {
        super(title);

        MyPanel panel = new MyPanel(new Linear(0 , 1));
        add(panel);
    }
}
