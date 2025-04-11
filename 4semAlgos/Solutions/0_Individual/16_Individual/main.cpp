#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>

int getMaxPlaceAB(
    std::vector<std::vector<unsigned short int>>& dp_curr,
    std::vector<std::vector<unsigned short int>>& dp_next,
    std::vector<std::vector<std::vector<bool>>>& choice,
    unsigned short int a,
    unsigned short int b,
    unsigned short int p,
    const std::vector<std::tuple<unsigned short int, unsigned short int, unsigned short int>>& rooms
);
std::vector<unsigned short int> getAPath(
    const std::vector<std::vector<std::vector<bool>>>& choice,
    unsigned short int a,
    unsigned short int b,
    unsigned short int p,
    const std::vector<std::tuple<unsigned short int, unsigned short int, unsigned short int>>& rooms
);

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    unsigned short int a, b, p;
    in >> a >> b >> p;

    std::vector<std::tuple<unsigned short int, unsigned short int, unsigned short int>> rooms(p);
    for (int i = 0; i < p; ++i)
        in >> std::get<0>(rooms[i]) >> std::get<1>(rooms[i]) >> std::get<2>(rooms[i]);

    std::vector<std::vector<unsigned short int>> dp_curr(a + 1, std::vector<unsigned short int>(b + 1, 0));
    std::vector<std::vector<unsigned short int>> dp_next(a + 1, std::vector<unsigned short int>(b + 1, 0));
    std::vector<std::vector<std::vector<bool>>> choice(p, std::vector<std::vector<bool>>(a + 1, std::vector<bool>(b + 1, false)));

    int result = getMaxPlaceAB(dp_curr, dp_next, choice, a, b, p, rooms);
    out << result << "\n";

    if (result == (a + b) && (a + b) != 0) {
        std::vector<unsigned short int> path = getAPath(choice, a, b, p, rooms);
        for (size_t i = 0; i < path.size(); ++i) {
            out << path[i] << (i + 1 < path.size() ? " " : "");
        }
    }

    in.close(); out.close();
    return 0;
}

int getMaxPlaceAB(
    std::vector<std::vector<unsigned short int>>& dp_curr,
    std::vector<std::vector<unsigned short int>>& dp_next,
    std::vector<std::vector<std::vector<bool>>>& choice,
    unsigned short int a,
    unsigned short int b,
    unsigned short int p,
    const std::vector<std::tuple<unsigned short int, unsigned short int, unsigned short int>>& rooms
)
{
    for (int i = p - 1; i >= 0; --i) {
        unsigned short int n = std::get<0>(rooms[i]);
        unsigned short int a_in = std::get<1>(rooms[i]);
        unsigned short int b_in = std::get<2>(rooms[i]);

        for (unsigned short int a_out = 0; a_out <= a; ++a_out) {
            for (unsigned short int b_out = 0; b_out <= b; ++b_out) {
                if (n == 0) {
                    dp_curr[a_out][b_out] = dp_next[a_out][b_out];
                    choice[i][a_out][b_out] = false;
                    continue;
                }

                if (a_in > 0) {
                    unsigned short int can_place = (a_out < n - a_in ? a_out : n - a_in);
                    dp_curr[a_out][b_out] = dp_next[a_out - can_place][b_out] + can_place;
                    choice[i][a_out][b_out] = true;
                }
                else if (b_in > 0) {
                    unsigned short int can_place = (b_out < n - b_in ? b_out : n - b_in);
                    dp_curr[a_out][b_out] = dp_next[a_out][b_out - can_place] + can_place;
                    choice[i][a_out][b_out] = false;
                }
                else {
                    unsigned short int place_a =
                        (a_out >= n)
                        ? dp_next[a_out - n][b_out] + n
                        : dp_next[0][b_out] + a_out;
                    unsigned short int place_b =
                        (b_out >= n)
                        ? dp_next[a_out][b_out - n] + n
                        : dp_next[a_out][0] + b_out;
                    if (place_a >= place_b) {
                        dp_curr[a_out][b_out] = place_a;
                        choice[i][a_out][b_out] = true;
                    }
                    else {
                        dp_curr[a_out][b_out] = place_b;
                        choice[i][a_out][b_out] = false;
                    }
                }
            }
        }
        dp_next = dp_curr;
    }
    return dp_curr[a][b];
}

std::vector<unsigned short int> getAPath(
    const std::vector<std::vector<std::vector<bool>>>& choice,
    unsigned short int a,
    unsigned short int b,
    unsigned short int p,
    const std::vector<std::tuple<unsigned short int, unsigned short int, unsigned short int>>& rooms
)
{
    std::vector<unsigned short int> path;
    path.reserve(p);
    unsigned short int a_out = a, b_out = b;
    for (int i = 0; i < p; ++i) {
        unsigned short int n = std::get<0>(rooms[i]);
        unsigned short int a_in = std::get<1>(rooms[i]);
        unsigned short int b_in = std::get<2>(rooms[i]);
        if (n == 0) continue;

        if (a_in > 0) {
            unsigned short int can_place = (a_out < n - a_in ? a_out : n - a_in);
            if (can_place > 0) {
                a_out -= can_place;
                path.push_back(i + 1);
            }
        }
        else if (b_in > 0) {
            unsigned short int can_place = (b_out < n - b_in ? b_out : n - b_in);
            b_out -= can_place;
        }
        else {
            if (choice[i][a_out][b_out] == true) {
                path.push_back(i + 1);
                if (a_out >= n)
                    a_out -= n;
                else
                    a_out = 0;
            }
            else if (choice[i][a_out][b_out] == false) {
                if (b_out >= n)
                    b_out -= n;
                else
                    b_out = 0;
            }
        }
    }
    std::sort(path.begin(), path.end());
    return path;
}
