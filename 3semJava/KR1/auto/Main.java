package auto;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {
    public static void main(String[] args) {

        List<Auto> list = new ArrayList<>();
        list = parseCars(new File("auto/input1.txt"));
        System.out.println(list.toString());

        System.out.println(Edit.getCollectionLowPrice(list));
    }
        
    public static List<Auto> parseCars(File file) {
        List<Auto> list = new ArrayList<>();
        try (Scanner in = new Scanner(file)) {
            while (in.hasNext()) {
                String s = in.nextLine();
                String[] ss = s.split("[ ]+");
                try {
                    Car car = new Car(ss[0], Integer.parseInt(ss[1]), Integer.parseInt(ss[2]), Integer.parseInt(ss[3]));
                    list.add(car);
                } catch (NumberFormatException e) {
                   System.err.println(e.getMessage());
                }
            }
        } catch (FileNotFoundException e) {
            System.err.println(e.getMessage());
        }
        return list;
    }
}
