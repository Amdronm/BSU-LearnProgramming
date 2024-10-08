import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Progr {
    public static void main(String[] args) throws FileNotFoundException, IOException {
        Scanner in = new Scanner(new File("3semJava\\Labs\\Lab6\\work07_10_2024\\input.txt"));
        in.useDelimiter("[,;\\s]+");
        double d = 0;
        while (in.hasNext()) {
            if (in.hasNextDouble()) {
                d += in.nextDouble();
            } else {
                in.next();
            }
        }
        in.close();
        File output = new File("3semJava\\Labs\\Lab6\\work07_10_2024\\output.txt");
        FileWriter out = new FileWriter(output);
        out.write(Double.valueOf(d).toString());
        out.close();
    }
}
