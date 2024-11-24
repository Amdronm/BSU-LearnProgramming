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
        Iterator<Integer> it = stack.getEndIterator();
        it.prev();
        while (!it.isDone()) {
            System.out.println(it.getCurrent());
            it.prev();
        }
        stack.pushAll(new ArrayList<>(Arrays.asList(new Integer[]{11, 13, 17, 19})));
        System.out.println(stack.toString());
        Iterator<Integer> rit = stack.getBaseIterator();
        while (!rit.isDone()) {
            System.out.println(rit.getCurrent());
            rit.next();
        }
    }
}