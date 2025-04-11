#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <algorithm>

std::vector<int> vec;

static int get() {
	FILE* fin = fopen("input.txt", "r");
	int n = 0;
	fscanf_s(fin, "%d", &n);
	vec.resize(n, 0);
	for (int i = 0; i < n; i++) {
		fscanf_s(fin, "%d", &vec[i]);
	}
	fclose(fin);
	return n;
}

static void give(int res) {
	FILE* fout = fopen("output.txt", "w");
	fprintf(fout, "%d", res);
	fclose(fout);
}

int main() {
	int n = get();
	for (int i = 1; i < vec.size(); i++) {
		if (vec[i - 1] >= vec[i]) {
			auto it = std::lower_bound(vec.begin(), vec.begin() + i, vec[i]);
			*it = vec[i];
			vec.erase(vec.begin() + i);
			i--;
		}
	}
	give(vec.size());
	return 0;
}