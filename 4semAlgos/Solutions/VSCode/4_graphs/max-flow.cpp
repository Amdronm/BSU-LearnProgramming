#include <iostream>
#include <vector>

using std::vector, std::pair, std::cin, std::cout;

using ull = unsigned long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t n, m;
    cin >> n >> m;

    vector<vector<pair<ull, ull>>> graph(n + 1);
    size_t u, v, c;
    while (m--) {
        cin >> u >> v >> c;
        graph[u].push_back({ v, c });
    }

    
    return 0;
}