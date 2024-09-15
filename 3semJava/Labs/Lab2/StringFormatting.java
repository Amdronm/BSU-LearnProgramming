import java.util.StringTokenizer;
import java.io.IOException;
import java.lang.StringBuilder;

class MyException extends Exception {
    public static Exception WrongNumberOfArgs() {
        return new Exception("wrong number of arguments");
    }
}

public class StringFormatting {
    public static void main(String[] args) throws IOException {
        try {
            if (args.length == 0) {
                throw MyException.WrongNumberOfArgs();
            }
            StringBuilder st = new StringBuilder();
            for (int i = 0; i < args.length; i++) {
                st.append(args[i]);
                st.append(" ");
            }
            StringTokenizer sttok = new StringTokenizer(st.toString());
            st.delete(0, st.length());
            while (sttok.hasMoreTokens()) {
                StringBuilder token = new StringBuilder(sttok.nextToken());
                try {
                    Double.parseDouble(token.toString());
                    int i = token.indexOf(".");
                    if (i != -1 && i + 2 < token.length()) {
                        token = new StringBuilder(token.substring(0, i + 3));
                    }
                } catch (NumberFormatException e) {}
                st.append(token.toString() + " ");
            }
            System.out.println(st.toString());
        } catch (Exception e) {
            System.err.println(e.getMessage());
            return;
        }
    }
}