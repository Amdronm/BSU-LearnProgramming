#include <fstream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    size_t n = 0;
    std::string init, procd;
    fin >> n >> init >> procd;
    return 0;
}