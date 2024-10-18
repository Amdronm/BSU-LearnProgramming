package Tasks;

import java.util.function.Predicate;

class MyAlgo {
    public static <T> int countIf(T[] arr, Predicate<T> pred) {
        int count = 0;
        for (T i : arr) {
            if (pred.test(i)) {
                count++;
            }
        }
        return count;
    }
}

// class OddPred implements Predicate<Integer> {
//     @Override
//     public boolean test(Integer t) {
//         return t % 2 != 0;
//     }

// }

public class CountOdd {
    public static void main(String[] args) {
        Integer[] array = {1, 2, 3, 4, 5, 6, 7};
        // OddPred pred = new OddPred();
        // Predicate<Integer> pred = new Predicate<Integer>() {
        //     @Override
        //     public boolean test(Integer t) {
        //         return t % 2 != 0;
        //     }
        // };
        Predicate<Integer> pred = i -> i % 2 != 0;
        int count = MyAlgo.countIf(array, pred);
        System.out.println(count);
    }
}
