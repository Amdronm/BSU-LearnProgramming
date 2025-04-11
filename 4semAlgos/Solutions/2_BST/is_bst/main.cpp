#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <cstdio>
#include <stack>
#include "limits.h"

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct elem {
	TreeNode* ptr;
	long long min;
	long long max;
};

bool look(TreeNode* node, long long int min, long long int max) {
	if (node == nullptr)
		return true;
	std::stack<elem> s;
	s.push({ node, min, max });
	while (!s.empty()) {
		elem it = s.top();
		s.pop();
		if (it.ptr->val < it.min || it.ptr->val >= it.max)
			return false;
		if (it.ptr->left != nullptr)
			s.push({ it.ptr->left, it.min, it.ptr->val });
		if (it.ptr->right != nullptr)
			s.push({ it.ptr->right, it.ptr->val, it.max });
	}
	return true;
}

int main() {
	FILE* fin = fopen("bst.in", "r");
	FILE* fout = fopen("bst.out", "w");
	int n = 0, r = 0;
	int scan_ret = fscanf(fin, "%d %d", &n, &r);
	TreeNode root(r);
	std::vector<TreeNode*> v = { &root };
	int val = 0, pos = 0;
	char c = 0;
	for (int i = 1; i < n; i++) {
		scan_ret = fscanf(fin, "%d %d %c", &val, &pos, &c);
		pos--;
		TreeNode* par = v[pos];
		TreeNode* kid = new TreeNode(val);
		if (c == 'L') {
			par->left = kid;
		}
		else {
			par->right = kid;
		}
		v.push_back(kid);
	}
	bool b = look(&root, LLONG_MIN, LLONG_MAX);
	fprintf(fout, (b) ? "YES" : "NO");
	return 0;
}