#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

static void print_vec(const std::vector<short>& v) {
	for (short i : v)
		std::cout << i << " ";
	std::cout << '\n';
}

static void print_mat(const std::vector<std::vector<short>>& m) {
	for (const auto& i : m)
		print_vec(i);
	std::cout << '\n';
}

int main() {
	std::string s = "";
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	//std::getline(std::cin, s);
	std::getline(fin, s);
	int n = s.size();
	std::vector<std::vector<short>> vec(n + 1, std::vector<short>(n + 1, 0));
	for (int i = 0, j = 1; j <= n; i++, j++)
		vec[i][j] = 1;
	for (int i = n - 2; i >= 0; i--)
		for (int j = i + 2; j <= n; j++)
			if (s[i] == s[j - 1])
				vec[i][j] = vec[i + 1][j - 1] + 2;
			else
				vec[i][j] = std::max(vec[i + 1][j], vec[i][j - 1]);

	print_mat(vec);
	int ans = vec.front().back();
	std::string resb, resl;
	for (int i = 0, j = n; i <= n && j > i; i++) {
		short ij = vec[i][j];
		if ((ij > vec[i+1][j] && ij > vec[i][j-1] && ij > vec[i+1][j-1])
			|| ij == vec[i+1][j-1] + 2
			&& (ij == vec[i][j-1] && ij != vec[i+1][j] && ij != vec[i+1][j-1] && vec[i+1][j] != vec[i+1][j-1]
				|| ij == vec[i+1][j] && ij != vec[i][j-1] && ij != vec[i+1][j-1] && vec[i][j-1] != vec[i+1][j-1])) {
			resb += s[j - 1];
			j--;
		}
		else if (ij == vec[i][j-1] && ij != vec[i+1][j]
			|| ij == vec[i][j-1] && ij == vec[i+1][j] && s[j-1] < s[i]) {
			j--;
			i--;
		}
	}
	std::string rr = resb;
	std::reverse(rr.begin(), rr.end());
	if (ans % 2) {
		rr.erase(rr.begin());
		resb += rr;
	}
	else {
		resb += rr;
	}
	//std::cout << ans << std::endl;
	//std::cout << resb;
	fout << ans << std::endl;
	fout << resb;
	return 0;
}