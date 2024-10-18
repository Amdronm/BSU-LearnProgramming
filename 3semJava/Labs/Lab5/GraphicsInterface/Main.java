package GraphicsInterface;

import javax.swing.JFrame;

public class Main {
    public static void main(String[] args) {
        JFrame fr = new MyFrame("Series");
        fr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        fr.setBounds(600, 300, 600, 400);
        fr.setVisible(true);
    }
}
