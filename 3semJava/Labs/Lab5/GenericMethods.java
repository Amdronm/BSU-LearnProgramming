import java.util.Arrays;
import java.util.function.Predicate;

public class GenericMethods {
    public static void main(String[] args) {
        Integer[] arr = { 1, 2, 3, 4, 5, 6, 7 };
        System.out.println("array : " + Arrays.toString(arr));
        int gr = countGreater(arr, Integer.valueOf(4));
        System.out.println("greater than 4 : " + gr);
        Predicate<Integer> pred = i -> i % 3 == 0;
        int pr = countPred(arr, pred);
        System.out.println("divided by 3 : " + pr);
    }

    public static <T> boolean has(T[] arr, T val) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i].equals(val)) {
                return true;
            }
        }
        return false;
    }

    public static <T> int count(T[] arr, T val) {
        int res = 0;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i].equals(val)) {
                res++;
            }
        }
        return res;
    }

    public static <T extends Comparable<T>> int countGreater(T[] arr, T val) {
        int res = 0;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i].compareTo(val) > 0) {
                res++;
            }
        }
        return res;
    }

    public static <T extends Number> double countSum(T[] arr) {
        double res = 0;
        for (int i = 0; i < arr.length; i++) {
            res += arr[i].doubleValue();
        }
        return res;
    }

    public static <T extends Number> double countAverage(T[] arr) throws Exception {
        double sum = countSum(arr);
        if (arr.length == 0) {
            throw new Exception("No elements in array!");
        }
        return sum / arr.length;
    }

    public static <T> int countPred(T[] arr, Predicate<T> pred) {
        int res = 0;
        for (T i : arr) {
            if (pred.test(i)) {
                res++;
            }
        }
        return res;
    }
}
