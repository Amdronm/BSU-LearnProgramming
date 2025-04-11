#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
	std::string s = "";
	std::getline(std::cin, s);
	int n = s.size();
	std::vector<std::vector<int>> vec(n + 1, std::vector<int>(n + 1, 0));
	for (int i = 0, j = 1; j <= n; i++, j++) {
		vec[i][j] = 1;
	}
	for (int i = n - 2; i >= 0 ; i--) {
		for (int j = i + 2; j <= n; j++) {
			if (s[i] == s[j - 1]) {
				vec[i][j] = vec[i + 1][j - 1] + 2;
			}
			else {
				vec[i][j] = std::max(vec[i + 1][j], vec[i][j - 1]);
			}
		}
	}
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size(); j++) {
			std::cout << vec[i][j] << " ";
		}
		std::cout << std::endl;
	}
	int ans = vec.front().back();
	std::vector<int> res;
	for (int i = 0, j = n; i <= n && j > 0; i++) {
		if (vec[i][j] <= 0)
			break;
		if (vec[i][j] > vec[i][j - 1] && vec[i][j] > vec[i + 1][j] && vec[i][j] > vec[i + 1][j - 1]) {
			res.push_back(j - 1);
			j--;
			continue;
		}
		if (vec[i][j] == vec[i][j - 1] || vec[i][j] == vec[i + 1][j]) {
            if (s[i] - s[j - 1] < 0) {
                i--;
                j--;
            }
			continue;
		}
		if (vec[i][j] == vec[i][j - 1]) {
			i--;
			j--;
		}
	}
	std::string rrr;
	for (int i : res) {
		rrr += s[i];
	}
	std::string rr = rrr;
	std::reverse(rr.begin(), rr.end());
	if (ans % 2) {
		rr.erase(rr.begin());
		rrr += rr;
	}
	else {
		rrr += rr;
	}
	std::cout << rrr;
	return 0;
}