package j9;

import j9.Task1.*;
import j9.Task2.*;
import j9.Task3.*;

import javax.swing.*;

public class MyFrame extends JFrame {
    public MyFrame(String title) {
        super(title);

        ListApp tab1 =  new ListApp();
        GridButtons tab2 = new GridButtons();
        RadioButtonsApp tab3 = new RadioButtonsApp();

        JTabbedPane pane =  new JTabbedPane(JTabbedPane.TOP);
        pane.addTab("move elements", tab1);
        pane.addTab("table of buttons", tab2);
        pane.addTab("Radio buttons", tab3);
        add(pane);
    }
}
