#include <fstream>

using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;
	
	Node(int _value) : value(_value), left(nullptr), right(nullptr) {}
};

struct BinarySearchTree {
	BinarySearchTree() : root(nullptr) {}

	void insert(int _value) {
		if (root == nullptr) {
			root = new Node(_value);
			return;
		}
		Node* current = root;
		Node* prev = current;
		while (current != nullptr) {
			if (_value < current->value) {
				prev = current;
				current = current->left;
			}
			else if (_value > current->value) {
				prev = current;
				current = current->right;
			}
			else {
				return;
			}
		}
		if (_value < prev->value)
			prev->left = new Node(_value);
		else
			prev->right = new Node(_value);
	}

	void preorder() {
		preorder(root);
	}

	void preorder(Node* node) {
		if (node == nullptr) return;
		fout << node->value << '\n';
		preorder(node->left);
		preorder(node->right);
	}

	ofstream fout = ofstream("output.txt");
	Node* root;
};

int main() {
	ifstream fin("input.txt");
	int n = 0;
	BinarySearchTree tree;
	while (!fin.eof()) {
		fin >> n;
		tree.insert(n);
	}
	tree.preorder();
	return 0;
}