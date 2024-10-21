package ComparaTree;

public class Person {
    String surname;
    String name;

    Person(String surname, String name) {
        this.surname = surname;
        this.name = name;
    }

    @Override
    public String toString() {
        return "(" + surname + " " + name + ")";
    }
}
