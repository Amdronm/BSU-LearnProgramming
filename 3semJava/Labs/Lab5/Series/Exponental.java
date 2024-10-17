package Series;

public class Exponental extends Series {
    public Exponental(double initElem, double q) {
        super(initElem, q);
    }

    @Override
    public double calculateJElement(int j) {
        return getInitElem() * Math.pow(getStep(), j);
    }
}