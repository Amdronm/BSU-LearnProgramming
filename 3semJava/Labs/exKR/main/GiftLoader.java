package main;

import sweets.*;
import gift.*;

import java.io.*;

public class GiftLoader {
    public static Gift loadGiftFromFile(String filePath) throws IOException {
        Gift gift = new Gift();
        BufferedReader reader = new BufferedReader(new FileReader(filePath));

        String line;
        while ((line = reader.readLine()) != null) {
            String[] parts = line.split(" ");
            switch (parts[0].trim()) {
                case "Chocolate":
                    gift.addSweet(new Chocolate(parts[1], Double.parseDouble(parts[2]),
                            Double.parseDouble(parts[3]), Double.parseDouble(parts[4]),
                            Chocolate.Type.valueOf(parts[5]), false));
                    break;
                case "Lollipop":
                    gift.addSweet(new Lolypop(parts[1], Double.parseDouble(parts[2]),
                            Double.parseDouble(parts[3]), 0, Lolypop.Color.valueOf(parts[4])));
                    break;
            }
        }
        reader.close();
        return gift;
    }
}