package contitcomp;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.util.Set;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class MyFrame extends JFrame {
    private Set<Toy> toys;

    private JTextArea inArea;
    private JTextArea outArea;
    private JScrollPane inScroll;
    private JScrollPane outScroll;
    private JButton openButton;

    MyFrame(String title) {
        super(title);
        
        setLayout(new BorderLayout(0, 10));

        inArea = new JTextArea();
        outArea = new JTextArea();
        inScroll = new JScrollPane(inArea);
        outScroll = new JScrollPane(outArea);

        JPanel panel = new JPanel(new GridLayout(1, 2));
        panel.add(inScroll);
        panel.add(outScroll);
        add(panel);

        openButton = new JButton("Open file");
        add(openButton, BorderLayout.SOUTH);

    }
}
