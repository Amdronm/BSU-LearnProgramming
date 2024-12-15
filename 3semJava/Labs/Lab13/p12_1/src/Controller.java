import javax.swing.*;
import java.awt.*;

public class Controller extends JFrame {
    private Stack<Integer> model;
    private View view;
    private JButton pushButton;
    private JButton popButton;
    private JTextField field;

    public Controller(String title) {
        super(title);
        model = new Stack<>();
        view = new View(new DefaultListModel<>(), model);

        pushButton = new JButton("PUSH");
        popButton = new JButton("POP");
        field = new JTextField(10);

        pushButton.addActionListener(_ -> {
            try {
                int value = Integer.parseInt(field.getText());
                model.push(value);
                view.update();
                field.setText("");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(field, ex.getMessage(), "NUMBER FORMAT EXCEPTION", JOptionPane.ERROR_MESSAGE);
            }
        });

        popButton.addActionListener(_ -> {
            if (!model.isEmpty()) {
                field.setText(model.pop().toString());
                view.update();
            }
        });

        JPanel panel = new JPanel();
        panel.add(new JLabel("VALUE: "));
        panel.add(field);
        panel.add(pushButton);
        panel.add(popButton);

        add(new JScrollPane(view), BorderLayout.CENTER);
        add(panel, BorderLayout.SOUTH);
    }

    public static void main(String[] args) {
        MyFrame app = new MyFrame("Stack");
        app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        app.setBounds(50, 200, 400, 600);
        app.setVisible(true);
    }
}
