package j9.Task1;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JPanel;
import java.awt.event.*;
import java.awt.*;

public class ButtonPanel extends JPanel {
    private JButton leftButton;
    private JButton rightButton;

    public ButtonPanel(JList<String> leftList, JList<String> rightList, DefaultListModel<String> leftListModel, DefaultListModel<String> rightListModel) {
        rightButton = new JButton("->");
        leftButton = new JButton("<-");

        rightButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                moveItems(leftList, rightList, leftListModel, rightListModel);
            }
        });

        leftButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                moveItems(rightList, leftList, rightListModel, leftListModel);
            }
        });
        
        setLayout(new BorderLayout());
        add(rightButton, BorderLayout.NORTH);
        add(leftButton, BorderLayout.SOUTH);
    }
    
    private void moveItems(JList<String> sourceList, JList<String> targetList, DefaultListModel<String> sourceModel, DefaultListModel<String> targetModel) {
        for (String selectedValue : sourceList.getSelectedValuesList()) {
            targetModel.addElement(selectedValue);
            sourceModel.removeElement(selectedValue);
        }
    }
}
