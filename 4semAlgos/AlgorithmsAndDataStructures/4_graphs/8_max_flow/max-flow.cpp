#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector, std::cin, std::cout, std::endl;

using ll = long long;

struct edge {
    ll v;
    ll cap;
    ll flow;
    ll rev;
};

class Dinitz {
public:
    Dinitz(ll n) : n(n), graph(n + 1), level(n + 1), iter(n + 1) {}

    void add_edge(ll u, ll v, ll cap) {
        graph[u].push_back({ v, cap, 0, static_cast<ll>(graph[v].size()) });
        graph[v].push_back({ u, 0, 0, static_cast<ll>(graph[u].size() - 1) });
    }

    ll max_flow() {
        ll flow = 0;
        while (bfs()) {
            std::fill(iter.begin(), iter.end(), 0);
            while (ll pushed = dfs(1, __LONG_LONG_MAX__)) {
                flow += pushed;
            }
        }
        return flow;
    }

private:
    ll n;
    vector<vector<edge>> graph;
    vector<ll> level;
    vector<ll> iter;

    bool bfs() {
        std::fill(level.begin(), level.end(), -1);
        level[1] = 0;
        std::queue<ll> q;
        q.push(1);
        while (!q.empty()) {
            ll v = q.front();
            q.pop();
            for (const edge& e : graph[v]) {
                if (e.flow < e.cap && level[e.v] == -1) {
                    level[e.v] = level[v] + 1;
                    q.push(e.v);
                }
            }
        }
        return level[n] != -1;
    }

    ll dfs(ll v, ll f) {
        if (v == n) return f;
        for (ll i = iter[v]; i < graph[v].size(); ++i) {
            edge& e = graph[v][i];
            if (e.flow < e.cap && level[e.v] == level[v] + 1) {
                ll pushed = dfs(e.v, std::min(f, e.cap - e.flow));
                if (pushed > 0) {
                    e.flow += pushed;
                    graph[e.v][e.rev].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
};

int main() {    
    ll n = 0, m = 0;
    cin >> n >> m;

    Dinitz dinitz(n);
    ll u, v, c;
    while (m--) {
        cin >> u >> v >> c;
        dinitz.add_edge(u, v, c);
    }

    cout << dinitz.max_flow() << endl;
    return 0;
}