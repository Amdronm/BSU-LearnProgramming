package ComparaTree;

import java.util.*;

public class BinTree<T> {
    private class Node {
        T value;
        Node left;
        Node right;

        Node(T value) {
            this.value = value;
            left = right = null;
        }
    }

    private Node root;
    private Comparator<T> comp;

    public BinTree(Comparator<T> comp) {
        this.comp = comp;
        this.root = null;
    }

    public boolean findCycle(T value) {
        Node current = root;
        while (current != null) {
            int compare = comp.compare(value, current.value);
            if (compare == 0) {
                return true;
            } else if (compare < 0) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        return false;
    }

    public boolean find(T value) {
        return null != find(value, root);
    }

    private Node find(T value, Node current) {
        if (current == null) {
            return null;
        }
        int c = comp.compare(value, current.value);
        if (c < 0) {
            return find(value, current.left);
        } else if (c > 0) {
            return find(value, current.right);
        } else {
            return current;
        }
    }

    public void add(T value) {
        root = add(value, root);
    }

    private Node add(T value, Node current) {
        if (current == null) {
            return new Node(value);
        }
        if (comp.compare(value, current.value) < 0) {
            current.left = add(value, current.left);
        } else {
            current.right = add(value, current.right);
        }
        return current;
    }

    public void remove(T value) {
        root = remove(value, root);
    }

    private Node remove(T value, Node current) {
        if (current == null) {
            return null;
        }
        int c = comp.compare(value, current.value);
        if (c < 0) {
            current.left = remove(value, current.left);
        } else if (c > 0) {
            current.right = remove(value, current.right);
        } else {
            if (current.left == null && current.right == null) {
                return null;
            }
            if (current.left == null) {
                return current.right;
            }
            if (current.right == null) {
                return current.left;
            }
            T leftestNode = getLeftestNode(current.right);
            current.value = leftestNode;
            current.right = remove(leftestNode, current.right);
        }
        return current;
    }

    private T getLeftestNode(Node current) {
        if (current.left == null) {
            return current.value;
        } else {
            return getLeftestNode(current.left);
        }
    }

    public void printVertLR() {
        printVertLR(root);
        System.out.println();
    }

    private void printVertLR(Node current) {
        if (current == null) {
            return;
        }
        System.out.print(current.value.toString() + " ");
        printVertLR(current.left);
        printVertLR(current.right);
    }

    public void printLRVert() {
        printLRVert(root);
        System.out.println();
    }

    private void printLRVert(Node current) {
        if (current == null) {
            return;
        }
        printLRVert(current.left);
        printLRVert(current.right);
        System.out.print(current.value.toString() + " ");
    }

    public void printLVertR() {
        printLVertR(root);
        System.out.println();
    }

    private void printLVertR(Node current) {
        if (current == null) {
            return;
        }
        printLVertR(current.left);
        System.out.print(current.value.toString() + " ");
        printLVertR(current.right);
    }

    public static void main(String[] args) {
        Comparator<Integer> comp = Comparator.naturalOrder();
        BinTree<Integer> tree = new BinTree<>(comp);
        tree.add(5);
        tree.add(2);
        tree.add(8);
        tree.add(4);
        tree.add(1);
        tree.add(6);
        tree.add(9);
        System.out.println("This is your tree, path - vertex, left, right : ");
        tree.printVertLR();
        System.out.println("Path - left, vertex, right : ");
        tree.printLVertR();
        System.out.println("Path - left, right, vertex : ");
        tree.printLRVert();
        tree.add(-1);
        tree.add(0);
        System.out.println("Tree after adding -1, 0 : ");
        tree.printVertLR();
        tree.remove(5);
        System.out.println("Removed 5, the root : ");
        tree.printLVertR();
        BinTree<Person> pTree = new BinTree<>(new Comparator<Person>() {
            @Override
            public int compare(Person o1, Person o2) {
                return o1.toString().compareTo(o2.toString());
            }
        });
        pTree.add(new Person("Einstein", "Albert"));
        pTree.add(new Person("Newton", "Isaak"));
        pTree.add(new Person("Trump", "Judd"));
        pTree.add(new Person("Armstrong", "Neil"));
        System.out.println("Tree of people : ");
        pTree.printLVertR();
        if (pTree.find(new Person("Armstrong", "Louis"))) {
            System.out.println("Armstrong Louis is here");
        } else {
            System.out.println("Armstrong Louis is not here");
        }
        System.out.println("Armstrong Neil is " + (pTree.find(new Person("Armstrong", "Neil")) ? "" : "not ") + "here");

        // Comparator<String> c = Comparator.reverseOrder();
        // Comparator<String> c3 = (String s1, String s2) -> {return s1.length() -
        // s2.length();};
        // Comparator<String> c4 = (s1, s2) -> s1.length() - s2.length();
        // Comparator<String> c5 = Comparator.comparingInt(String::length);
        // BinTree<String> tree = new BinTree<>(c5);
        // tree.add("Petr");
        // tree.add("Ivan");
        // tree.add("Ann");
        // tree.add("Andrey");
        // tree.add("Pasha");
        // tree.printLVertR();
    }
}