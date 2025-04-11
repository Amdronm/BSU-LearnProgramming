#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream fin("in.txt");
	int x = 0, y = 0, z = 0;
	fin >> x >> y >> z;
	z = ((x + y < z) ? (x + y) : z);
	std::string a, b;
	std::getline(fin, a);
	std::getline(fin, a);
	std::getline(fin, b);
	std::vector<std::vector<int>> mat(a.size() + 1, std::vector<int>(b.size() + 1, 0));
	for (int j = 1, i = 0; j < mat.front().size(); j++) {
		mat[i][j] = mat[i][j - 1] + y;
	}
	for (int i = 1, j = 0; i < mat.size(); i++) {
		mat[i][j] = mat[i - 1][j] + x;
	}
	for (int i = 1; i < mat.size(); i++) {
		for (int j = 1; j < mat[i].size(); j++) {
			mat[i][j] = std::min({mat[i][j - 1] + y, mat[i - 1][j] + x
				, mat[i - 1][j - 1] + ((a[i - 1] == b[j - 1]) ? 0 : z)});
		}
	}
	std::ofstream fout("out.txt");
	fout << mat.back().back();
	return 0;
}