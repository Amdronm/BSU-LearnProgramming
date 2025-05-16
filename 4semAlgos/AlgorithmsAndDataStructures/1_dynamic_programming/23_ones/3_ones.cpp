#include <bitset>
#include <iostream>

using namespace std;

using ull = unsigned long long;
const int MOD = 1000000007;

ull binpow(const ull a, int b) {
	std::bitset<32> s(b);
	ull res = 1;
	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[i]) {
			ull aa = a;
			for (int j = i; j; j--) {
				aa *= aa;
				aa %= MOD;
			}
			res *= aa;
			res %= MOD;
		}
	}
	return res;
}

int main() {
	int n = 0;
    int k = 0;
    cin >> n >> k;
    if (k == 0 || k == n) {
        cout << 1;
		return 0;
	}
	int nmk = n - k;
	ull den = 1;
	for (int i = 2; i <= nmk; i++) {
		den *= i;
		den %= MOD;
	}
	ull nom = 1;
	for (int i = k + 1; i <= n; i++) {
		nom *= i;
		nom %= MOD;
	}
	ull res = nom * binpow(den, MOD - 2);
    res %= MOD;
    cout << res;
	return 0;
}