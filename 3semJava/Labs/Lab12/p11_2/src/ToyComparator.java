import java.util.Comparator;

public class ToyComparator implements Comparator<Toy> {
    @Override
    public int compare(Toy o1, Toy o2) {
        return Integer.compare(o1.getPrice(), o2.getPrice());
    }    
}