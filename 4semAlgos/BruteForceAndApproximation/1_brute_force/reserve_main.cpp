/*
putting Queens on board
to hit every tile k times
*/

#include <algorithm>
#include <fstream>
// #include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const int kBlack = 128;
const int kQueen = 256;

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

    // void PrintBoard() const {
    //     vector<vector<int>> vec = board_;
    //     reverse(vec.begin(), vec.end());
    //     for (const auto& row : vec) {
    //         for (int tile : row) {
    //             if (tile == kBlack) {
    //                 cout << setw(4) << "#";
    //             } else {
    //                 if (tile >= kQueen) {
    //                     cout << setw(3) << tile % kQueen << "Q";
    //                 } else {
    //                     cout << setw(4) << tile;
    //                 }
    //             }
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

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
                if (tile == kBlack) {
                    continue;
                }
                if (tile % kQueen < k_) {
                    return false;
                }
            }
        }
        return true;
    }

    // pair<int, int> FindNextPosOptimal(int row, int col) const {
    //     for (int j = col + 1; j < w_; j++) {
    //         if (board_[row][j] < kBlack && board_[row][j] % kQueen < k_) {
    //             return {row, j};
    //         }
    //     }
    //     for (int i = row + 1; i < h_; i++) {
    //         for (int j = 0; j < w_; j++) {
    //             if (board_[i][j] < kBlack && board_[i][j] % kQueen < k_) {
    //                 return {i, j};
    //             }
    //         }
    //     }
    //     return {h_ - 1, w_ - 1};
    // }

    // void SetMin(int row, int col, int queens) {
    //     if (queens > min_) {
    //         return;
    //     }
    //     if (IsDone()) {
    //         min_ = min(queens, min_);
    //         return;
    //     }
    //     if (row == h_ - 1 && col == w_ - 1) {
    //         PutQueen(row, col, 1);
    //         if (IsDone() && queens + 1 <= min_) {
    //             min_ = min(queens + 1, min_);
    //         }
    //         PutQueen(row, col, -1);
    //         return;
    //     }
    //     auto [next_row, next_col] = FindNextPosOptimal(row, col);
    //     SetMin(next_row, next_col, queens);
    //     PutQueen(row, col, 1);
    //     auto [rr, cc] = FindNextPosOptimal(row, col);
    //     SetMin(rr, cc, queens + 1);
    //     PutQueen(row, col, -1);
    // }

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
        if (k_ > max(h_, w_) + 2 * min(h_, w_) - 2) {
            fout << 0 << "\n";
            return;
        }
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

/*
2
4 4
2
1 2
2 1

4
0 0 0 3 3 0 3 3
0 0 0 3 2 2 3 0
0 3 1 1 3 0 3 3
0 0 1 1 2 2 3 3

1
3 3
4
0 0
2 0
2 2
1 2

2
1 1
0 1

1
3 3
3
0 2
1 1
2 1

5
0 2 2 1
0 1 2 2
0 1 2 1
0 0 2 2
0 0 2 1

1
3 3
4
0 2
1 1
2 1
0 1

6
0 2 2 2
0 2 2 1
0 1 2 2
0 1 2 1
0 0 2 2
0 0 2 1

1
2 2
1
1 1

2
2 3
1
1 1
*/