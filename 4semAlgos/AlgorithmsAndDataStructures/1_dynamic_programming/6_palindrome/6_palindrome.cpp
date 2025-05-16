#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

int main() {
	std::string s = "";
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	std::getline(fin, s);
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
	int ans = vec.front().back();
	std::vector<int> res;
	for (int i = 0, j = n; i <= n && j > 0; i++) {
		if (vec[i][j] > vec[i][j - 1] && vec[i][j] > vec[i + 1][j] && vec[i][j] > vec[i + 1][j - 1]) {
			res.push_back(j - 1);
			j--;
		}
		else if (vec[i][j] == vec[i][j - 1]) {
			j--;
			i--;
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
	fout << ans << std::endl;
	fout << rrr;
	return 0;
}