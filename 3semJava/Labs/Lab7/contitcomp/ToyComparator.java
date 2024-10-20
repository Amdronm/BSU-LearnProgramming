package contitcomp;

import java.util.Comparator;

public class ToyComparator implements Comparator<Toy> {
    @Override
    public int compare(Toy o1, Toy o2) {
        return Integer.valueOf(o1.getPrice()).compareTo(Integer.valueOf(o2.getPrice()));
    }    
}