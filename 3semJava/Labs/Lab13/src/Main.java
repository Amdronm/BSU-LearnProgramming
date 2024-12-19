public class Main {
    public static void main(String[] args) {
        Stack<MyInt> stack = new Stack<>();
        stack.push(new MyInt(1));
        stack.push(new MyInt(2));
        stack.push(new MyInt(6));
        stack.push(new MyInt(11));
        ToStringV v = new ToStringV();
        for (Iterator<MyInt> it = stack.getIterator(); !it.isDone(); it.next()) {
            it.getItem().accept(v);
        }
        System.out.println(v.getResult());
    }
}