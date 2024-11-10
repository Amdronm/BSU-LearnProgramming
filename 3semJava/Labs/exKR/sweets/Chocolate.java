package sweets;

public class Chocolate extends Sweet {
    private Type type;
    private boolean hasFilling;

    public Chocolate(String name, double sugar, double weight, double price, Type type, boolean hasFilling) {
        super(name, sugar, weight, price);
        this.type = type;
        this.hasFilling = hasFilling;
    }

    public Type getType() {
        return type;
    }

    public boolean isHasFilling() {
        return hasFilling;
    }

    @Override
    public String toString() {
        return "Choco:" + super.toString() + type + ", " + hasFilling;
    }

    public enum Type {
        DARK,
        MILK,
        WHITE
    }

    public static Chocolate parseCandy(String s) throws Exception {
        String[] toks = s.split(", ");
        if (toks.length != 6) {
            throw new Exception("invalid String to parse Chocolate");
        }
        String name = toks[0];
        double sugar = Double.parseDouble(toks[1]);
        double weight = Double.parseDouble(toks[2]);
        double price = Double.parseDouble(toks[3]);
        Type type = Type.valueOf(toks[4]);
        boolean hasFilling = Boolean.parseBoolean(toks[5]);
        return new Chocolate(name, sugar, weight, price, type, hasFilling);
    }
}