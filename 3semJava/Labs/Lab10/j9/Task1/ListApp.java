package j9.Task1;

import javax.swing.*;
import java.awt.*;

public class ListApp extends JPanel {
    private JList<String> leftList;
    private JList<String> rightList;
    private DefaultListModel<String> leftListModel;
    private DefaultListModel<String> rightListModel;
    private ButtonPanel panel;

    public ListApp() {
        setLayout(new BorderLayout());

        leftListModel = new DefaultListModel<>();
        rightListModel = new DefaultListModel<>();

        for (int i = 1; i <= 13; i++) {
            leftListModel.addElement("Element " + i);
        }

        leftList = new JList<>(leftListModel);
        rightList = new JList<>(rightListModel);

        add(new JScrollPane(leftList), BorderLayout.WEST);
        add(new JScrollPane(rightList), BorderLayout.EAST);

        panel = new ButtonPanel(leftList, rightList, leftListModel, rightListModel);
        
        add(panel, BorderLayout.CENTER);
    }
}
