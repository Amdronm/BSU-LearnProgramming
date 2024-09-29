public class BinaryTree<T extends Comparable<T>> {
    class Node {
        T value;
        Node left;
        Node right;
        Node(T value) {
            this.value = value;
            left = right = null;
        }
    }

    Node root;

    BinaryTree(T value) {
        root = new Node(value);
    }

    boolean findCycle(T value) {
        Node current = root;
        while (current != null) {
            int compare = value.compareTo(current.value);
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

    boolean find(T value) {
        return null != find(value, root);
    }

    Node find(T value, Node current) {
        if (current == null) {
            return null;
        }
        int comp = value.compareTo(current.value);
        if (comp < 0) {
            return find(value, current.left);
        } else if (comp > 0) {
            return find(value, current.right);
        } else {
            return current;
        }
    }

    void add(T value) {
        add(value, root);
    }

    Node add(T value, Node current) {
        if (current == null) {
            return new Node(value);
        }
        if (value.compareTo(current.value) < 0) {
            current.left = add(value, current.left);
        } else {
            current.right = add(value, current.right);
        }
        return current;
    }

    void remove(T value) {
        root = remove(value, root);
    }

    Node remove(T value, Node current) {
        if (current == null) {
            return null;
        }
        int comp = value.compareTo(current.value);
        if (comp < 0) {
            current.left = remove(value, current.left);
        } else if (comp > 0) {
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

    T getLeftestNode(Node current) {
        if (current.left == null) {
            return current.value;
        } else {
            return getLeftestNode(current.left);
        }
    }

    void printVertLR() {
        printVertLR(root);
    }

    void printVertLR(Node current) {
        if (current == null) {
            return;
        }
        printVertLR(current.left);
        System.out.println(current.value);
        printVertLR(current.right);
    }

    void printLRVert() {
        printLRVert(root);
    }

    void printLRVert(Node current) {
        if (current == null) {
            return;
        }
        printLRVert(current.left);
        printLRVert(current.right);
        System.out.println(current.value);
    }

    void printLVertR() {
        printLVertR(root);
    }

    void printLVertR(Node current) {
        if (current == null) {
            return;
        }
        printLVertR(current.left);
        System.out.println(current.value);
        printLVertR(current.right);
    }

    public static void main(String[] args) {
        System.out.println("This is your tree : ");
        BinaryTree<Integer> tree = new BinaryTree<Integer>(5);
        tree.add(2);
        tree.add(8);
        tree.add(4);
        tree.add(1);
        tree.add(6);
        tree.add(9);
        tree.printVertLR();
        tree.add(-1);
        tree.printVertLR();
        tree.remove(5);
        tree.printLVertR();
    }
}