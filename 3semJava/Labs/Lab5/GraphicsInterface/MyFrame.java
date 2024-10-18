package GraphicsInterface;

import Series.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class MyFrame extends JFrame {
    private Series series;
    private Font font;

    private MyPanel initPanel;
    private MyPanel stepPanel;
    private MyPanel elemPanel;
    private JPanel buttonsPanel;
    private JTextArea textArea;
    private JButton saveButton;
    private JTextField fileField;

    public MyFrame(String title) {
        super(title);

        series = new Linear(0, 1);

        font = new Font(Font.DIALOG, Font.TRUETYPE_FONT, 23);

        setLayout(new GridLayout(7, 1));
        initPanel = new MyPanel();
        initPanel.setLabelText("Initial element = ");
        initPanel.setFieldText("0");
        add(initPanel);

        stepPanel = new MyPanel();
        stepPanel.setLabelText("Step of series = ");
        stepPanel.setFieldText("6");
        add(stepPanel);

        elemPanel = new MyPanel();
        elemPanel.setLabelText("Amount of elements = ");
        elemPanel.setFieldText("6");
        add(elemPanel);

        buttonsPanel = new JPanel(new GridLayout(1, 2));
        JButton linearButton = new JButton("Create linear");
        linearButton.setFont(font);
        linearButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                try {                    
                    series = new Linear(Double.valueOf(initPanel.getText()), Double.valueOf(stepPanel.getText()));
                    int j = Integer.valueOf(elemPanel.getText());
                    if (j < 0) {
                        throw new Exception("AMOUNT OF ELEMENTS MUST BE NON-NEGATIVE!");
                    }
                    textArea.setText(series.toString(j));
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(MyFrame.this, "Wrong number format!", "Try again!", JOptionPane.ERROR_MESSAGE);
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(MyFrame.this, e.getMessage(), "WRONG", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        buttonsPanel.add(linearButton);

        JButton exponentalButton = new JButton("Create exponental");
        exponentalButton.setFont(font);
        exponentalButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                try {                    
                    series = new Exponental(Double.valueOf(initPanel.getText()), Double.valueOf(stepPanel.getText()));
                    int j = Integer.valueOf(elemPanel.getText());
                    if (j < 0) {
                        throw new Exception("AMOUNT OF ELEMENTS MUST BE NON-NEGATIVE!");
                    }
                    textArea.setText(series.toString(j));
                } catch (NumberFormatException e) {
                    JOptionPane.showMessageDialog(MyFrame.this, "Wrong number format!", "Try again!", JOptionPane.ERROR_MESSAGE);
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(MyFrame.this, e.getMessage(), "WRONG", JOptionPane.ERROR_MESSAGE);
                }
                
            }
        });
        buttonsPanel.add(exponentalButton);
        add(buttonsPanel);

        textArea = new JTextArea();
        textArea.setFont(font);
        textArea.setText("Your series will appear here!");
        textArea.setEditable(false);
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);
        JScrollPane scroll = new JScrollPane(textArea);
        add(scroll);
        
        saveButton = new JButton();
        saveButton.setFont(font);
        saveButton.setText("SAVE SERIES TO FILE!");
        saveButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                try {                    
                    File file = new File("3semJava\\Labs\\Lab5\\GraphicsInterface\\" + fileField.getText());
                    series.saveToFile(file);
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(MyFrame.this, e.getMessage(), "WRONG", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        add(saveButton);

        fileField = new JTextField();
        fileField.setFont(font);
        fileField.setText("output.txt");
        fileField.setHorizontalAlignment(JTextField.CENTER);
        add(fileField);
    }
}