#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int m = 0, n = 0;
    std::cin >> m >> n;
    std::vector<int> h(m, 0);
    std::vector<int> b(n, 0);
    for (int i = 0; i < m; i++)
        std::cin >> h[i];
    for (int i = 0; i < n; i++)
        std::cin >> b[i];

    std::vector<std::vector<int>> v(m, std::vector<int>(n, -1));
    v[0][0] = h[0] + b[0];
    for (int j = 1; j < v[0].size(); j++)
        v[0][j] = std::min(v[0][j - 1], b[j] + h[0]);

    for (int i = 1; i < v.size(); i++) {
        for (int j = i; j < v[i].size(); j++) {
            if (v[i - 1][j - 1] < 0) {
                v[i][j] = -1;
            }
            else if (h[i] + b[j] > v[i - 1][j - 1]) {
                if (v[i][j - 1] == -1) {
                    v[i][j] = h[i] + b[j];
                }
                else {
                    v[i][j] = std::min(h[i] + b[j], v[i][j - 1]);
                }
            }
            else {
                v[i][j] = v[i][j - 1];
            }
        }
    }

    if (v.back().back() == -1) {
        std::cout << -1;
        return 0;
    }

    std::vector<int> res;
    for (int i = m - 1, j = n - 1; i >= 0 && j >= 0; j--) {
        if (v[i][j] == b[j] + h[i]) {
            res.push_back(j + 1);
            i--;
        }
    }
    std::reverse(res.begin(), res.end());
    for (int i : res)
        std::cout << i << " ";
    return 0;
}