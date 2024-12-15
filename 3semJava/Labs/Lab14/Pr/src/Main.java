import collection.MyCollection;
import controller.Controller;
import iterator.MyIterator;
import strategy.Strategy2;
import visitor.CountVisitor;
import visitor.PrintVisitor;
import visitor.StringVisitor;

import java.util.List;

public class Main {
    public static void main(String[] args) {
//        MyCollection mc = new MyCollection();
//        mc.add(1);
//        mc.add(6);
//        mc.add(9);
//        mc.add(4);
//        mc.add(-8);
//        MyIterator<Integer> it = mc.createIterator();
//        for (it.first(); !it.isDone(); it.next()) {
//            System.out.println(it.currentItem());
//        }
//        System.out.println(mc);
//        List<Integer> list = mc.sort();
//        System.out.println(list);
//
//        mc.setStrategy(new Strategy2());
//        list = mc.sort();
//        System.err.println(list);
//
//        System.out.println("using visitor: ");
//        mc.accept(new PrintVisitor());
//
//        CountVisitor cv = new CountVisitor();
//        mc.accept(cv);
//        System.out.println("using CountVisitor: " + cv.getCount());
//
//        StringVisitor sv = new StringVisitor();
//        mc.accept(sv);
//        System.out.println("using StringVisitor: " + sv.getString());
        MyCollection mc = new MyCollection();
        mc.add(4);
        mc.add(6);
        mc.add(9);
        Controller controller = new Controller(mc);
    }
}
