package work;

import java.util.StringTokenizer;

public class Ex3 {
    public static void main(String[] args) {
        String s = new String("675 fdhjk 68. 86768,  78,7899  78.2938 djkf78fjk");
        StringTokenizer sttok = new StringTokenizer(s, ", ");
        StringBuilder res = new StringBuilder();
        while (sttok.hasMoreTokens()) {
            String token = new String(sttok.nextToken());
            try {
                Integer.parseInt(token.toString());
            } catch (NumberFormatException e) {
                res.append(token.toString() + " ");
            }
        }
        System.out.println(res.toString());
    }
}
