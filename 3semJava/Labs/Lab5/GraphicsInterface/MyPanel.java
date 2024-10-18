package GraphicsInterface;

import Series.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MyPanel extends JPanel {
    public MyPanel(Linear linear) {
        setLayout(new GridLayout(2, 1));

        JTextField text = new JTextField(linear.toString());
        text.setFont(new Font("Courier", Font.BOLD | Font.ITALIC, 20));
        text.setHorizontalAlignment(JTextField.CENTER);
        this.add(text);

        JButton buttonChange = new JButton("Change");
        add(buttonChange);
        buttonChange.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                
            }
        });
        // add(buttonChange);
        // buttonChange.addActionListener(new ActionListener() {
        //     @Override
        //     public void actionPerformed(ActionEvent e) {
        //         student.setAge(student.getAge() + 1);
        //         text.setText(student.toString());
        //     }
        // });
    }
    public MyPanel(Series s) {
        
    }
}
