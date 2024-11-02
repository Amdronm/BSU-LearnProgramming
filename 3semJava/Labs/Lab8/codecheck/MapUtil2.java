package codecheck;

import java.util.*;

public class MapUtil2 {
    /**
      Make a sorted map whose keys are the word lengths words and whose values are
      the sets of the words with the given lengths. The map and sets should be sorted.
      @param words an array of strings
      @return a map mapping strings to their lengths
   */
   public Map<Integer, TreeSet<String>> makeMap(String[] words)
   {
      Map<Integer, TreeSet<String>> map = new TreeMap<>();
      for (String s : words) {
        map.putIfAbsent(s.length(), new TreeSet<>(Arrays.asList(s)));
        map.get(s.length()).add(s);
      }
      return map;
   }
}
