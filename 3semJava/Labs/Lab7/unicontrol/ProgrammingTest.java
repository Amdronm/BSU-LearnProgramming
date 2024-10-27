package unicontrol;

import java.io.File;
import java.util.*;
import java.util.function.Predicate;

public class ProgrammingTest {    
    public static void main(String[] args) {
        Set<Student> students = new TreeSet<>(new ComparatorByName());
        Course course = new Course(students, "Mathematical modeling");
        course.addStudent(new Undergraduate("Max", "gg4", "max@mail", new Academic("Paul Deitel")));
        course.addStudent(new Undergraduate("Ann", "pr3", "ann@mail", new Academic("Cay Horstmann")));
        course.addStudent(new Postgraduate("Ben", "te2", "Ben@mail", new Academic("Paul Deitel")));
        course.addStudent(new Postgraduate("Tom", "yj34", "tom@mail", new Academic("Cay Horstmann")));
        course.addStudent(new Postgraduate("Sam", "jj8", "sam@mail", new Academic("Cay Horstmann")));

        System.out.println(course.toString());

        File file = new File("3semJava\\Labs\\Lab7\\unicontrol\\output.txt");
        Writer out = new Writer();
        out.write(course, file);

        System.out.println("Postgraduates with sup Horstmann:");
        Set<Student> set = new TreeSet<>();
        set = course.lookCourse(new Predicate<Student>() {
            @Override
            public boolean test(Student t) {
                if (t.getClass() != Postgraduate.class) {
                    return false;
                } else {
                    return ((Postgraduate)t).getSupervisor().getName() == "Cay Horstmann";
                }
            }
        });
        for (Student i : set) {
            System.out.println(i.toString());
        }
        System.out.println();

        Notifier n = new Notifier(students);
        n.doNotifyAll("Hello, students!");
    }
}