import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.List;

public class MyListener extends KeyAdapter implements Subject {
    private List<Observer> list = new ArrayList<>();
    private Character character;

    @Override
    public void attach(Observer obs) {
        list.add(obs);
    }

    @Override
    public void detach(Observer obs) {
        list.remove(obs);
    }

    @Override
    public void notifyObserver() {
        for (Observer obs : list) {
            obs.update(this);
        }
    }

    @Override
    public void keyPressed(KeyEvent e) {
        this.character = e.getKeyChar();
        this.notifyObserver();
    }

    public Character getCharacter() {
        return character;
    }
}
