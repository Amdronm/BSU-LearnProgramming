import java.util.StringTokenizer;

public class StringFormatting {
    public static void main(String[] args) {
        StringTokenizer st = new StringTokenizer("this  66.85 is 998 a test");
        while (st.hasMoreTokens()) {
            String token = st.nextToken();
            boolean flag = false;
            try {
                double d = Double.parseDouble(token);
                if (token.indexOf('.') != -1) {
                    flag = true;
                }
            } catch (NumberFormatException exc) {}
            System.out.println(token + " - " + flag);
        }
    }
}