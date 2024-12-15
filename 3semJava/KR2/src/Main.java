import collection.BinaryTree;
import controller.FrameController;

public class Main {
    public static void main(String[] args) {
//        BinaryTree tree = new BinaryTree();
//        try {
//            tree.parse(new File("src/collection/input.txt"));
//        } catch (FileNotFoundException e) {
//            System.err.println(e.getMessage());
//        }
//        Visitor v = new PrintVisitor();
//        tree.accept(v);
//        System.out.println(tree.moveToMax());
//        System.out.println(tree.max());
//        Iterator it = tree.createIterator();
//        for (it.first(); !it.isDone(); it.next()) {
//            System.out.println(it.currentItem());
//        }

        FrameController app = new FrameController(new BinaryTree());
    }
}
