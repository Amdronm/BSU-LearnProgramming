#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using ll = long long;

/*
расставить камни что можно, потом
сопоставить большие камни наибольшим каналам
уменьшить остатки
*/

int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector<int> stones(n);
    for (int i = 0; i < n; i++)
        std::cin >> stones[i];
    std::sort(stones.begin(), stones.end());
    std::vector<int> canals(n);
    for (int i = 0; i < n; i++)
        std::cin >> canals[i];
    std::priority_queue<int, std::vector<int>, std::greater<int>> canheap(canals.begin(), canals.end());
    ll result = 0;
    std::vector<int> diffs;
    while (!canheap.empty() || k == 0) {
        int wcan = canheap.top();
        auto it = std::lower_bound(stones.begin(), stones.end(), wcan);
        if (it == stones.end()) {
            if (k < stones.size()) {
                std::cout << "-1";
                return 0;
            } else {
                while (!canheap.empty()) {
                    result += canheap.top();
                    k--;
                    canheap.pop();
                }
                break;
            }
        }
        result += *it;
        diffs.push_back(*it - wcan);
        stones.erase(it);
        canheap.pop();
    }
    std::sort(diffs.begin(), diffs.end());
    for (int i = 0; i < k; i++) {
        result -= diffs.back();
        diffs.pop_back();
    }
    std::cout << result;
    return 0;
}
/*
6 2
12 1 7 5 2 10
1 4 11 4 7 5

1 2 5 7 10 12
1 4 4 5 7 11

1 10 2 5 7 12
1 4 4 5 7 11
*/