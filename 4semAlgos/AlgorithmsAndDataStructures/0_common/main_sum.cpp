#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <set>
#include <algorithm>

int main() {
	FILE* input = fopen("input.txt", "r");
	std::set<int> set;
	int n;
	while (fscanf(input, "%d", &n) != EOF) {
		set.insert(n);
	}
	fclose(input);
	long long res = 0;
	std::for_each(set.begin(), set.end(), [&res](int a) {
		res += a;
	});

	FILE* output = fopen("output.txt", "w");
	fprintf(output, "%lld\n", res);
	fclose(output);
	return 0;
}