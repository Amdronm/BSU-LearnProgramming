package unicontrol;

// import java.util.HashSet;
// import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

public class Main {
    public static void main(String[] args) {
        Set<Student> students = new TreeSet<>(new ComparatorByName());
        students.add(new Student("Ivan", "ivan1", "ivan@mail.com"));
        students.add(new Student("Ann", "ann2", "ann@mail.com"));
        students.add(new Student("Max", "max3", "max@mail.com"));
        students.add(new Student("Ivan", "ivan1", "ivan@mail.com"));
        Course course = new Course(students, "Mathematical modeling");

        System.out.println(course.toString());

        for (Student i : course) {
            System.out.printf("%-10s%20s%n", i.getName(), i.getEmail());
        }

        // Iterator<Student> it = students.iterator();
        // while (it.hasNext()) {
        //     Stu
        // }
    }
}
