#include <iostream>
#include <vector>
#include <algorithm>

void get(std::vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cin >> vec[i];
	}
}

static void print_vec(const std::vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	int n = 0;
	std::cin >> n;
	std::vector<int> a(n);
	std::vector<int> b(n);
	get(a);
	get(b);
	std::vector<std::vector<int>> vec(n + 1, std::vector<int>(n + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i - 1] == b[j - 1]) {
				vec[i][j] = vec[i - 1][j - 1] + 1;
			}
			else {
				vec[i][j] = std::max(vec[i][j - 1], vec[i - 1][j]);
			}
		}
	}
	std::vector<int> resa;
	std::vector<int> resb;
	for (int j = n, i = n; j > 0 && i > 0; j--) {
		if (vec[i][j] > vec[i - 1][j] && vec[i][j] > vec[i][j - 1] && vec[i][j] > vec[i - 1][j - 1]) {
			resa.push_back(i - 1);
			resb.push_back(j - 1);
			i--;
		}
		else if (vec[i][j] > vec[i][j - 1]) {
			i--;
			j++;
		}
	}
	std::reverse(resa.begin(), resa.end());
	std::reverse(resb.begin(), resb.end());
	std::cout << vec.back().back() << std::endl;
	print_vec(resa);
	print_vec(resb);
	return 0;
}