package auto;

public class Car extends Auto {
    private static final int K1 = 2;
    private static final int K2 = 5;

    private int speed;

    public Car(String name, int color, int rate, int speed) {
        super(name, color, rate);
        this.speed = speed;
    }

    @Override
    public int countPrice() {
        return K1 * super.getRate() * speed - K2 * super.getColor();
    }
}
