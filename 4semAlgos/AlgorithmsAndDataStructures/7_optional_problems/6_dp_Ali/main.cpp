#include <algorithm>
#include <cstdint>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

static const int kImp = INT32_MAX / 3;

class Solve {
public:
    Solve(const vector<pair<int, int>>& vec) {
        n_ = vec.size();
        dist_.resize(n_);
        time_.resize(n_);
        for (int i = 0; i < n_; i++) {
            dist_[i] = vec[i].first;
            time_[i] = vec[i].second;
        }
        mat_.resize(n_, vector<pair<int, int>>(n_, {0, 0}));
    }

    int GetResult() {
        FillMat();
        auto elem = mat_[0].back();
        return std::min(elem.first, elem.second);
    }

private:
    int n_;
    vector<int> dist_;
    vector<int> time_;
    vector<vector<pair<int, int>>> mat_;

    void FillMat() {
        for (int i = n_ - 2; i >= 0; i--) {
            for (int j = i + 1; j < n_; j++) {
                int left_min = FindMinLeft(i, j);
                mat_[i][j].first = (left_min <= time_[i]) ? left_min : kImp;
                int right_min = FindMinRight(i, j);
                mat_[i][j].second = (right_min <= time_[j]) ? right_min : kImp;
            }
        }
    }

    int FindMinLeft(int i, int j) const {
        auto elem = mat_[i + 1][j];
        if (elem.first == kImp && elem.second == kImp) {
            return kImp;
        }
        int time1 = elem.first + (dist_[i + 1] - dist_[i]);
        int time2 = elem.second + (dist_[j] - dist_[i]);
        return min(time1, time2);
    }

    int FindMinRight(int i, int j) const {
        auto elem = mat_[i][j - 1];
        if (elem.first == kImp && elem.second == kImp) {
            return kImp;
        }
        int time1 = elem.first + (dist_[j] - dist_[i]);
        int time2 = elem.second + (dist_[j] - dist_[j - 1]);
        return min(time1, time2);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    ifstream fin("input.txt");
    int n = 0;
    fin >> n;
    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; i++) {
        int dist;
        int time;
        fin >> dist >> time;
        vec[i] = {dist, time};
    }
    Solve sol(vec);
    int res = sol.GetResult();
    ofstream fout("output.txt");
    if (res < kImp) {
        fout << res;
    } else {
        fout << "No solution";
    }
    return 0;
}
