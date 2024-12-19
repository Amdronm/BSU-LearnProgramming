import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamReader;
import java.io.File;
import java.io.FileReader;
import java.util.TreeSet;

public class ParserStAX implements StrategyXML {
    @Override
    public TreeSet<Toy> parseToys(File file) throws Exception {
        XMLInputFactory factory = XMLInputFactory.newInstance();
        XMLStreamReader reader = factory.createXMLStreamReader(new FileReader(file));
        TreeSet<Toy> res = new TreeSet<>(new ToyComparator());

        String name = "";
        int price = 0;
        int lba = 0;
        int uba = 0;

        while (reader.hasNext()) {
            int event = reader.next();
            if (event == XMLStreamConstants.START_ELEMENT && "toy".equals(reader.getLocalName())) {
                while (reader.hasNext()) {
                    event = reader.next();
                    if (event == XMLStreamConstants.START_ELEMENT) {
                        String tagName = reader.getLocalName();
                        event = reader.next();
                        if (event == XMLStreamConstants.CHARACTERS) {
                            String tagContent = reader.getText();
                            switch (tagName) {
                                case "name":
                                    name = tagContent;
                                    break;
                                case "price":
                                    price = Integer.parseInt(tagContent);
                                    break;
                                case "lba":
                                    lba = Integer.parseInt(tagContent);
                                    break;
                                case "uba":
                                    uba = Integer.parseInt(tagContent);
                                    break;
                            }
                        }
                    } else if (event == XMLStreamConstants.END_ELEMENT && "toy".equals(reader.getLocalName())) {
                        res.add(new Toy(name, price, lba, uba));
                        break;
                    }
                }
            }
        }
        reader.close();
        return res;
    }
}

