#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector, std::string, std::size_t;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    size_t n;
    fin >> n;
    string s1, s2;
    fin >> s1;
    fin >> s2;
    if (s1 == s2) {
        fout << "0";
        return 0;
    }

    string s = s2 + "$" + s1 + s1;
    vector<size_t> p(s.size(), 0);

    for (size_t i = 1; i < p.size(); i++) {
        size_t k = p[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = p[k - 1];
        }
        if (s[k] == s[i]) {
            p[i] = k + 1;
        }
        else {
            p[i] = k;
        }
    }

    auto it = std::max_element(p.begin(), p.end());
    if (*it < n) {
        fout << "-1";
        return 0;
    }
    size_t res = n - (p.end() - it - 1);
    fout << res;

    return 0;
}
