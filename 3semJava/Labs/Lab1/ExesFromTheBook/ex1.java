import java.util.*;

class Ex1 {
    public static void main(String[] args) {
        System.out.println("Enter number");
        Scanner in = new Scanner(System.in);
        int nn = in.nextInt();
        System.out.println(Integer.toBinaryString(nn));
        System.out.printf("oct number - %o %n", nn);
        System.out.printf("hex number - %x %n", nn);
        double dd = 1. / nn;
        System.out.printf("reciprocal hex number - %a %n", dd);
        in.close();
    }
}