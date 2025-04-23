#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector, std::cout, std::cin, std::sort;
using ll = long long;

template <typename T>
static void print_vec(const vector<T>& v) {
    for (T i : v) {
        cout << i << " ";
    }
    cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n = 0, k = 0;
    cin >> n >> k;
    vector<ll> stones_init(n);
    vector<ll> canals(n);
    for (ll i = 0; i < n; i++)
        cin >> stones_init[i];
    for (ll i = 0; i < n; i++)
        cin >> canals[i];

    sort(canals.begin(), canals.end());
    std::priority_queue<ll, vector<ll>, std::greater<ll>> heap_stones(stones_init.begin(), stones_init.end());
    std::priority_queue<ll> q;
    vector<ll> stones(n, 0);
    ll j = 0;

    while (!heap_stones.empty()) {
        ll stone = heap_stones.top();
        heap_stones.pop();
        auto it = std::upper_bound(canals.begin(), canals.end(), stone);
        if (it == canals.begin()) {
            continue;
        }
        ll i = std::distance(canals.begin(), it) - 1;
        if (stones[i] == 0) {
            stones[i] = stone;
            while (j < i) {
                if (stones[j] == 0) {
                    q.push(j);
                }
                j++;
            }
            j = i + 1;
        }
        else {
            if (!q.empty()) {
                ll ii = q.top();
                q.pop();
                stones[ii] = stone;
            }
        }
    }

    long long result = 0;
    vector<ll> diffs;
    diffs.reserve(n);
    ll m = 0;

    for (ll i = 0; i < n; i++) {
        if (stones[i] > 0) {
            result += stones[i];
            diffs.push_back(stones[i] - canals[i]);
        }
        else {
            result += canals[i];
            m++;
        }
    }

    if (m > k) {
        cout << "-1\n";
        return 0;
    }
    k -= m;

    std::priority_queue<ll> q_diffs(diffs.begin(), diffs.end());
    while (!q_diffs.empty() && k > 0) {
        ll el = q_diffs.top();
        q_diffs.pop();
        if (el > 0) {
            result -= el;
            k--;
        }
        else {
            break;
        }
    }

    cout << result << "\n";
    return 0;
}