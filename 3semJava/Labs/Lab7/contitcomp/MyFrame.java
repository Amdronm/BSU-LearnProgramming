package contitcomp;

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
    private Font font;
    private Scanner in;
    private int lowBound;
    private int upBound;

    private JTextArea inArea;
    private JTextArea outArea;
    private JScrollPane inScroll;
    private JScrollPane outScroll;

    MyFrame(String title) {
        super(title);
        font = new Font(Font.SANS_SERIF, Font.ROMAN_BASELINE, 19);
        toys = new TreeSet<Toy>(new ToyComparator());
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
        inScroll = new JScrollPane(inArea);
        outScroll = new JScrollPane(outArea);

        JPanel panel1 = new JPanel(new GridLayout(1, 2));
        panel1.add(inScroll);
        panel1.add(outScroll);
        add(panel1);

        JButton openButton = new JButton("Open file");
        openButton.setFont(font);
        openButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ev) {
                JFileChooser fileChooser = new JFileChooser(new File("3semJava/Labs/Lab7/contitcomp/"));
                int res = fileChooser.showOpenDialog(panel1);
                if (res == JFileChooser.APPROVE_OPTION) {
                    File file = fileChooser.getSelectedFile();
                    try {
                        in = new Scanner(file);
                        readToys(in);
                        printToys(inArea);
                        printToys(outArea);
                    } catch (FileNotFoundException e) {
                        outArea.setText(e.getMessage());
                    } catch (Exception e) {
                        outArea.setText(e.getMessage());
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
                    String[] arr = m.split("[ ]+", 2);
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
                    JFileChooser fileChooser = new JFileChooser(new File("3semJava/Labs/Lab7/contitcomp/"));
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

    public void readToys(Scanner in) throws Exception {
        String s;
        while (in.hasNext()) {
            s = in.nextLine();
            Toy toy = new Toy();
            try {
                toy.fromString(s);
            } catch (Exception e) {
                JOptionPane.showMessageDialog(this, e.getMessage(), "ERROR!", JOptionPane.ERROR_MESSAGE);
                throw new Exception("File of Wrong format");
            }            
            toys.add(toy);
        }
    }

    @Override
    public Iterator<Toy> iterator() {
        return toys.iterator();
    }

    public void printToys(JTextArea out) {
        StringBuilder sb = new StringBuilder();
        Iterator<Toy> it = toys.iterator();
        Toy toy = new Toy();
        while (it.hasNext()) {
            toy = it.next();
            if (toy.getLowBoundAge() >= lowBound && toy.getUpBoundAge() <= upBound) {
                sb.append(toy.toString());
                sb.append('\n');
            }
        }
        out.setText(sb.toString());
    }

    public void writeToFile(File file) throws FileNotFoundException {
        StringBuilder sb = new StringBuilder();
        Iterator<Toy> it = toys.iterator();
        Toy toy = new Toy();
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