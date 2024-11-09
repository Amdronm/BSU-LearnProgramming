package auto;

import java.util.Comparator;
import java.util.List;

public class Edit {
    public static List<Auto> getCollectionLowPrice(List<Auto> list) {
        List<Auto> res = list.stream().sorted(new Comparator<Auto>() {
            public int compare(Auto o1, Auto o2) {
                if (o1.countPrice() == o2.countPrice()) {
                    return o1.getRate() - o2.getRate();
                } else {
                    return o1.countPrice() - o2.countPrice();
                }
            }
        }).toList();
        return res;
    }

    public static int getNumAutosByColor(List<Auto> list, int color) {
        long res = list.stream().filter(a -> a.getColor() == color).count();
        return (int) res;
    }

    public static boolean searchBin(List<Auto> list, Auto auto) {

        return true;
    }

    public static List<Auto> getPriceDivColor(List<Auto> list) {
        return list;
    }

    public static List<Auto> getAutosOnT(List<Auto> list) {
        return list;
    }
}
