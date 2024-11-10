package task1;

import javax.swing.*;

import java.awt.*;
import java.awt.event.*;

public class MyFrame extends JFrame {
    private final int WIDTH = 600;
    private final int HEIGHT = 450;
    private JTextField field;
    private JButton button;
    private Point p;
    private Point pb;

    public MyFrame(String title) {
        super(title);
        setSize(WIDTH, HEIGHT);
        setResizable(false);
        setLayout(null);

        addMouseMotionListener(new MouseMotionListener() {
            @Override
            public void mouseDragged(MouseEvent e) {
                showCoords(e);
            }

            @Override
            public void mouseMoved(MouseEvent e) {
                showCoords(e);
            }
        });

        button = new JButton("Just button");
        button.setBounds(WIDTH / 2 - 100, HEIGHT - 100, 200, 40);
        add(button);

        p = new Point(button.getX(), button.getY());
        pb = new Point(p);

        button.addMouseMotionListener(new MouseMotionListener() {
            @Override
            public void mouseMoved(MouseEvent e) {
                field.setText("(" + e.getXOnScreen() + ", " + e.getYOnScreen() + ")");
                showCoords(e);
            }

            @Override
            public void mouseDragged(MouseEvent e) {
                showCoords(e);
                if (e.isControlDown()) {
                    moveButton(e);
                }
            }
        });

        button.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                pb.move(e.getX() + 6, e.getY() + 26);
            }
        });
        
        button.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {   
                if (e.getKeyCode() == KeyEvent.VK_BACK_SPACE) {
                    String text = button.getText();
                    if (text.length() > 0) {
                        button.setText(text.substring(0, text.length() - 1));
                    }
                } else if (Character.isLetterOrDigit(e.getKeyCode()) || "!@#$%^&*()_+-=[]{}|;':\\\",.<>/? ".indexOf(e.getKeyChar()) != -1) {
                    button.setText(button.getText() + e.getKeyChar());
                }
            }
        });

        field = new JTextField(30);
        field.setBounds(WIDTH / 2 - 30, 10, 60, 20);
        add(field);

        field.addMouseMotionListener(new MouseMotionListener() {
            @Override
            public void mouseDragged(MouseEvent e) {
                showCoords(e);
            }

            @Override
            public void mouseMoved(MouseEvent e) {
                showCoords(e);
            }
        });
    }

    private void moveButton(MouseEvent e) {
        p.move(e.getXOnScreen() - this.getX() - pb.x, e.getYOnScreen() - this.getY() - pb.y);
        button.setLocation(p);
    }

    private void showCoords(MouseEvent e) {
        field.setText("(" + (e.getXOnScreen() - this.getX()) + ", " + (e.getYOnScreen() - this.getY()) + ")");
    }

    public static void main(String[] args) {
        MyFrame frame = new MyFrame("Button pos");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        frame.setSize(600, 450);
    }
}
