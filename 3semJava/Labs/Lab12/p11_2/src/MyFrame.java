import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Font;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.TreeSet;
import java.util.Iterator;
import java.util.Scanner;

import javax.swing.*;

public class MyFrame extends JFrame implements Iterable<Toy> {
    private TreeSet<Toy> toys;
    private Scanner in;
    private int lowBound;
    private int upBound;

    private JTextArea inArea;
    private JTextArea outArea;

    MyFrame(String title) {
        super(title);
        Font font = new Font(Font.SANS_SERIF, Font.PLAIN, 19);
        toys = new TreeSet<>(new ToyComparator());
        lowBound = 0;
        upBound = 100;
        
        setLayout(new BorderLayout(0, 10));

        inArea = new JTextArea();
        inArea.setFont(font);
        inArea.setLineWrap(true);
        inArea.setEditable(false);
        outArea = new JTextArea();
        outArea.setFont(font);
        outArea.setLineWrap(true);
        outArea.setEditable(false);
        JScrollPane inScroll = new JScrollPane(inArea);
        JScrollPane outScroll = new JScrollPane(outArea);

        JPanel panel1 = new JPanel(new GridLayout(1, 2));
        panel1.add(inScroll);
        panel1.add(outScroll);
        add(panel1);

        JButton openButton = new JButton("Open file");
        openButton.setFont(font);
        openButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ev) {
                JFileChooser fileChooser = new JFileChooser(new File("src/input.txt"));
                int res = fileChooser.showOpenDialog(panel1);
                if (res == JFileChooser.APPROVE_OPTION) {
                    File file = fileChooser.getSelectedFile();
                    try {
                        in = new Scanner(file);
//                        ParserToysNoStream pn = new ParserToysNoStream();
//                        toys = pn.parseToys(in);
                        ParserToyStream ps = new ParserToyStream();
                        toys = ps.parseToys(in);
                        printToys(inArea);
                        printToys(outArea);
                    } catch (Exception e) {
                        JOptionPane.showMessageDialog(panel1, e.getMessage(), "Number format exception", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });

        JButton addButton = new JButton("Add toy");
        addButton.setFont(font);
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ev) {
                try {
                    String m = JOptionPane.showInputDialog("Print your toy");
                    Toy t = new Toy();
                    t.fromString(m);
                    toys.add(t);
                    printToys(outArea);
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(panel1, e.getMessage(), "Number format exception", JOptionPane.ERROR_MESSAGE);
                } catch (Exception e) {
                }
            }
        });

        JButton setButton = new JButton("Set age bounds");
        setButton.setFont(font);
        setButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ev) {
                try {
                    String m = JOptionPane.showInputDialog("Set age bounds", "0 100");
                    String[] arr = m.split(" +", 2);
                    lowBound = Integer.parseInt(arr[0]);
                    upBound = Integer.parseInt(arr[1]);
                    printToys(outArea);
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(panel1, "2 Integers required", "ERROR!", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        JButton saveButton = new JButton("Save to file");
        saveButton.setFont(font);
        saveButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ev) {
                try {
                    JFileChooser fileChooser = new JFileChooser(new File("src/input.txt"));
                    int res = fileChooser.showOpenDialog(panel1);
                    if (res == JFileChooser.APPROVE_OPTION) {
                        File file = fileChooser.getSelectedFile();
                        writeToFile(file);
                    }
                
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(panel1, e.getMessage(), "ERROR!", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        JPanel panel2 = new JPanel(new GridLayout(1, 4));
        panel2.add(openButton);
        panel2.add(addButton);
        panel2.add(setButton);
        panel2.add(saveButton);
        add(panel2, BorderLayout.SOUTH);
    }

    @Override
    public Iterator<Toy> iterator() {
        return toys.iterator();
    }

    public void printToys(JTextArea out) {
        StringBuilder sb = new StringBuilder();
        Iterator<Toy> it = toys.iterator();
        Toy toy;
        while (it.hasNext()) {
            toy = it.next();
            if (toy.getLowBoundAge() >= lowBound && toy.getUpBoundAge() <= upBound) {
                sb.append(toy);
                sb.append('\n');
            }
        }
        out.setText(sb.toString());
    }

    public void writeToFile(File file) throws FileNotFoundException {
        StringBuilder sb = new StringBuilder();
        Iterator<Toy> it = toys.iterator();
        Toy toy;
        while (it.hasNext()) {
            toy = it.next();
            if (toy.getLowBoundAge() >= lowBound && toy.getUpBoundAge() <= upBound) {
                sb.append(toy.toFileString());
                sb.append('\n');
            }
        }
        PrintWriter out = new PrintWriter(file);
        out.write(sb.toString());
        out.close();
    }
}