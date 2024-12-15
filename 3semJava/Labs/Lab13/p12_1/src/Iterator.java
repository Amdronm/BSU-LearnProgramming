import java.util.List;
import java.util.Objects;

public class Iterator<T> implements iIterator<T> {
    private final List<T> list;
    private int current;

    public Iterator(List<T> list) {
        this.list = list;
        this.current = 0;
    }

    @Override
    public void first() {
        current = 0;
    }

    @Override
    public void next() {
        current++;
    }

    @Override
    public boolean isDone() {
        return current >= list.size();
    }

    @Override
    public T getItem() {
        return list.get(current);
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        Iterator<?> iterator = (Iterator<?>) o;
        return current == iterator.current && Objects.equals(list, iterator.list);
    }

    @Override
    public int hashCode() {
        return Objects.hash(list, current);
    }
}
