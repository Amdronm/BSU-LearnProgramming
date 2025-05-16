#include <fstream>
#include <bitset>

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    long long n = 0;
    fin >> n;
    std::bitset<64> b(n);
    for (int i = 0; i < 64; i++) {
        if (b[i]) {
            fout << i << '\n';
        }
    }
    return 0;
}