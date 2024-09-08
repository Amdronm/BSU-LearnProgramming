import java.math.BigInteger;

class Ex6 {
    public static void main(String[] args) {
        BigInteger n = BigInteger.ONE;
        for (int i = 2; i <= 1000; i++) {
            n = n.multiply(BigInteger.valueOf(i));
        }
        System.out.println(n.toString());
    }
}