#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using std::vector, std::size_t;

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

class Solution {
public:
    Solution() {
        fin >> n;
        n++;

        terminals.resize(n);
        is_rep.resize(n, false);
        for (size_t i = 1; i < n; i++) {
            fin >> terminals[i];
        }

        orig_graph.resize(n);
        size_t u, v;
        while (fin >> u >> v) {
            orig_graph[u].push_back(v);
        }
        result.reserve(n);
    }

    ~Solution() = default;

    void process() {
        kos_sha_algo();
        rm_sources();
        print_result();
    }

private:
    void rm_sources() {
        vector<bool> degs(n, true);
        for (size_t i = 1; i < n; i++) {
            for (size_t j : graph[i]) {
                degs[j] = false;
            }
        }

        result.clear();
        result.reserve(n);
        for (size_t i = 1; i < n; i++) {
            if (degs[i] && is_rep[i]) {
                result.push_back(i);
            }
        }
    }

    void create_rev_graph() {
        rev_graph.resize(n);
        for (size_t i = 1; i < n; i++) {
            for (size_t j : orig_graph[i]) {
                rev_graph[j].push_back(i);
            }
        }
    }

    void kos_sha_algo() {
        ord.reserve(n);
        create_rev_graph();
        linked_comp.reserve(n);
        vis.resize(n, false);
        for (size_t i = 1; i < n; i++) {
            if (!vis[i]) {
                dfs1(i);
            }
        }
        std::fill(vis.begin(), vis.end(), false);
        std::reverse(ord.begin(), ord.end());
        vector<vector<size_t>> cond_graph(n);

        for (size_t i : ord) {
            if (!vis[i]) {
                linked_comp.clear();
                dfs2(i);
                shrink(cond_graph);
            }
        }
        graph = cond_graph;
    }

    void dfs1(size_t v) {
        vis[v] = true;
        for (size_t i : orig_graph[v]) {
            if (!vis[i]) {
                dfs1(i);
            }
        }
        ord.push_back(v);
    }

    void dfs2(size_t v) {
        vis[v] = true;
        linked_comp.push_back(v);
        for (size_t i : rev_graph[v]) {
            if (!vis[i]) {
                dfs2(i);
            }
        }
    }

    void shrink(vector<vector<size_t>>& cond_graph) {
        if (linked_comp.empty()) return;

        size_t min_term_idx = linked_comp.front();
        for (size_t i : linked_comp) {
            if (terminals[i] < terminals[min_term_idx]) {
                min_term_idx = i;
            }
        }
        is_rep[min_term_idx] = true;

        std::unordered_set<size_t> comps(linked_comp.begin(), linked_comp.end());
        std::unordered_set<size_t> edges;
        for (size_t i : linked_comp) {
            for (size_t j : orig_graph[i]) {
                if (!comps.contains(j)) {
                    edges.insert(j);
                }
            }
        }
        edges.erase(min_term_idx);

        cond_graph[min_term_idx].reserve(edges.size());
        for (size_t i : edges) {
            cond_graph[min_term_idx].push_back(i);
        }
    }

    void print_result() const {
        fout << result.size() << "\n";
        for (size_t i : result) {
            fout << i << " ";
        }
    }

    size_t n;
    vector<size_t> terminals;
    vector<vector<size_t>> orig_graph;
    vector<vector<size_t>> graph;
    vector<size_t> result;

    vector<bool> vis;
    vector<size_t> ord;
    vector<vector<size_t>> rev_graph;
    vector<size_t> linked_comp;

    vector<bool> is_rep;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    Solution sol;
    sol.process();

    return 0;
}