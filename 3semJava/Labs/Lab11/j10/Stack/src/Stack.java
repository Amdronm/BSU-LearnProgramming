import java.util.ArrayList;
import java.util.Objects;
import java.util.List;

public class Stack<T> {
    private List<T> data;

    public Stack() {
        data = new ArrayList<>();
    }

    public Stack(ArrayList<T> data) {
        this.data = data;
    }

    public int size() {
        return data.size();
    }

    public boolean isEmpty() {
        return data.isEmpty();
    }

    public void clear() {
        data.clear();
    }

    public List<T> getList() {
        return data;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        Stack<?> stack = (Stack<?>) o;
        return Objects.equals(data, stack.data);
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(data);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = data.size() - 1; i >= 0; i--) {
            sb.append(data.get(i)).append('\n');
        }
        return sb.toString();
    }

    public T top() {
        return data.getLast();
    }

    public void push(T element) {
        data.add(element);
    }

    public T pop() {
        return data.removeLast();
    }

    public void pushAll(List<T> list) {
        data.addAll(list);
    }

    public Iterator<T> getIterator() {
        return new Iterator<>(data);
    }

    public ReverseIterator<T> getReverseIterator() {
        return new ReverseIterator<>(data);
    }
}