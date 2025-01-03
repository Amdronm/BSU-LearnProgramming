package codecheck;

import java.util.TreeSet;

/**
   This TreeSetUtil class tests various usages of the HashSetUtil class. 
   params 1 is an aray of strings. param2 is a single string. This program will create
   a TreeSet made of Person object. Person is an inner class. This program will fail to
   run as any TreeSet element MUST implement the Comparable interface. You will need  to
   implement that interface for the <String> type to make the program run correctly.
*/

public class TreeSetUtil {
    
public static boolean check(String [] names, String name)
 {
     Person p1 = new Person(name);

     TreeSet<Person> people = new TreeSet<Person>();
     for (String person : names)
       people.add(new Person(person));

     return processSet(people, p1);
 }


 public static boolean processSet(TreeSet<Person> people, Person person)
 {
   return people.contains(person);
 }


/* Inner class Person simply has two name fields fn, first name and ln, last name, 
   a constructor and the toString  method override
*/


static class Person implements Comparable<Person>
{
   private String name;

   public Person(String name) {
      this.name = name;
   }

   public String toString()
   {
     return name;
   }
   
   public int hashCode()
   {
     return name.hashCode();
   }
   public boolean equals(Object object)
   {
     Person p = (Person) object;
     return name.equals(p.name);
   }


   @Override
   public int compareTo(Person o) {
       return this.name.compareTo(o.name);
   }

}

}
