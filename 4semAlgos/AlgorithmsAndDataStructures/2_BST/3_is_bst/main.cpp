#include <climits>
#include <fstream>
#include <vector>

using namespace std;

struct node {
    int val;
    long long min;
    long long max;
};

int main() {
    bool b = true;
    ifstream fin("bst.in");
    int n = 0, r = 0;
    fin >> n >> r;
    std::vector<node> v;
    v.reserve(n);
    v = { { r, LONG_LONG_MIN, LONG_LONG_MAX } };
    int val = 0, pos = 0;
    char c = 0;
    for (int i = 1; i < n; i++) {
        fin >> val >> pos >> c;
        pos--;
        if (c == 'L') {
            v.push_back({ val, v[pos].min, v[pos].val });
        } else {
            v.push_back({ val, v[pos].val, v[pos].max });
        }
        if (val < v.back().min || val >= v.back().max) {
            b = false;
            break;
        }
    }
    ofstream fout("bst.out");
    fout << ((b) ? "YES" : "NO");
    return 0;
}