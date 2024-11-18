package j9;

import javax.swing.JFrame;

public class Main {
    public static void main(String[] args) {
        MyFrame frame = new MyFrame("lab j9");        
        frame.setBounds(500, 300, 660, 660);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
