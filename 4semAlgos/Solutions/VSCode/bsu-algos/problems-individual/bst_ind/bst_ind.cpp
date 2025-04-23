#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>

struct node {
    int val;
    node* left;
    node* right;
    int height;
    std::unordered_set<int> set_left;
    std::unordered_set<int> set_right;
    node(int a) : val(a), left(nullptr), right(nullptr), height(0) {}
};

struct BST {
    BST() : root(nullptr) {}

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
        if (smnode == nullptr) return;
        v.push_back(smnode->val);
        pre_order_traversal(smnode->left);
        pre_order_traversal(smnode->right);
    }

    node* rm(int val, node* n) {
        if (n == nullptr) return nullptr;
        if (val < n->val) {
            n->left = rm(val, n->left);
        }
        else if (val > n->val) {
            n->right = rm(val, n->right);
        }
        else {
            if (n->left == nullptr && n->right == nullptr) {
                delete n;
                return nullptr;
            }
            if (n->left == nullptr) {
                node* temp = n->right;
                delete n;
                return temp;
            }
            if (n->right == nullptr) {
                node* temp = n->left;
                delete n;
                return temp;
            }
            int ln = getln(n->right);
            n->val = ln;
            n->right = rm(ln, n->right);
        }
        return n;
    }

    int getln(node* n) {
        while (n->left != nullptr) n = n->left;
        return n->val;
    }

    int calc_height_and_fill_sets(node* n) {
        if (n == nullptr) return -1;

        int left_height = calc_height_and_fill_sets(n->left);
        int right_height = calc_height_and_fill_sets(n->right);

        n->height = 1 + std::max(left_height, right_height);

        if (n->left != nullptr) {
            if (n->left->left == nullptr && n->left->right == nullptr) {
                n->set_left.insert(1);
            }
            else {
                for (int i : n->left->set_left) {
                    n->set_left.insert(i + 1);
                }
                for (int i : n->left->set_right) {
                    n->set_left.insert(i + 1);
                }
            }
        }

        if (n->right != nullptr) {
            if (n->right->left == nullptr && n->right->right == nullptr) {
                n->set_right.insert(1);
            }
            else {
                for (int i : n->right->set_left) {
                    n->set_right.insert(i + 1);
                }
                for (int i : n->right->set_right) {
                    n->set_right.insert(i + 1);
                }
            }
        }

        return n->height;
    }

    void collect_req_vertex(node* n) {
        if (n == nullptr || n->height * 2 < height) return;

        for (int i : n->set_left) {
            if (n->set_right.count(height - i)) {
                req_verts.push_back(n->val);
                break;
            }
        }

        collect_req_vertex(n->left);
        collect_req_vertex(n->right);
    }

    int find_depth(int val) {
        node* curr = root;
        int depth = 0;
        while (curr != nullptr) {
            if (val == curr->val) return depth;
            if (val < curr->val) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
            depth++;
        }
        return -1;
    }

    void process() {
        height = calc_height_and_fill_sets(root);

        req_verts.clear();
        collect_req_vertex(root);

        depth = 0;
        for (int val : req_verts) {
            int d = find_depth(val);
            if (d > depth) depth = d;
        }

        req_verts.erase(std::remove_if(req_verts.begin(), req_verts.end(),
            [this](int val) { return find_depth(val) < depth; }),
            req_verts.end());

        if (req_verts.size() % 2 != 0) {
            std::sort(req_verts.begin(), req_verts.end());
            int mid = req_verts.size() / 2;
            rm(req_verts[mid], root);
        }
    }

    std::vector<int> v;
    std::vector<int> req_verts;
    node* root;
    int height = 0;
    int depth = 0;
};

// 1 set instead of 2 for every vertex
// look through the shortest set
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::ifstream fin("tst.in");
    if (!fin.is_open()) {
        std::ofstream fout("tst.out");
        return 1;
    }

    BST tree;
    int n;
    while (fin >> n) {
        tree.add(n);
    }
    fin.close();

    tree.process();
    tree.pre_order_traversal();

    std::ofstream fout("tst.out");
    for (int i : tree.v) {
        fout << i << "\n";
    }
    fout.close();

    return 0;
}