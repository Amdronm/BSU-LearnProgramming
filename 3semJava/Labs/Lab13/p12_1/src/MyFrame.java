import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MyFrame extends JFrame {
    private Stack<Integer> stack;
    private JList<Integer> list;
    private DefaultListModel<Integer> listModel;
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

        pushButton.addActionListener(_ -> {
            try {
                int value = Integer.parseInt(field.getText());
                stack.push(value);
                updateList();
                field.setText("");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(field, ex.getMessage(), "NUMBER FORMAT EXCEPTION", JOptionPane.ERROR_MESSAGE);
            }
        });

        popButton.addActionListener(_ -> {
            if (!stack.isEmpty()) {
                field.setText(stack.pop().toString());
                updateList();
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
        for (ReverseIterator<Integer> it = stack.getReverseIterator(); !it.isDone(); it.next()) {
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
