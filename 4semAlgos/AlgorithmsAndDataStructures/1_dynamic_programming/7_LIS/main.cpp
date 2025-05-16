#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

std::vector<int> vec;

static int get() {
	std::ifstream fin("input.txt");
	int n = 0;
	fin >> n;
	vec.resize(n, 0);
	for (int i = 0; i < n; i++) {
        fin >> vec[i];
	}
	return n;
}

static void give(int res) {
	ofstream fout("output.txt");
	fout << res;
}

int main() {
	int n = get();
	for (int i = 1; i < vec.size(); i++) {
		if (vec[i - 1] >= vec[i]) {
			auto it = std::lower_bound(vec.begin(), vec.begin() + i, vec[i]);
			*it = vec[i];
			vec.erase(vec.begin() + i);
			i--;
		}
	}
	give(vec.size());
	return 0;
}