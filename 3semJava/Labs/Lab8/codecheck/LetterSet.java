package codecheck;

import java.util.*;

public class LetterSet {
    public Set<String> makeLetterSet(String str)
   {
    Set<String> set = new TreeSet<>();
    for (int i = 0; i < str.length(); i++) {
        set.add(String.valueOf(str.charAt(i)));
    }
    return set;
   }
}
