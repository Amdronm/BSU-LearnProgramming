// FROG TASK


#include <vector>
#include <algorithm>

#include <iostream>

using namespace std;

int main() {
	int n = 0;
    cin >> n;
    if (n < 3) {
		cout << -1;
		return 0;
	}
	std::vector<int> vec;
	int a = 0;
	for (int i = 0; i < n; i++) {
		cin >> a;
		vec.push_back(a);
	}
	if (n == 3 || n == 4) {
		int res = vec.front() + vec.back();
		cout << res << "\n1 " << vec.size();
		return 0;
	}
	if (n == 5) {
		int res = vec.front() + vec.back() + vec.at(2);
		cout << res << "\n1 3 5";
		return 0;
	}

	std::vector<int> res = { n };
	std::vector<int> maxs(vec.size());
	std::copy(vec.begin(), vec.begin() + 5, maxs.begin());
	maxs[1] = -1;
	maxs[2] += vec[0];
	maxs[3] += vec[0];
	maxs[4] += maxs[2];
	for (int i = 5; i < vec.size(); i++) {
		if (maxs[i - 2] > maxs[i - 3]) {
			maxs[i] = maxs[i - 2] + vec[i];
		}
		else {
			maxs[i] = maxs[i - 3] + vec[i];
		}
	}
	for (int i = vec.size() - 1; i >= 2;) {
		int a = maxs[i] - vec[i];
		if (maxs[i - 2] == a) {
			res.push_back(i - 1);
			i -= 2;
		}
		else {
			res.push_back(i - 2);
			i -= 3;
		}
	}
	std::reverse(res.begin(), res.end());
	cout << maxs.back() << "\n";
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
	return 0;
}

