package unicontrol;

public class ProgrammingTest {
    public static void main(String[] args) {
        Undergraduate a = new Undergraduate("yoy", "log", "email", new Academic("aca"));
        // a.notify("notied");
        System.out.println(a.toString());
    }
}
