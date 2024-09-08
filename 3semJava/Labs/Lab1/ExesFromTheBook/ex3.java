import java.util.*;

class Ex3 {
    public static void main(String[] args) {
        System.out.println("Enter a, b, c");
        Scanner in = new Scanner(System.in);
        int a = in.nextInt();
        int b = in.nextInt();
        int c = in.nextInt();
        ownMax(a, b, c);
        internalMax(a, b, c);
        in.close();
    }

    public static void ownMax(int x, int y, int z) {
        System.out.print("using if-else ");
        if (x >= y && x >= z) {
            System.out.println("the largest = " + x);
        } else {
            if (y >= x && y >= z) {
                System.out.println("the largest = " + y);   
            } else {
                System.out.println("the largest = " + z);
            }
        }
    }

    public static void internalMax(int x, int y, int z) {
        int xx = Math.max(x, y);
        System.out.println("using Math.max() the largest = " + Math.max(xx, z));
    }
}
