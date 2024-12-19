import java.util.List;
import java.util.Objects;

public class ReverseIterator<T> implements iIterator<T> {
    private final List<T> list;
    private int current;

    public ReverseIterator(List<T> list) {
        this.list = list;
        this.current = list.size() - 1;
    }

    @Override
    public void first() {
        current = list.size() - 1;
    }

    @Override
    public void next() {
        current--;
    }

    @Override
    public boolean isDone() {
        return current < 0;
    }

    @Override
    public T getItem() {
        return list.get(current);
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        ReverseIterator<?> that = (ReverseIterator<?>) o;
        return current == that.current && Objects.equals(list, that.list);
    }

    @Override
    public int hashCode() {
        return Objects.hash(list, current);
    }
}
