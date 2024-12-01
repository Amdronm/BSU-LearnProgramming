import java.util.Scanner;
import java.util.TreeSet;

public interface Strategy {
    TreeSet<Toy> parseToys(Scanner in) throws Exception;
}
