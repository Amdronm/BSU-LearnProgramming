#include <fstream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    size_t m = 0, c = 0, n = 0;
    fin >> m >> c >> n;
    std::vector<int> table(m, -1);
    int x = 0;
    size_t h = 0;
    for (size_t i = 0; i < n; i++) {
        fin >> x;
        h = x % m;
        if (table[h] == x || table[h] == -1) {
            table[h] = x;
        }
        else {
            for (size_t j = 1; j < m; j++) {
                h = ((x % m) + j * c) % m;
                if (table[h] == x || table[h] == -1) {
                    table[h] = x;
                    break;
                }
            }
        }
    }
    for (size_t i = 0; i < table.size(); i++) {
        fout << table[i] << " ";
    }
    return 0;
}