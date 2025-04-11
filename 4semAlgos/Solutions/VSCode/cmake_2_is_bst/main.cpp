#include <vector>
#include <cstdio>
#include "limits.h"

struct node {
	int val;
	long long min;
	long long max;
};

int main() {
	printf("%d", sizeof(__int128_t));
	bool b = true;
	FILE* fin = fopen("bst.in", "r");
	int n = 0, r = 0;
	fscanf(fin, "%d %d", &n, &r);
	// std::vector<node> v(n, {0, 0, 0});
	// v[0] = {r, LONG_LONG_MIN, LONG_LONG_MAX};
	std::vector<node> v;
	v.reserve(n);
	v = {{r, LONG_LONG_MIN, LONG_LONG_MAX}};
	int val = 0, pos = 0;
	char c = 0;
	for (int i = 1; i < n; i++) {
		fscanf(fin, "%d %d %c", &val, &pos, &c);
		pos--;
		if (c == 'L') {
			// v[i] = {val, v[pos].min, v[pos].val};
			v.push_back({val, v[pos].min, v[pos].val});
		} else {
			v.push_back({val, v[pos].val, v[pos].max});
			// v[i] = {val, v[pos].val, v[pos].max};
		}
		// if (val < v[i].min || val >= v[i].max) {
		if (val < v.back().min || val >= v.back().max) {
			b = false;
			break;
		}
	}
	fclose(fin);
	FILE* fout = fopen("bst.out", "w");
	fprintf(fout, (b) ? "YES" : "NO");
	fclose(fout);
	return 0;
}