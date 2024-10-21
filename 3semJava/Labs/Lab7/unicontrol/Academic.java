package unicontrol;

public class Academic extends Person {
    Academic(String name) {
        super(name);
    }

    @Override
    public String toString() {
        return "Academic=[" + getName() + "]";
    }
}
