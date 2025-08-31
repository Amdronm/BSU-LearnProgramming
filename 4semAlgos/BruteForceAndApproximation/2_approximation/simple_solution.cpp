#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const long long kInf = 4e18;

ifstream fin("input.txt");
ofstream fout("output.txt");

class Dinitz {
public:
    struct Edge {
        int to;
        long long capacity;
        int rev;
    };

    Dinitz(int cap_val)
        : size_(cap_val),
          graph_(cap_val),
          level_(cap_val),
          iter_(cap_val) {}

    void AddEdge(int u, int v, long long cap) {
        graph_[u].push_back({v, cap, (int)graph_[v].size()});
        graph_[v].push_back({u, 0, (int)graph_[u].size() - 1});
    }

    long long GetMaxFlow(int s, int t) {
        long long total_flow = 0;
        while (Bfs(s, t)) {
            fill(iter_.begin(), iter_.end(), 0);
            long long pushed_flow;
            while ((pushed_flow = Dfs(s, t, kInf)) > 0) {
                total_flow += pushed_flow;
            }
        }
        return total_flow;
    }

    vector<bool> GetReachableNodes(int s) {
        vector<bool> reachable(size_, false);
        queue<int> qu;
        qu.push(s);
        reachable[s] = true;
        while (!qu.empty()) {
            int u = qu.front();
            qu.pop();
            for (const auto& edge : graph_[u]) {
                if (edge.capacity > 0 && !reachable[edge.to]) {
                    reachable[edge.to] = true;
                    qu.push(edge.to);
                }
            }
        }
        return reachable;
    }

private:
    bool Bfs(int s, int t) {
        fill(level_.begin(), level_.end(), -1);
        queue<int> qu;
        level_[s] = 0;
        qu.push(s);
        while (!qu.empty()) {
            int u = qu.front();
            qu.pop();
            for (const auto& edge : graph_[u]) {
                if (edge.capacity > 0 && level_[edge.to] < 0) {
                    level_[edge.to] = level_[u] + 1;
                    qu.push(edge.to);
                }
            }
        }
        return level_[t] != -1;
    }

    long long Dfs(int u, int t, long long flow) {
        if (u == t) {
            return flow;
        }
        for (int& i = iter_[u]; i < graph_[u].size(); ++i) {
            Edge& e = graph_[u][i];
            if (e.capacity > 0 && level_[u] < level_[e.to]) {
                long long pushed = Dfs(e.to, t, min(flow, e.capacity));
                if (pushed > 0) {
                    e.capacity -= pushed;
                    graph_[e.to][e.rev].capacity += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    int size_;
    vector<vector<Edge>> graph_;
    vector<int> level_;
    vector<int> iter_;
};

class Solver {
private:
    struct OriginalEdge {
        int u, v;
        long long weight;
        int id;
    };

    int nodes_;
    int num_edges_;
    vector<OriginalEdge> edges_;
    int num_terms_;
    vector<int> terminals_;
    vector<long long> edge_weights_;
    long long totalSumWeights_;

public:
    Solver() : nodes_(0), num_edges_(0), num_terms_(0), totalSumWeights_(0) {
        ios_base::sync_with_stdio(false);
    }

    void ReadInput() {
        fin >> nodes_ >> num_edges_;
        edges_.resize(num_edges_);
        edge_weights_.resize(num_edges_ + 1);
        totalSumWeights_ = 0;
        for (int i = 0; i < num_edges_; ++i) {
            fin >> edges_[i].u >> edges_[i].v >> edges_[i].weight;
            edges_[i].id = i + 1;
            totalSumWeights_ += edges_[i].weight;
            edge_weights_[edges_[i].id] = edges_[i].weight;
        }
        fin >> num_terms_;
        terminals_.resize(num_terms_);
        for (int i = 0; i < num_terms_; ++i) {
            fin >> terminals_[i];
        }
    }

    void Process() {
        long long super_edge_cap = totalSumWeights_ + 1;
        if (super_edge_cap <= 0) {
            super_edge_cap = 1;
        }

        vector<pair<long long, vector<int>>> isolating_cuts;

        for (int i = 0; i < num_terms_; ++i) {
            int source = terminals_[i];
            int sink = nodes_ + 1;

            Dinitz dinitz(nodes_ + 2);
            for (const auto& edge : edges_) {
                dinitz.AddEdge(edge.u, edge.v, edge.weight);
                dinitz.AddEdge(edge.v, edge.u, edge.weight);
            }
            for (int j = 0; j < num_terms_; ++j) {
                if (i == j) {
                    continue;
                }
                int other_term = terminals_[j];
                dinitz.AddEdge(other_term, sink, super_edge_cap);
            }

            long long flow_val = dinitz.GetMaxFlow(source, sink);
            vector<bool> reachable_set = dinitz.GetReachableNodes(source);
            vector<int> current_cut_i_ds;
            for (const auto& edge : edges_) {
                if (reachable_set[edge.u] != reachable_set[edge.v]) {
                    current_cut_i_ds.push_back(edge.id);
                }
            }
            isolating_cuts.push_back({flow_val, current_cut_i_ds});
        }

        sort(isolating_cuts.begin(), isolating_cuts.end());

        set<int> final_cut_i_ds;
        for (int i = 0; i < num_terms_ - 1; ++i) {
            if (i < isolating_cuts.size()) {
                for (int edge_id : isolating_cuts[i].second) {
                    final_cut_i_ds.insert(edge_id);
                }
            }
        }

        long long final_weight = 0;
        for (int id_val : final_cut_i_ds) {
            final_weight += edge_weights_[id_val];
        }

        fout << final_weight << endl;
        fout << final_cut_i_ds.size() << endl;

        vector<int> result(final_cut_i_ds.begin(), final_cut_i_ds.end());
        sort(result.begin(), result.end());
        for (int id_val : result) {
            fout << id_val << endl;
        }
    }
};

int main() {
    Solver sol;
    sol.ReadInput();
    sol.Process();
    fin.close();
    fout.close();
    return 0;
}