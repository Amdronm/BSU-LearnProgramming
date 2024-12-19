import javax.swing.*;

public class View extends JList<Integer> {
    private Stack<Integer> data;
    private DefaultListModel<Integer> dlm;

    public View(DefaultListModel<Integer> dlm, Stack<Integer> data) {
        super(dlm);
        this.dlm = dlm;
        this.data = data;
    }

    public void update() {
        dlm.clear();
        ReverseIterator<Integer> it = data.getReverseIterator();
        for (it.first(); !it.isDone(); it.next()) {
            dlm.addElement(it.getItem());
        }
    }
}
