// FROG TASK



////#define _CRT_SECURE_NO_WARNINGS
//
//#include <cstdio>
//#include <vector>
//#include <algorithm>
//
////fixed not here
// 
//
//
//int main() {
//	int n = 0;
//	scanf_s("%d", &n);
//	if (n < 3) {
//		printf("-1");
//		return 0;
//	}
//	std::vector<int> vec;
//	int a = 0;
//	for (int i = 0; i < n; i++) {
//		scanf_s("%d", &a);
//		vec.push_back(a);
//	}
//	if (n == 3 || n == 4) {
//		int res = vec.front() + vec.back();
//		printf("%d\n1 %d", res, vec.size());
//		return 0;
//	}
//	if (n == 5) {
//		int res = vec.front() + vec.back() + vec.at(2);
//		printf("%d\n1 3 5", res);
//		return 0;
//	}
//
//	std::vector<int> res = { n };
//	std::vector<int> maxs(vec.size());
//	std::copy(vec.begin(), vec.begin() + 5, maxs.begin());
//	maxs[1] = -1;
//	maxs[2] += vec[0];
//	maxs[3] += vec[0];
//	maxs[4] += maxs[2];
//	for (int i = 5; i < vec.size(); i++) {
//		if (maxs[i - 2] > maxs[i - 3]) {
//			maxs[i] = maxs[i - 2] + vec[i];
//		}
//		else {
//			maxs[i] = maxs[i - 3] + vec[i];
//		}
//	}
//	for (int i = vec.size() - 1; i >= 2;) {
//		int a = maxs[i] - vec[i];
//		if (maxs[i - 2] == a) {
//			res.push_back(i - 1);
//			i -= 2;
//		}
//		else {
//			res.push_back(i - 2);
//			i -= 3;
//		}
//	}
//	std::reverse(res.begin(), res.end());
//	printf("%d\n", maxs.back());
//	for (int i = 0; i < res.size(); i++) {
//		printf("%d ", res[i]);
//	}
//	return 0;
//}
//
// 
// 
// ONES TASK
// 
//
//#include <cstdio>
//#include <bitset>
//
//using ull = unsigned long long;
//const int MOD = 1000000007;
//
//ull binpow(const ull a, int b) {
//	std::bitset<32> s(b);
//	ull res = 1;
//	for (int i = s.size() - 1; i >= 0; i--) {
//		if (s[i]) {
//			ull aa = a;
//			for (int j = i; j; j--) {
//				aa *= aa;
//				aa %= MOD;
//			}
//			res *= aa;
//			res %= MOD;
//		}
//	}
//	return res;
//}
//
//int main() {
//	int n = 0;
//	int k = 0;
//	scanf_s("%d %d", &n, &k);
//	if (k == 0 || k == n) {
//		printf("1");
//		return 0;
//	}
//	int nmk = n - k;
//	ull den = 1;
//	for (int i = 2; i <= nmk; i++) {
//		den *= i;
//		den %= MOD;
//	}
//	ull nom = 1;
//	for (int i = k + 1; i <= n; i++) {
//		nom *= i;
//		nom %= MOD;
//	}
//	ull res = nom * binpow(den, MOD - 2);
//	res %= MOD;
//	printf("%lld", res);
//	return 0;
//}

// 2 3 5 10
// 20 5 35 _4 25
// _1 2 3 4 5 6 7 8 _
// _10 9 6 5 3 1 _


// MATRIX TASK

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <algorithm>

std::vector<int> vec;
int res = 0;

void calc(int l, int r) {
	
}

void test(void) {
	vec.clear();
	vec = { 3, 2, 4, 7, 3, 4 };
	int n = vec.size();
	calc(0, n);
	printf("%d", res);
}

int main() {
	FILE* input = fopen("input.txt", "r");
	int n = 0;
	fscanf_s(input, "%d", &n);
	vec.resize(n + 1);
	int a = 0, b = 0;
	for (int i = 0; i < n; i++) {
		fscanf_s(input, "%d %d", &a, &b);
		vec[i] = a;
	}
	fclose(input);
	vec[n] = b;
	calc(0, n + 1);
	FILE* output = fopen("output.txt", "w");
	fprintf(output, "%d", res);
	fclose(output);


	//test();
	return 0;
}