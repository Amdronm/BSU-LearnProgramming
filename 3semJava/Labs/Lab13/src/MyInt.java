public class MyInt implements Element {
    private int value;

    public MyInt(int value) {
        this.value = value;
    }

    @Override
    public void accept(Visitor v) {
        v.visit(this);
    }

    @Override
    public String toString() {
        return Integer.toString(value);
    }
}
