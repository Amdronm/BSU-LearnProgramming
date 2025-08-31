#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

class DisjointSetUnion {
public:
    DisjointSetUnion() = default;
    DisjointSetUnion(int size) {
        data_.resize(size + 1);
        for (int i = 0; i < data_.size(); i++) {
            data_[i] = i;
        }
    }
    ~DisjointSetUnion() = default;

    bool Equivalent(int a_vert, int b_vert) {
        int a_ind = FindRoot(a_vert);
        int b_ind = FindRoot(b_vert);
        return a_ind == b_ind;
    }
    void Unite(int set1, int set2) {
        if (Equivalent(set1, set2)) {
            return;
        }
        bool ran = static_cast<bool>(rand() % 2);
        int a_ind = FindRoot(set1);
        int b_ind = FindRoot(set2);
        if (ran) {
            data_[a_ind] = b_ind;
        } else {
            data_[b_ind] = a_ind;
        }
    }

private:
    int FindRoot(int vert) {
        int a_ind = vert;
        vector<int> vec;
        while (data_[a_ind] != a_ind) {
            vec.push_back(a_ind);
            a_ind = data_[a_ind];
        }
        for (int el : vec) {
            data_[el] = a_ind;
        }
        return a_ind;
    }

    vector<int> data_;
};

struct Edge {
    int u, v, w, id;
};

bool CompareEdges(const Edge& ed1, const Edge& ed2) { return ed1.w > ed2.w; }

bool CompareId(const Edge& ed1, const Edge& ed2) { return ed1.id < ed2.id; }

int main() {
    ios_base::sync_with_stdio(false);
    fin.tie(NULL);
    srand(time(nullptr));

    int n;
    int m;
    fin >> n >> m;

    vector<Edge> edges;
    edges.reserve(m + 1);
    for (int i = 1; i <= m; i++) {
        int ver1;
        int ver2;
        int weight;
        fin >> ver1 >> ver2 >> weight;
        edges.push_back({ver1, ver2, weight, i});
    }
    sort(edges.begin(), edges.end(), CompareEdges);
    DisjointSetUnion dsu(n);

    vector<bool> terms(n + 1, false);
    int terms_count;
    fin >> terms_count;
    for (int i = 0; i < terms_count; i++) {
        int ter;
        fin >> ter;
        terms[ter] = true;
    }

    vector<Edge> cut_edges;
    cut_edges.reserve(m);

    for (const auto& edge : edges) {
        int u_vert = edge.u;
        int v_vert = edge.v;
        if (dsu.Equivalent(u_vert, v_vert)) {
            continue;
        }
        bool u_term = false;
        bool v_term = false;
        for (int i = 1; i < terms.size(); i++) {
            if (terms[i]) {
                u_term |= dsu.Equivalent(i, u_vert);
                v_term |= dsu.Equivalent(i, v_vert);
            }
        }
        if (!(u_term && v_term)) {
            dsu.Unite(u_vert, v_vert);
        } else {
            cut_edges.push_back(edge);
        }
    }

    sort(cut_edges.begin(), cut_edges.end(), CompareId);
    long long cut_weight = 0;
    for (const auto& edge : cut_edges) {
        cut_weight += edge.w;
    }
    fout << cut_weight << "\n";
    fout << cut_edges.size() << "\n";
    for (const auto& edge : cut_edges) {
        fout << edge.id << "\n";
    }

    return 0;
}