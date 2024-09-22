package work;

import java.util.StringTokenizer;

public class Ex2 {
    public static void main(String[] args) {
        String st = new String("One two three раз два три one1 two2 123");
        StringTokenizer sttok = new StringTokenizer(st);
        // String letters = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKL";
        int res = 0;
        boolean flag = true;
        while(sttok.hasMoreTokens()) {
            flag = true;
            String token = new String(sttok.nextToken());
            for (int i = 0; i < token.length(); i++) {
                if (!(token.charAt(i) >= 'A' && token.charAt(i) <= 'Z') && !(token.charAt(i) >= 'a' && token.charAt(i) <= 'z')) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                res++;
            }
        }
        System.out.println(res);
    }    
}