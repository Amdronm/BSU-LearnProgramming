package auto;

public abstract class Auto {
    private String name;
    private int color;
    private int rate;

    public Auto(String name, int color, int rate) {
        this.name = name;
        this.color = color;
        this.rate = rate;
    }

    public int getColor() {
        return color;
    }

    public String getName() {
        return name;
    }

    public int getRate() {
        return rate;
    }
    
    public abstract int countPrice();
}
