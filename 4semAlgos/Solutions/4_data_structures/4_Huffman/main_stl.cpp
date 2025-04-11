#include <fstream>
#include <queue>

using ll = long long;

std::queue<int> data;
std::queue<ll> sup;

static ll getmin() {
	if (sup.empty() || !data.empty() && data.front() <= sup.front()) {
		ll res = data.front();
		data.pop();
		return res;
	}
	else {
		ll res = sup.front();
		sup.pop();
		return res;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::ifstream fin("huffman.in");
	int n = 0;
	fin >> n;
	int val = 0;
	for (int i = 0; i < n; i++) {
		fin >> val;
		data.push(val);
	}
	ll n1 = 0, n2 = 0, result = 0;
	while (!data.empty()) {
		n1 = getmin();
		n2 = getmin();
		result += n1 + n2;
		sup.push(n1 + n2);
	}
	while (sup.size() > 1) {
		ll sf = sup.front();
		sup.pop();
		result += sf;
		if (sup.empty()) break;
		sf += sup.front();
		result += sup.front();
		sup.pop();
		sup.push(sf);
	}
	std::ofstream fout("huffman.out");
	fout << result;
	return 0;
}