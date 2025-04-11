#include <fstream>
#include <vector>
#include <queue>

using std::vector;
using std::pair;

using ull = unsigned long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    size_t n = 0, m = 0;
    fin >> n >> m;

    size_t u, v, w;
    vector<vector<pair<ull, ull>>> graph(n + 1);
    while (m--) {
        fin >> u >> v >> w;
        graph[u].push_back({ w, v });
        graph[v].push_back({ w, u });
    }

    vector<ull> dist(n + 1, LLONG_MAX);
    vector<bool> procd(n + 1, false);
    std::priority_queue<pair<ull, ull>, vector<pair<ull, ull>>, std::greater<pair<ull, ull>>> pq;
    pq.push({ 0, 1 });

    while (!pq.empty()) {
        size_t w = pq.top().first;
        size_t u = pq.top().second;
        pq.pop();

        if (procd[u]) continue;
        procd[u] = true;
        dist[u] = w;

        for (const auto& e : graph[u]) {
            if (procd[e.second]) continue;
            pq.push({ e.first + w, e.second });
        }
    }

    fout << dist.back();
    return 0;
}