package codecheck;

import java.util.*;

public class LetterMap {
    public Map<String, Integer> makeLetterMap(String str)
   {
      // TODO: Complete method
      Map<String, Integer> map = new TreeMap<>();
      for (int i = 0; i < str.length(); i++) {
        String s = String.valueOf(str.charAt(i));
        if (map.get(s) == null) {
            map.put(s, 1);
            continue;
        }
        map.put(s, map.get(s) + 1);
      }
      return map;
   }
}
