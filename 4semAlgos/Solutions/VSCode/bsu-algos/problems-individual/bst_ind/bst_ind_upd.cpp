#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>

struct node {
    int val;
    node* left;
    node* right;
    std::unordered_set<int> set;
    node(int a) : val(a), left(nullptr), right(nullptr) {}
};

struct BST {
    struct vert {
        int val;
        int depth;
    };

    BST() : root(nullptr) {}
    BST(int val) : root(new node(val)), vert_numb(1) {}

    void add(int key) {
        depth = 0;
        node* n = root;
        node* prev = n;
        while (n != nullptr) {
            prev = n;
            if (key < n->val) {
                n = n->left;
                depth++;
            }
            else if (key > n->val) {
                n = n->right;
                depth++;
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
        height = std::max(depth, height);
        vert_numb++;
    }

    void pre_order_traversal() {
        v.clear();
        v.reserve(vert_numb);
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

    void fill_sets_collect_verts(node* n, int d) {
        if (n == nullptr) return;

        fill_sets_collect_verts(n->left, d + 1);
        fill_sets_collect_verts(n->right, d + 1);

        if (n->right == nullptr && n->left == nullptr) {
            n->set.insert(1);
            return;
        }

        if (n->left != nullptr && n->right == nullptr) {
            for (int i : n->left->set) {
                n->set.insert(i + 1);
            }
            return;
        }
        if (n->left == nullptr && n->right != nullptr) {
            for (int i : n->right->set) {
                n->set.insert(i + 1);
            }
            return;
        }
        bool flag = true;
        if (n->left->set.size() < n->right->set.size()) {
            for (int i : n->left->set) {
                n->set.insert(i + 1);
                if (flag && n->right->set.count(height - i)) {
                    req_verts.push_back({ n->val, d });
                    flag = false;
                }
            }
            for (int i : n->right->set) {
                n->set.insert(i + 1);
            }
            return;
        }
        for (int i : n->right->set) {
            n->set.insert(i + 1);
            if (flag && n->left->set.count(height - i)) {
                req_verts.push_back({ n->val, d });
                flag = false;
            }
        }
        for (int i : n->left->set) {
            n->set.insert(i + 1);
        }
    }

    void process() {
        req_verts.reserve(vert_numb);
        fill_sets_collect_verts(root, 0);

        int max_d = 0;

        for (const auto& i : req_verts) {
            if (max_d < i.depth) {
                max_d = i.depth;
            }
        }

        std::vector<vert> compl_vec;
        compl_vec.reserve(req_verts.size());
        for (size_t i = 0; i < req_verts.size(); i++) {
            if (req_verts[i].depth == max_d) {
                compl_vec.push_back(req_verts[i]);
            }
        }

        if (compl_vec.size() % 2 != 0) {
            std::sort(compl_vec.begin(), compl_vec.end(), [](vert a, vert b) {return a.val < b.val;});
            int mid = compl_vec.size() / 2;
            rm(compl_vec[mid].val, root);
        }
    }

    std::vector<int> v;
    std::vector<vert> req_verts;
    node* root;
    int height = 0;
    int depth = 0;
    size_t vert_numb = 0;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::ifstream fin("tst.in");
    fin.tie(nullptr);

    int n;
    fin >> n;
    BST tree(n);
    while (fin >> n) {
        tree.add(n);
    }

    tree.process();
    tree.pre_order_traversal();

    std::ofstream fout("tst.out");
    fout.tie(nullptr);
    for (int i : tree.v) {
        fout << i << "\n";
    }
    return 0;
}