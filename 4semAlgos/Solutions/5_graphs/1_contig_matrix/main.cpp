#include <fstream>
#include <vector>
#include <queue>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

static void print_mat(const std::vector<std::vector<size_t>>& mat) {
    for (int i = 0; i < mat.size(); i++) {
        //fout << mat[i].size() << " ";
        for (int j = 0; j < mat[i].size(); j++) {
            fout << mat[i][j] << " ";
        }
        fout << "\n";
    }
}

static void print_vec(const std::vector<size_t>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        fout << v[i] << " ";
    }
    fout << "\n";
}

static void bfs(const std::vector<std::vector<size_t>>& v, std::vector<size_t> &res, size_t &pos, size_t &label) {
    size_t n = res.size();

    std::queue<size_t> q;
    q.push(pos);
    res[pos - 1] = label;
    label++;
    while (!q.empty()) {
        size_t ver = q.front();
        pos = ver;
        q.pop();
        for (size_t i = 0; i < n; i++) {
            if (v[ver - 1][i] == 1 && res[i] == 0) {
                res[i] = label;
                label++;
                q.push(i + 1);
                //pos = i + 1;
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    size_t n = 0;
    fin >> n;
    std::vector<std::vector<size_t>> v(n, std::vector<size_t>(n, 0));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fin >> v[i][j];
        }
    }
    std::vector<size_t> res(n, 0);
    size_t pos = 1, label = 1;
    while (label != n + 1) {
        for (size_t i = 0; i < res.size(); i++) {
            if (res[i] == 0) {
                pos = i + 1;
                break;
            }
        }
        bfs(v, res, pos, label);
    }
    print_vec(res);
    return 0;
}