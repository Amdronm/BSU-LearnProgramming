package work;

public class Ex1 {
    @SuppressWarnings("unused")
    public static void main(String[] args) {
        int a = 3, b = 56;
        String aplusb = new String(a + " + " + b + " = " + (a + b));
        String aminusb = new String(a + " - " + b + " = " + (a - b));
        String amulb = new String(a + " * " + b + " = " + (a * b));
    }   
}