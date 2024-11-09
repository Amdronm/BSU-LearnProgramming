package auto;

public class Bus extends Auto {
    private static final int K1 = 4;
    private static final int K2 = 5;
    private static final int K3 = 2;
    
    private int places;
    private int doors;

    public Bus(String name, int color, int rate, int places, int doors) {
        super(name, color, rate);
        this.places = places;
        this.doors = doors;
    }

    @Override
    public int countPrice() {
        return K1 * super.getRate() * doors + K2 * places - K3 * super.getColor();
    }
}
