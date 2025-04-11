//#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>

void bin_search_prnt(const std::vector<int>& vec, int key) {
	if (vec.empty()) {
		printf("0 0 0\n");
		return;
	}
	int b = 0;
	int l = 0;
	int r = vec.size() - 1;
	int m = 0;
	int nResL = 0;
	while (l < r) {
		m = (r + l) / 2;
		if (key <= vec[m]) {
			r = m;
		}
		else {
			if (l + 1 == r && m == l) {
				l++;
				break;
			}
			else {
				l = m;
			}
		}
	}
	r = vec.size() - 1;
	if (vec[l] < key)
		l++;
	nResL = l;
	while (l < r) {
		m = (r + l) / 2 + (r + l) % 2;
		if (key >= vec[m]) {
			l = m;
		}
		else {
			if (l + 1 == r && m == r) {
				r--;
				break;
			}
			else {
				r = m;
			}
		}
	}
	if (vec[r] <= key)
		r++;
	if (nResL == r) {
		printf("0 %d %d\n", r, r);
	}
	else {
		printf("1 %d %d\n", nResL, r);
	}
}

int main() {
	int n = 0;
	int a = 0;
	scanf_s("%d", &n);
	std::vector<int> vec;
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &a);
		vec.push_back(a);
	}
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &a);
		bin_search_prnt(vec, a);
	}
	return 0;
}