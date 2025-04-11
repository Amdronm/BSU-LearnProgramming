#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>

struct Node {
	Node() = default;
	Node(int a) : val(a) {}
	~Node() = default;

	int val;
	Node* left = nullptr;
	Node* right = nullptr;
};

struct BST {
	BST() = default;
	BST(int a) : root(new Node(a)) {}
	~BST() {
		del(root);
	}

	void del(Node* node) {
		if (node == nullptr)
			return;
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			return;
		}
		del(node->left);
		del(node->right);
	}

	void add(int a) {
		add(a, root);
	}

	void add(int a, Node* node) {
		if (a == node->val)
			return;
		if (a < node->val) {
			if (node->left == nullptr) {
				node->left = new Node(a);
				return;
			}
			else {
				add(a, node->left);
			}
		}
		else {
			if (node->right == nullptr) {
				node->right = new Node(a);
				return;
			}
			else {
				add(a, node->right);
			}
		}
	}

	void order() {
		vec.clear();
		order(root);
	}

	void order(Node* node) {
		if (node == nullptr)
			return;
		vec.push_back(node->val);
		order(node->left);
		order(node->right);
	}

	Node* find(int a, Node* node) {
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

	Node* find_prev(int a, Node* node) {
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
		Node* n = find(a, root);
		if (n == nullptr)
			return;
		if (n->left == nullptr) {
			if (n == root) {
				root = n->right;
			}
			else {
				Node* prev = find_prev(a, root);
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
				Node* prev = find_prev(a, root);
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
		Node* r = n->right;
		bool bLeft = false;
		Node* pre = n;
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

	std::vector<int> vec;
	Node* root = nullptr;
};

int main() {
	FILE* input = fopen("bst.in", "r");
	int n = 0;
	fscanf_s(input, "%d", &n);
	int k = 0;
	fscanf_s(input, "%d", &k);
	n--;
	BST tree(n);
	while (fscanf_s(input, "%d", &n) != EOF)
		tree.add(n);
	fclose(input);
	tree.remove(k);
	tree.order();
	FILE* output = fopen("bst.out", "w");
	for (size_t i = 0; i < tree.vec.size(); i++) {
		fprintf(output, "%d\n", tree.vec[i]);
	}
	fclose(output);
	return 0;
}