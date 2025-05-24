#include <fstream>
#include <vector>
#include <iostream>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

static void print_vec(const std::vector<size_t>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        fout << v[i] << " ";
    }
    fout << "\n";
}

std::vector<std::vector<size_t>> v;
std::vector<size_t> vis;

static void dfs(size_t vertex, size_t& label) {
    vis[vertex] = label;
    label++;
    for (size_t j = 0; j < v[vertex].size(); j++) {
        if (v[vertex][j] && !vis[j]) {
            dfs(j, label);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    size_t n = 0;
    fin >> n;
    v.resize(n + 1, std::vector<size_t>(n + 1, 0));
    for (size_t i = 1; i < n + 1; i++) {
        for (size_t j = 1; j < n + 1; j++) {
            fin >> v[i][j];
        }
    }
    vis.resize(n + 1, 0);
    size_t label = 1;
    while (label < n + 1) {
        for (size_t i = 1; i < n + 1; i++) {
            if (!vis[i]) {
                dfs(i, label);
                break;
            }
        }
    }
    print_vec(vis);
    return 0;
}