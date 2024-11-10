package sweets;

public class Lolypop extends Sweet {
    private Color color;

    public Lolypop(String name, double sugar, double weight, double price, Color color) {
        super(name, sugar, weight, price);
        this.color = color;
    }

    public Color getColor() {
        return color;
    }

    @Override
    public String toString() {
        return "Lolypop:" + super.toString() + color;
    }

    public enum Color {
        RED, YELLOW, BLUE, GREEN
    }

    public static Lolypop parseLolypop(String s) throws Exception {
        String[] toks = s.split(", ");
        if (toks.length != 6) {
            throw new Exception("invalid String to parse Chocolate");
        }
        String name = toks[0];
        double sugar = Double.parseDouble(toks[1]);
        double weight = Double.parseDouble(toks[2]);
        double price = Double.parseDouble(toks[3]);
        Color color = Color.valueOf(toks[4]);
        return new Lolypop(name, sugar, weight, price, color);
    }
}
