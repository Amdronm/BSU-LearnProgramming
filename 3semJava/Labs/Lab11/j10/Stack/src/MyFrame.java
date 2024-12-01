import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MyFrame extends JFrame {
    private Stack<String> stack;
    private JList<String> list;
    private DefaultListModel<String> listModel;
    private JButton pushButton;
    private JButton popButton;
    private JTextField field;

    public MyFrame(String title) {
        super(title);
        stack = new Stack<>();
        listModel = new DefaultListModel<>();
        list = new JList<>(listModel);

        pushButton = new JButton("PUSH");
        popButton = new JButton("POP");
        field = new JTextField(10);

        pushButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String value = field.getText();
                if (!value.isEmpty()) {
                    stack.push(value);
                    updateList();
                    field.setText("");
                }
            }
        });

        popButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!stack.isEmpty()) {
                    field.setText(stack.pop());
                    updateList();
                }
            }
        });

        JPanel panel = new JPanel();
        panel.add(new JLabel("VALUE: "));
        panel.add(field);
        panel.add(pushButton);
        panel.add(popButton);

        add(new JScrollPane(list), BorderLayout.CENTER);
        add(panel, BorderLayout.SOUTH);
    }

    private void updateList() {
        listModel.clear();
        for (ReverseIterator<String> it = stack.getReverseIterator(); !it.isDone(); it.next()) {
            listModel.addElement(it.getItem());
        }
    }

    public static void main(String[] args) {
        MyFrame app = new MyFrame("Stack");
        app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        app.setBounds(50, 200, 400, 600);
        app.setVisible(true);
    }
}
