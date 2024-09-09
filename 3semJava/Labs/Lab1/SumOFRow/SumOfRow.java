import java.io.IOException;

public class SumOfRow {
    public static void main(String[] args) throws IOException {
        if (args.length != 2) {
            throw new IOException("wrong number of args");
        }

        double x = 0.5;
        try {
            x = Double.parseDouble(args[0]);
        } catch (NumberFormatException ex) {
            System.err.println("x must be double");
        }

        double e = 1e-5;
        try {
            e = Double.parseDouble(args[1]);
        } catch (NumberFormatException ex) {
            System.err.println("precision must be double");
        }

        System.out.println("x = " + x);
        System.out.println("precision - " + e);
        double sum = 0;
        int k = 1;
        long kfact = 6;
        double el = ((Math.pow((-1), k + 1) * x * x) / (kfact)) * Math.pow(4./3, 4 * k + 2);
        while (Math.abs(el) > e) {
            sum += el;
            k++;
            kfact *= 2 * k * (2 * k + 1);
            el = ((Math.pow((-1), k + 1) * x * x) / (kfact)) * Math.pow(4./3, 4 * k + 2);
        }
        System.out.println("sum = " + sum);
    }
}