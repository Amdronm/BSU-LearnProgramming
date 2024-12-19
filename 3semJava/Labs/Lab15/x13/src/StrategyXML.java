import java.io.File;
import java.util.TreeSet;

public interface StrategyXML {
    TreeSet<Toy> parseToys(File file) throws Exception;
}
