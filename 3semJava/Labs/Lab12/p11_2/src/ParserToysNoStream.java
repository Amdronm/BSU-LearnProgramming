import java.util.Scanner;
import java.util.TreeSet;

public class ParserToysNoStream implements Strategy {
    @Override
    public TreeSet<Toy> parseToys(Scanner in) throws Exception {
        TreeSet<Toy> res = new TreeSet<>(new ToyComparator());
        String s;
        while (in.hasNext()) {
            s = in.nextLine();
            Toy toy = new Toy();
            try {
                toy.fromString(s);
            } catch (Exception e) {
                throw new Exception("File of Wrong format");
            }
            res.add(toy);
        }
        return res;
    }
}
