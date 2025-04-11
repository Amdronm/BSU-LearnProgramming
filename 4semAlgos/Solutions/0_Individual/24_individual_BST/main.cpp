#include <iostream>
#include <fstream>
#include <vector>

static void print_vec(const std::vector<int>& v) {
    for (int i : v)
        std::cout << i << "\n";
    std::cout << std::endl;
}

struct node {
    int val;
    node* left;
    node* right;
    int height;
    node(int a) : val(a), left(nullptr), right(nullptr), height(-1) {}
};

struct BST {
    BST() : root(nullptr) {}
    BST(int a) : root(new node(a)) {}

    void add(int key) {
        if (root == nullptr) {
            root = new node(key);
            return;
        }
        node* curr = root;
        node* prev = curr;
        while (curr != nullptr) {
            prev = curr;
            if (key < curr->val) {
                curr = curr->left;
            }
            else if (key > curr->val) {
                curr = curr->right;
            }
            else {
                return;
            }
        }
        if (key < prev->val) {
            prev->left = new node(key);
        }
        else {
            prev->right = new node(key);
        }
    }
    void pre_order_traversal() {
        v.clear();
        pre_order_traversal(root);
    }
    void pre_order_traversal(node* smnode) {
        if (smnode == nullptr)
            return;
        v.push_back(smnode->val);
        pre_order_traversal(smnode->left);
        pre_order_traversal(smnode->right);
    }
    node* find(int a, node* node) {
        if (node == nullptr)
            return nullptr;
        if (node->val == a)
            return node;
        if (a < node->val) {
            return find(a, node->left);
        }
        else {
            return find(a, node->right);
        }
    }
    node* find_prev(int a, node* node) {
        if (node == nullptr)
            return nullptr;
        if (node->val == a)
            return node;
        if (node->left != nullptr) {
            if (node->left->val == a)
                return node;
        }
        if (node->right != nullptr) {
            if (node->right->val == a)
                return node;
        }
        if (a < node->val) {
            return find_prev(a, node->left);
        }
        else {
            return find_prev(a, node->right);
        }
    }
    void remove(int a) {
        node* n = find(a, root);
        if (n == nullptr)
            return;
        if (n->left == nullptr) {
            if (n == root) {
                root = n->right;
            }
            else {
                node* prev = find_prev(a, root);
                if (n == prev->left) {
                    prev->left = n->right;
                }
                else {
                    prev->right = n->right;
                }
            }
            delete n;
            return;
        }
        if (n->right == nullptr) {
            if (n == root) {
                root = n->left;
            }
            else {
                node* prev = find_prev(a, root);
                if (n == prev->left) {
                    prev->left = n->left;
                }
                else {
                    prev->right = n->left;
                }
            }
            delete n;
            return;
        }
        node* r = n->right;
        bool bLeft = false;
        node* pre = n;
        while (r->left != nullptr) {
            pre = r;
            r = r->left;
            bLeft = true;
        }
        n->val = r->val;
        if (bLeft) {
            pre->left = r->right;
        }
        else {
            pre->right = r->right;
        }
        delete r;
    }
    void calc_height() {
        this->height = calc_height(root);
    }
    int calc_height(node* smnode) {
        if (smnode == nullptr) {
            return -1;
        }
        return 1 + std::max(calc_height(smnode->left), calc_height(smnode->right));
    }
    friend std::ostream& operator<<(std::ostream& out, BST& tree) {
        tree.pre_order_traversal();
        for (int i : tree.v)
            out << i << "\n";
        return out;
    }

    std::vector<int> v;
    node* root;
    int height = -1;
};

int main() {
    std::ifstream fin("tst.in");
    std::ofstream fout("tst.out");
    BST tree;
    int n = 0;
    while (!fin.eof()) {
        fin >> n;
        tree.add(n);
    }
    fout << tree;
    //tree.pre_order_traversal();
    tree.calc_height();
    std::cout << tree.height << std::endl;
    return 0;
}