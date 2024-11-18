package j9.Task2;

import javax.swing.*;
import java.awt.*;

public class GridButtons extends JPanel {
    private static final int GRID_ROWS = 6;
    private static final int GRID_COLS = 6;

    public GridButtons() {
        setLayout(new GridLayout(GRID_ROWS, GRID_COLS));

        ButtonMouseListener buttonMouseListener = new ButtonMouseListener();
        
        for (int i = 0; i < GRID_ROWS * GRID_COLS; i++) {
            JButton button = new JButton(String.valueOf(i + 1));
            button.addMouseListener(buttonMouseListener);
            add(button);
        }
    }
}
