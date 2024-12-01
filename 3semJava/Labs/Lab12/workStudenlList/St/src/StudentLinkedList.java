import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class StudentLinkedList implements StudentList, Iterable<Student> {
    private StudentNode head;

    private static class StudentNode {
        public Student data;
        public StudentNode next;
        public StudentNode(Student student, StudentNode next) {
            this.data = student;
            this.next = next;
        }
    }

    public StudentLinkedList() {
        this.head = null;
    }

    @Override
    public void add(Student student) {
        this.head = new StudentNode(student, this.head);
    }

    @Override
    public void print() {
        Iterator<Student> it = iterator();
        while (it.hasNext()) {
            System.out.println(it.next());
        }
    }

    public class StudentListIterator implements Iterator<Student> {
        private StudentNode curr = head;

        @Override
        public boolean hasNext() {
            return curr != null;
        }

        @Override
        public Student next() {
            Student res = curr.data;
            curr = curr.next;
            return res;
        }
    }

    @Override
    public Iterator<Student> iterator() {
        return new StudentListIterator();
    }

    public List<Student> toList() {
        List<Student> list  = new ArrayList<>();
        for (Student student : this) {
            list.add(student);
        }
        return  list;
    }
}
