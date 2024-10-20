package contitcomp;

public class Toy {
    private String name;
    private int price;
    private int lowBoundAge;
    private int upBoundAge;

    Toy() {
        this("Teddy", 100, 6, 23);
    }

    Toy(String name,  int price, int lowBoundAge, int upBoundAge) {
        this.name = name;
        this.price = price;
        this.lowBoundAge = lowBoundAge;
        this.upBoundAge = upBoundAge;
    }
    
    public String getName() {
        return name;
    }
    public int getPrice() {
        return price;
    }
    public int getLowBoundAge() {
        return lowBoundAge;
    }
    public int getUpBoundAge() {
        return upBoundAge;
    }
    public void setName(String name) {
        this.name = name;
    }
    public void setPrice(int price) {
        this.price = price;
    }
    public void setLowBoundAge(int lowBoundAge) {
        this.lowBoundAge = lowBoundAge;
    }
    public void setUpBoundAge(int upBoundAge) {
        this.upBoundAge = upBoundAge;
    }
}