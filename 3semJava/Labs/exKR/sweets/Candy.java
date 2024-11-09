package sweets;

public class Candy {
    private String name;
    private double sugar;
    private double weight;
    private double price;

    public Candy(String name, double sugar, double weight, double price) {
        this.name = name;
        this.sugar = sugar;
        this.weight = weight;
        this.price = price;
    }

    public String getName() {
        return name;
    }

    public double getSugar() {
        return sugar;
    }

    public double getWeight() {
        return weight;
    }

    public double getPrice() {
        return price;
    }

    @Override
    public String toString() {
        return name + ", " + sugar + ", " + weight + ", " + price;
    }
}
