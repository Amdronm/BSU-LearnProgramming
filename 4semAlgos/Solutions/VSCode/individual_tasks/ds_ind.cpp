#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

template <typename T>
static void print_vec(const std::vector<T>& v) {
    for (T i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    size_t n = 0, k = 0;
    std::cin >> n >> k;
    std::vector<size_t> stones_init(n);
    std::vector<size_t> canals(n);
    for (size_t i = 0; i < n; i++)
        std::cin >> stones_init[i];
    for (size_t i = 0; i < n; i++)
        std::cin >> canals[i];
    std::sort(stones_init.begin(), stones_init.end());
    std::sort(canals.begin(), canals.end());
    std::vector<size_t> stones;
    stones.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto it = std::lower_bound(stones_init.begin(), stones_init.end(), canals[i]);
        if (it == stones_init.end()) {
            continue;
        }
        stones.push_back(*it);
        stones_init.erase(it);
    }
    size_t a = stones.size() - 1;
    if (stones_init.size() > k) {
        std::cout << "-1";
        return 0;
    }
    for (size_t i : stones_init) {
        stones.push_back(i);
    }

    std::cout << "stones : " << std::endl;
    print_vec(stones);
    std::cout << "canals : " << std::endl;
    print_vec(canals);

    for (int i = a; i >= 0; i--) {
        auto it = std::lower_bound(canals.begin(), canals.end(), stones[i]);
        if (it == canals.end()) {
            std::swap(stones.back(), stones[i]);
            continue;
        }
        if (*it > stones[i]) {
            std::swap(stones[i], stones[it - canals.begin() - 1]);
        }
        else {
            std::swap(stones[it - canals.begin()], stones[i]);            
        }
    }

    std::cout << "end -> " << std::endl;
    std::cout << "stones : " << std::endl;
    print_vec(stones);
    std::cout << "canals : " << std::endl;
    print_vec(canals);

    std::vector<int> diffs(n);
    ll result = 0;
    for (size_t i = 0; i < n; i++) {
        diffs[i] = stones[i] - canals[i];
        result += stones[i];
    }

    std::cout << "sum of stones : " << result << std::endl;
    
    std::sort(diffs.begin(), diffs.end());

    std::cout << "diffs : " << std::endl;
    print_vec(diffs);

    for (size_t i = 0; diffs[i] < 0 && i < n; i++) {
        result -= diffs[i];
        k--;
    }
    for (int i = n - 1; k > 0 && i >= 0; i--) {
        result -= diffs[i];
        k--;
    }
    std::cout << "\nresult = " << result << std::endl;
    // std::cout << result;
    return 0;
}


/*
6 2
4 6 7 8 9 33
2 4 8 8 10 19
*/