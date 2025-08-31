/*
putting Queens on board
to hit every tile k times
*/

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int kBlack = 1024;
const int kQueen = 2048;

ofstream fout("output.txt");

class Solve {
public:
    Solve(int kk, int width, int height, const vector<vector<int>>& vec,
          int obsts)
        : k_(kk),
          w_(width),
          h_(height),
          board_(vec),
          copy_board_(board_),
          obstacles_(obsts) {}

    void FindBest() {
        min_ = 0;
        while (!IsDone()) {
            auto [row, col] = FindMin();
            if (row == -1 || col == -1) {
                min_ = 0;
                board_ = copy_board_;
                return;
            }
            PutQueen(row, col, 1);
            min_++;
        }
        board_ = copy_board_;
        int min_optimal = 0;
        while (min_optimal < min_ && !IsDone()) {
            auto [row, col] = FindOptimal();
            if (row == -1 || col == -1) {
                board_ = copy_board_;
                return;
            }
            PutQueen(row, col, 1);
            min_optimal++;
        }
        min_ = min(min_, min_optimal);
        board_ = copy_board_;

        int queens_s3 = 0;
        while (queens_s3 < min_ && !IsDone()) {
            auto [row, col] = FindMaxCoverMove();
            if (row == -1 || col == -1) {
                queens_s3 = w_ * h_ + 1;
                break;
            }
            PutQueen(row, col, 1);
            queens_s3++;
        }
        min_ = min(min_, queens_s3);
        board_ = copy_board_;
    }

    pair<int, int> FindOptimal() {
        pair<int, int> res = {-1, -1};
        int max_tiles = 0;
        for (int i = 0; i < h_; i++) {
            for (int j = 0; j < w_; j++) {
                if (board_[i][j] >= kBlack) {
                    continue;
                }
                PutQueen(i, j, 1);
                int tiles = SumOfTiles(i, j);
                PutQueen(i, j, -1);
                if (max_tiles < tiles) {
                    max_tiles = tiles;
                    res = {i, j};
                }
            }
        }
        return res;
    }

    int SumOfTiles(int row, int col) const {
        int res = 0;
        for (int i = 0; i < h_; i++) {
            for (int j = 0; j < w_; j++) {
                if (board_[i][j] <= k_ &&
                    (i == row || j == col || (i + j) == row + col ||
                     (i - j) == row - col)) {
                    res += board_[i][j];
                }
            }
        }
        return res;
    }

    pair<int, int> FindMin() const {
        pair<int, int> res = {-1, -1};
        for (int i = 0; i < h_; i++) {
            for (int j = 0; j < w_; j++) {
                if (board_[i][j] < kBlack) {
                    res = {i, j};
                }
            }
        }
        if (res.first == -1 || res.second == -1) {
            return res;
        }
        for (int i = 0; i < h_; i++) {
            for (int j = 0; j < w_; j++) {
                if (board_[i][j] == kBlack || board_[i][j] >= kQueen) {
                    continue;
                }
                if (board_[i][j] < board_[res.first][res.second]) {
                    res = {i, j};
                }
            }
        }
        return res;
    }

    int CountUnsatHits(int r_q, int c_q) const {
        vector<vector<bool>> counted_here(h_, vector<bool>(w_, false));
        int hits = 0;

        auto check_cell = [&](int row, int col) -> bool {
            if (board_[row][col] == kBlack) {
                return false;
            }

            if (!counted_here[row][col]) {
                if (board_[row][col] % kQueen < k_) {
                    hits++;
                }
                counted_here[row][col] = true;
            }
            return true;
        };

        check_cell(r_q, c_q);

        for (int j = c_q + 1; j < w_; ++j) {
            if (!check_cell(r_q, j)) {
                break;
            }
        }
        for (int j = c_q - 1; j >= 0; --j) {
            if (!check_cell(r_q, j)) {
                break;
            }
        }
        for (int i = r_q + 1; i < h_; ++i) {
            if (!check_cell(i, c_q)) {
                break;
            }
        }
        for (int i = r_q - 1; i >= 0; --i) {
            if (!check_cell(i, c_q)) {
                break;
            }
        }
        for (int i = r_q - 1, j = c_q - 1; i >= 0 && j >= 0; --i, --j) {
            if (!check_cell(i, j)) {
                break;
            }
        }
        for (int i = r_q + 1, j = c_q + 1; i < h_ && j < w_; ++i, ++j) {
            if (!check_cell(i, j)) {
                break;
            }
        }
        for (int i = r_q - 1, j = c_q + 1; i >= 0 && j < w_; --i, ++j) {
            if (!check_cell(i, j)) {
                break;
            }
        }
        for (int i = r_q + 1, j = c_q - 1; i < h_ && j >= 0; ++i, --j) {
            if (!check_cell(i, j)) {
                break;
            }
        }

        return hits;
    }

    pair<int, int> FindMaxCoverMove() {
        pair<int, int> best_pos = {-1, -1};
        int max_score = -1;

        for (int row = 0; row < h_; ++row) {
            for (int col = 0; col < w_; ++col) {
                if (board_[row][col] == kBlack || board_[row][col] >= kQueen) {
                    continue;
                }

                int score = CountUnsatHits(row, col);

                if (score > max_score) {
                    max_score = score;
                    best_pos = {row, col};
                }
            }
        }
        return best_pos;
    }

    void PutQueen(int row, int col, int sign) {
        if (board_[row][col] == kBlack) {
            return;
        }
        if (sign == 1) {
            if (board_[row][col] >= kQueen) {
                return;
            }
            board_[row][col] += kQueen + 1;
        } else {
            if (board_[row][col] < kQueen) {
                return;
            }
            board_[row][col] -= (kQueen + 1);
        }
        for (int j = col + 1; j < w_; j++) {
            if (board_[row][j] == kBlack) {
                break;
            }
            board_[row][j] += sign;
        }
        for (int j = col - 1; j >= 0; j--) {
            if (board_[row][j] == kBlack) {
                break;
            }
            board_[row][j] += sign;
        }
        for (int i = row + 1; i < h_; i++) {
            if (board_[i][col] == kBlack) {
                break;
            }
            board_[i][col] += sign;
        }
        for (int i = row - 1; i >= 0; i--) {
            if (board_[i][col] == kBlack) {
                break;
            }
            board_[i][col] += sign;
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board_[i][j] == kBlack) {
                break;
            }
            board_[i][j] += sign;
        }
        for (int i = row + 1, j = col + 1; i < h_ && j < w_; i++, j++) {
            if (board_[i][j] == kBlack) {
                break;
            }
            board_[i][j] += sign;
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < w_; i--, j++) {
            if (board_[i][j] == kBlack) {
                break;
            }
            board_[i][j] += sign;
        }
        for (int i = row + 1, j = col - 1; i < h_ && j >= 0; i++, j--) {
            if (board_[i][j] == kBlack) {
                break;
            }
            board_[i][j] += sign;
        }
    }

    bool IsDone() const {
        for (const auto& row : board_) {
            for (int tile : row) {
                if (tile % kQueen < k_) {
                    return false;
                }
            }
        }
        return true;
    }

    pair<int, int> FindNextPos(int row, int col) const {
        int next_row = row;
        int next_col = col + 1;
        if (next_col == w_) {
            next_row++;
            next_col = 0;
        }
        return {next_row, next_col};
    }

    void Process(int row, int col, int queens) {
        if (queens > min_) {
            return;
        }
        if (row == h_) {
            if (IsDone()) {
                if (queens < min_) {
                    min_ = queens;
                    results_.clear();
                    AddAnswer();
                } else if (queens == min_) {
                    AddAnswer();
                }
            }
            return;
        }
        auto [next_row, next_col] = FindNextPos(row, col);
        Process(next_row, next_col, queens);
        if (board_[row][col] != kBlack) {
            PutQueen(row, col, 1);
            Process(next_row, next_col, queens + 1);
            PutQueen(row, col, -1);
        }
    }

    void AddAnswer() {
        vector<int> vec;
        vec.reserve(min_ * 2);
        for (int i = 0; i < h_; i++) {
            for (int j = 0; j < w_; j++) {
                if (board_[i][j] >= kQueen) {
                    vec.push_back(i);
                    vec.push_back(j);
                }
            }
        }
        results_.push_back(vec);
    }

    void MakeItAllWork() {
        FindBest();
        if (min_ == 0) {
            fout << 0 << "\n";
            return;
        }
        Process(0, 0, 0);
        PrintAnswer();
    }

    void PrintAnswer() const {
        fout << results_.size() << "\n";
        for (const auto& vec : results_) {
            for (int i = 0; i < vec.size(); i++) {
                fout << vec[i] << ((i == vec.size() - 1) ? "" : " ");
            }
            fout << "\n";
        }
    }

private:
    int k_;
    int w_;
    int h_;
    int min_ = 0;
    vector<vector<int>> board_;
    vector<vector<int>> copy_board_;

    vector<vector<int>> results_;

    int obstacles_ = 0;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.txt");
    int kk;
    int width;
    int height;
    fin >> kk >> height >> width;
    int tiles;
    fin >> tiles;
    vector<vector<int>> black_tiles(height, vector<int>(width, 0));
    int row;
    int col;
    for (int i = 0; i < tiles; i++) {
        fin >> row >> col;
        black_tiles[row][col] = kBlack;
    }
    Solve sol(kk, width, height, black_tiles, tiles);
    sol.MakeItAllWork();
    return 0;
}
