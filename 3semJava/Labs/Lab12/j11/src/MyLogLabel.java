import javax.swing.*;
import java.awt.*;

public class MyLogLabel extends JLabel implements Observer {
    public MyLogLabel() {
        super();
        this.setFont(new Font(Font.MONOSPACED, Font.BOLD, 30));
        this.setSize(300, 300);
        this.setDoubleBuffered(true);
    }

    @Override
    public void update(Subject s) {
        MyListener ml = (MyListener) s;
        this.setText(this.getText() + ml.getCharacter().toString());
    }
}
