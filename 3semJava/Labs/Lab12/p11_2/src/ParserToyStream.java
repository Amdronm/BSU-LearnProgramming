import java.util.Scanner;
import java.util.TreeSet;

public class ParserToyStream implements Strategy {
    @Override
    public TreeSet<Toy> parseToys(Scanner in) {
        TreeSet<Toy> res = new TreeSet<>(new ToyComparator());
        in.useDelimiter("\n");
        in.tokens().forEach(s -> {
            try {
                s = s.strip();
                Toy t = new Toy();
                t.fromString(s);
                res.add(t);
            } catch (NumberFormatException e) {
                throw new RuntimeException("Wrong File Format!");
            }
        });
        return res;
    }
}
