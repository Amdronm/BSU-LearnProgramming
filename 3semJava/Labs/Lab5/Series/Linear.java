package Series;

import java.io.File;
import java.io.FileNotFoundException;

public class Linear extends Series {
    public Linear(double initElem, double d) {
        super(initElem, d);
    }

    @Override
    public double calculateJElement(int j) {
        return getInitElem() + j * getStep();
    }

    public static void main(String[] args) throws FileNotFoundException {
        Linear lin = new Linear(0, 1);
        File output = new File("3semJava\\Labs\\Lab5\\GraphicsInterface\\output.txt");
        lin.saveToFile(output);
    }
}