#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Dinitz {
public:
    Dinitz(int nodes) : n_(nodes), source_(1), sink_(n_) {
        graph_.resize(n_ + 1);
        level_.resize(n_ + 1, -1);
        iter_.resize(n_ + 1, 0);
    }

    void AddEdge(int u, int v, long long cap) {
        graph_[u].push_back({v, cap, (int)graph_[v].size()});
        graph_[v].push_back({u, 0, (int)graph_[u].size() - 1});
    }

    long long CalculateMaxFlow() {
        if (source_ == sink_) {
            return 0;
        }
        long long total_flow = 0;

        while (Bfs()) {
            fill(iter_.begin(), iter_.end(), 0);
            while (long long pushed = Dfs(source_, kInf)) {
                total_flow += pushed;
            }
        }
        return total_flow;
    }

private:
    static const long long kInf = LLONG_MAX;

    struct Edge {
        int to;
        long long capacity;
        int rev;
    };

    int n_;
    int source_;
    int sink_;

    vector<vector<Edge>> graph_;
    vector<int> level_;
    vector<int> iter_;

    bool Bfs() {
        fill(level_.begin(), level_.end(), -1);
        level_[source_] = 0;
        queue<int> q;
        q.push(source_);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const auto& edge : graph_[u]) {
                if (edge.capacity > 0 && level_[edge.to] == -1) {
                    level_[edge.to] = level_[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level_[sink_] != -1;
    }

    long long Dfs(int u, long long pushed) {
        if (pushed == 0 || u == sink_) {
            return pushed;
        }
        for (int& idx = iter_[u]; idx < graph_[u].size(); ++idx) {
            Edge& edge = graph_[u][idx];

            if (level_[edge.to] != level_[u] + 1 || edge.capacity == 0) {
                continue;
            }
            long long flow = Dfs(edge.to, min(pushed, edge.capacity));

            if (flow == 0) {
                continue;
            }
            edge.capacity -= flow;
            graph_[edge.to][edge.rev].capacity += flow;

            return flow;
        }
        return 0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int m;
    cin >> n >> m;
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    Dinitz din(n);

    for (int i = 0; i < m; ++i) {
        int u;
        int v;
        long long w;
        cin >> u >> v >> w;
        din.AddEdge(u, v, w);
    }

    cout << din.CalculateMaxFlow() << endl;

    return 0;
}