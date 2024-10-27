package unicontrol;

import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;
import java.util.function.Predicate;

public class Course implements Iterable<Student> {
    private Set<Student> students;
    private String course;

    public Course(Set<Student> students, String course) {
        this.students = students;
        this.course = course;
    }

    public boolean addStudent(Student student) {
        boolean res = students.add(student);
        return res;
    }

    public Set<Student> lookCourse(Predicate<Student> predicate) {
        Set<Student> res = new TreeSet<>(new ComparatorByName());
        for (Student i : students) {
            if (predicate.test(i)) {
                res.add(i);
            }
        }
        return res;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(course + ":\n");
        for (Student i : students) {
            sb.append(i.toString() + "\n");
        }
        return sb.toString();
    }

    @Override
    public Iterator<Student> iterator() {
        return students.iterator();
    }
}
