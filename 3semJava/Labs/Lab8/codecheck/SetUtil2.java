package codecheck;

import java.util.ArrayList;
import java.util.*;
import java.util.Set;
import java.util.TreeSet;

public class SetUtil2 {
    /**
      Determine the strings that are unique to words1 and words2
      @param words1 an array of strings
      @param words2 an array of strings      
      @param a list of two sets: the words that are in words1 but not word2,
      and the words that are in words2 but not word1. The sets should be sorted.
   */
   public static List<Set<String>> uniqueInEach(String[] words1, String[] words2)
   {
      List<Set<String>> list = new ArrayList<>();
      Set<String> s1 = new TreeSet<>();
      s1.addAll(Arrays.asList(words1));
      Set<String> s2 = new TreeSet<>(Arrays.asList(words2));
      Set<String> r1 = new TreeSet<>();
      for (String s : s1) {
        if (!s2.contains(s)) {
            r1.add(s);
        }
      }
      Set<String> r2 = new TreeSet<>();
      for (String s : s2) {
        if (!s1.contains(s)) {
            r2.add(s);
        }
      }
      list.add(r1);
      list.add(r2);
      return list;
   }
}
