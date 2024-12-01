import java.util.Iterator;
import java.util.List;

public class SortedByNameIterator implements Iterator<Student> {
    private StudentLinkedList data;
    private Iterator<Student> it;

    public SortedByNameIterator() {
        List<Student> list = data.toList();
        list = list.stream().sorted().toList();
        this.it = list.iterator();
    }

    @Override
    public boolean hasNext() {
        return data.iterator().hasNext();
    }

    @Override
    public Student next() {
        return null;
    }
}
