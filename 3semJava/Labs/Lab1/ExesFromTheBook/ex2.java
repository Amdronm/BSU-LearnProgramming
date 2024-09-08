import java.util.*;

class Ex2 {
    public static void main(String[] args) {
        System.out.println("Enter angle");
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        usingMod(n);
        usingFloorMod(n);
        in.close();
    }

    public static void usingMod(int a) {
        a %= 360;
        a += 360;
        a %= 360;
        System.out.println("using % angle = " + a);
    }

    public static void usingFloorMod(int a) {
        a = Math.floorMod(a, 360);
        System.out.println("using floorMod() angle = " + a);
    }
}
