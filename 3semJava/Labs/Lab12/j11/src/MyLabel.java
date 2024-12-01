import javax.swing.*;
import java.awt.*;

public class MyLabel extends JLabel implements Observer {
    public MyLabel() {
        super();
        setFont(new Font(Font.MONOSPACED, Font.BOLD, 30));
    }

    @Override
    public void update(Subject s) {
        MyListener ms = (MyListener) s;
        this.setText(ms.getCharacter().toString());
    }
}
