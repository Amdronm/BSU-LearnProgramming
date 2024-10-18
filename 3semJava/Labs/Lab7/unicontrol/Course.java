package unicontrol;

import java.util.Iterator;
import java.util.Set;

public class Course implements Iterable<Student> {
    private Set<Student> students;
    private String course;

    public Course(Set<Student> students, String course) {
        this.students = students;
        this.course = course;
    }

    @Override
    public String toString() {
        return course + ":\n" + students.toString();
    }

    @Override
    public Iterator<Student> iterator() {
        return students.iterator();
    }
}
