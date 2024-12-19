import org.w3c.dom.*;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import java.util.TreeSet;

public class ParserDOM implements StrategyXML {
    @Override
    public TreeSet<Toy> parseToys(File file) throws Exception {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        Document document = factory.newDocumentBuilder().parse(file);
        TreeSet<Toy> res = new TreeSet<>(new ToyComparator());
        NodeList toyNodes = document.getElementsByTagName("toy");
        for (int i = 0; i < toyNodes.getLength(); i++) {
            Node toyNode = toyNodes.item(i);
            if (toyNode.getNodeType() == Node.ELEMENT_NODE) {
                Element toyElement = (Element) toyNode;
                String name = toyElement.getElementsByTagName("name").item(0).getTextContent();
                int price = Integer.parseInt(toyElement.getElementsByTagName("price").item(0).getTextContent());
                int lba = Integer.parseInt(toyElement.getElementsByTagName("lba").item(0).getTextContent());
                int uba = Integer.parseInt(toyElement.getElementsByTagName("uba").item(0).getTextContent());
                res.add(new Toy(name, price, lba, uba));
            }
        }
        return res;
    }
}