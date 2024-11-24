import java.util.List;
import java.util.Objects;

public class Iterator<T> {
    private final List<T> list;
    private int current;

    public Iterator(List<T> list) {
        this.list = list;
        this.current = 0;
    }

    public Iterator(List<T> list, int current) {
        this.list = list;
        this.current = current;
    }

    public void base() {
        current = 0;
    }

    public void end() {
        current = list.size();
    }

    public void next() {
        current++;
    }

    public void prev() {
        current--;
    }

    public boolean isDone() {
        return current >= list.size() || current < 0;
    }

    public T getCurrent() {
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
