import java.util.ArrayList;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        ArrayList<Integer> data = new ArrayList<>(Arrays.asList(new Integer[]{1, 2, 3, 4}));
        Stack<Integer> stack = new Stack<>(data);
        stack.push(5);
        System.out.println(stack.pop());
        System.out.println(stack.pop());
        System.out.println(stack.toString());
        stack.push(6);
        stack.push(8);
        ReverseIterator<Integer> it = stack.getReverseIterator();
        for (it.first(); !it.isDone(); it.next()) {
            System.out.println(it.getItem());
        }
        stack.pushAll(new ArrayList<>(Arrays.asList(new Integer[]{11, 13, 17, 19})));
        System.out.println(stack.toString());
        Iterator<Integer> rit = stack.getIterator();
        while (!rit.isDone()) {
            System.out.println(rit.getItem());
            rit.next();
        }
    }
}