#include <fstream>
#include <vector>

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int n = 0;
    fin >> n;
    std::vector<int> v(n);
    fin >> v[0];
    for (int i = 1; i < n; i++) {
        fin >> v[i];
        if (v[i] < v[(i + 1) / 2 - 1]) {
            fout << "No";
            return 0;
        }
    }
    fout << "Yes";
    return 0;
}