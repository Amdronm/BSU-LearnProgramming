#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const long long kInfCapacity = numeric_limits<long long>::max() / 2;

struct FlowEdge {
    int to;
    long long capacity;
    int rev;
};

struct OrigEdge {
    int u, vert;
    long long weight;
    int id;
};

struct IsolatingCutResult {
    long long weight;
    vector<pair<int, int>> edges_uv_pairs;
    int isolated_terminal;

    bool operator<(const IsolatingCutResult& other) const {
        if (weight != other.weight) {
            return weight < other.weight;
        }
        return isolated_terminal < other.isolated_terminal;
    }
};

class MultiwayCutter {
private:
    // Поля для алгоритма Диница (будут инициализироваться для каждого вызова
    // max-flow)
    vector<vector<FlowEdge>> adj_max_flow_;
    vector<int> level_graph_;
    vector<int> iter_dfs_;         // Итераторы для DFS в Динице
    int num_nodes_in_flow_graph_;  // Количество вершин в графе для потока
                                   // (включая sink' и term')

    // Данные исходного графа
    int num_original_vertices_;
    vector<OrigEdge> all_original_graph_edges_;

    void AddDinicEdge(int from, int to, long long cap) {
        adj_max_flow_[from].push_back({to, cap, (int)adj_max_flow_[to].size()});
        // Для неориентированных ребер в задаче разреза, обратное ребро в
        // остаточной сети изначально имеет 0 пропускную способность. При
        // построении графа для потока мы добавляем два ориентированных ребра
        // (u,vert) и (vert,u) с одинаковой пропускной способностью.
        adj_max_flow_[to].push_back(
            {from, 0, (int)adj_max_flow_[from].size() - 1});
    }

    bool BfsDinic(int sink, int term) {
        level_graph_.assign(num_nodes_in_flow_graph_, -1);
        queue<int> q;
        level_graph_[sink] = 0;
        q.push(sink);
        while (!q.empty()) {
            int vert = q.front();
            q.pop();
            for (const auto& edge : adj_max_flow_[vert]) {
                if (edge.capacity > 0 && level_graph_[edge.to] < 0) {
                    level_graph_[edge.to] = level_graph_[vert] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level_graph_[term] != -1;
    }

    long long DfsDinic(int vert, int term, long long flow) {
        if (vert == term) {
            return flow;
        }
        for (int& i = iter_dfs_[vert]; i < adj_max_flow_[vert].size(); ++i) {
            FlowEdge& e = adj_max_flow_[vert][i];
            if (e.capacity > 0 && level_graph_[vert] < level_graph_[e.to]) {
                long long d = DfsDinic(e.to, term, min(flow, e.capacity));
                if (d > 0) {
                    e.capacity -= d;
                    adj_max_flow_[e.to][e.rev].capacity += d;
                    return d;
                }
            }
        }
        return 0;
    }

    long long CalculateMaxFlow(int sink, int term) {
        long long flow = 0;
        while (BfsDinic(sink, term)) {
            iter_dfs_.assign(num_nodes_in_flow_graph_, 0);
            long long ff;
            while ((ff = DfsDinic(sink, term, kInfCapacity)) > 0) {
                flow += ff;
            }
        }
        return flow;
    }

    IsolatingCutResult FindMinCutForTerminalIsolation(
        int terminal_to_isolate, const set<int>& all_terminals) {
        if (all_terminals.size() <= 1 &&
            all_terminals.contains(terminal_to_isolate)) {
            // Не от кого изолировать, или это единственный терминал
            return {0, {}, terminal_to_isolate};
        }

        num_nodes_in_flow_graph_ = num_original_vertices_ + 2;
        int s_prime = num_original_vertices_;      // Вспомогательный источник
        int t_prime = num_original_vertices_ + 1;  // Вспомогательный сток

        adj_max_flow_.assign(num_nodes_in_flow_graph_, vector<FlowEdge>());

        // Добавляем ребра исходного графа
        for (const auto& orig_edge : all_original_graph_edges_) {
            // Для неориентированного ребра (u,vert) с весом w, добавляем
            // (u,vert,w) и (vert,u,w)
            AddDinicEdge(orig_edge.u, orig_edge.vert, orig_edge.weight);
            AddDinicEdge(orig_edge.vert, orig_edge.u, orig_edge.weight);
        }

        // Подключаем terminal_to_isolate к s_prime
        AddDinicEdge(s_prime, terminal_to_isolate, kInfCapacity);

        // Подключаем остальные терминалы к t_prime
        for (int other_term : all_terminals) {
            if (other_term != terminal_to_isolate) {
                AddDinicEdge(other_term, t_prime, kInfCapacity);
            }
        }

        long long cut_weight = CalculateMaxFlow(s_prime, t_prime);

        vector<pair<int, int>> cut_edges_list;
        // Восстановление ребер разреза:
        // После нахождения max_flow, делаем BFS/DFS из s_prime в остаточной
        // сети
        vector<bool> visited_in_residual(num_nodes_in_flow_graph_, false);
        queue<int> q_residual;

        q_residual.push(s_prime);
        visited_in_residual[s_prime] = true;
        while (!q_residual.empty()) {
            int u_res = q_residual.front();
            q_residual.pop();
            // Обход по остаточной сети (ребра с capacity > 0)
            for (const auto& flow_edge : adj_max_flow_[u_res]) {
                if (flow_edge.capacity > 0 &&
                    !visited_in_residual[flow_edge.to]) {
                    visited_in_residual[flow_edge.to] = true;
                    q_residual.push(flow_edge.to);
                }
            }
        }

        // Собираем ребра разреза из исходного графа
        for (const auto& orig_edge : all_original_graph_edges_) {
            // Вершина считается в S-части разреза, если она достижима от
            // s_prime в остаточной сети
            bool u_is_s_part = visited_in_residual[orig_edge.u];
            bool v_is_s_part = visited_in_residual[orig_edge.vert];

            if (u_is_s_part != v_is_s_part) {  // Ребро пересекает разрез
                cut_edges_list.push_back({orig_edge.u, orig_edge.vert});
            }
        }

        return {cut_weight, cut_edges_list, terminal_to_isolate};
    }

public:
    MultiwayCutter(int n_verts, const vector<OrigEdge>& edges)
        : num_original_vertices_(n_verts), all_original_graph_edges_(edges) {}

    pair<long long, vector<int>> SolveIsolatingCutHeuristic(
        const set<int>& terminals) {
        int k_terminals = terminals.size();
        if (k_terminals <= 1) {
            return {0, {}};
        }

        vector<IsolatingCutResult> all_isolating_cuts_info;
        for (int term_to_isolate : terminals) {
            all_isolating_cuts_info.push_back(
                FindMinCutForTerminalIsolation(term_to_isolate, terminals));
        }

        sort(all_isolating_cuts_info.begin(), all_isolating_cuts_info.end());

        set<pair<int, int>> final_multiway_cut_edges_normalized;
        int cuts_to_take = max(0, k_terminals - 1);

        for (int i = 0; i < cuts_to_take && i < all_isolating_cuts_info.size();
             ++i) {
            for (const auto& edge_pair :
                 all_isolating_cuts_info[i].edges_uv_pairs) {
                final_multiway_cut_edges_normalized.insert(
                    {min(edge_pair.first, edge_pair.second),
                     max(edge_pair.first, edge_pair.second)});
            }
        }

        long long total_weight_of_final_cut = 0;
        vector<int> result_edge_ids;

        for (const auto& p_cut : final_multiway_cut_edges_normalized) {
            // Находим вес этого ребра и его ID в исходном списке ребер
            // (Предполагаем, что нет параллельных ребер с РАЗНЫМИ весами между
            // одной парой вершин, или что выбор любого из них корректен. Если
            // могут быть параллельные ребра, и нужно выбрать конкретное
            // (например, самое легкое из них, если оно было частью min-cut), то
            // find_min_cut_for_terminal_isolation должна была бы возвращать
            // OrigEdge объекты. Здесь мы просто берем первое
            // попавшееся ребро из all_original_graph_edges, которое
            // соответствует паре вершин p_cut)
            bool found_edge = false;
            for (const auto& orig_edge : all_original_graph_edges_) {
                if (min(orig_edge.u, orig_edge.vert) == p_cut.first &&
                    max(orig_edge.u, orig_edge.vert) == p_cut.second) {
                    total_weight_of_final_cut += orig_edge.weight;
                    result_edge_ids.push_back(orig_edge.id);
                    found_edge = true;
                    break;  // Взяли одно ребро, соответствующее паре
                }
            }
            // if (!found_edge) { /* Обработка ошибки: ребро из разреза не
            // найдено. */ }
        }

        sort(result_edge_ids.begin(), result_edge_ids.end());
        // Уникальность ID уже должна быть обеспечена set'ом пар вершин, если
        // между u,vert только одно ребро. Если могут быть параллельные ребра, и
        // мы хотим уникальные ID, то:
        // result_edge_ids.erase(unique(result_edge_ids.begin(),
        // result_edge_ids.end()), result_edge_ids.end()); Но это не совсем
        // правильно, если в разрез должны войти ОБА параллельных ребра. Однако,
        // set<pair<int,int>> уже гарантирует, что пара вершин {u,vert} вносится
        // один раз.

        return {total_weight_of_final_cut, result_edge_ids};
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n_verts;
    int m_edges;
    fin >> n_verts >> m_edges;

    vector<OrigEdge> all_edges_input;
    for (int i = 0; i < m_edges; ++i) {
        int u;
        int vert;
        long long w;
        fin >> u >> vert >> w;
        --u;
        --vert;
        all_edges_input.push_back({u, vert, w, i + 1});
    }

    int k_terminals;
    fin >> k_terminals;
    set<int> terminals_s_input;
    for (int i = 0; i < k_terminals; ++i) {
        int term_node;
        fin >> term_node;
        terminals_s_input.insert(term_node - 1);
    }

    MultiwayCutter cutter(n_verts, all_edges_input);
    auto result = cutter.SolveIsolatingCutHeuristic(terminals_s_input);

    fout << result.first << endl;
    fout << result.second.size() << endl;
    for (int id : result.second) {
        fout << id << "\n";
    }

    return 0;
}