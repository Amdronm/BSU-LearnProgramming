import java.util.Iterator;

public class Main {
    public static void main(String[] args) {
        StudentLinkedList list = new StudentLinkedList();
        list.add(new Student("Vasya"));
        list.add(new Student("Danya"));
        list.add(new Student("Alesya"));
        list.print();

        System.out.println("Using iterator : ");
        for (Student student : list) {
            System.out.println(student);
        }
    }
}