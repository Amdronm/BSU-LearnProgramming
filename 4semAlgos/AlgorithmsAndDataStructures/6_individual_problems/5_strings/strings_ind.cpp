#include <iostream>
#include <string>
#include <vector>
#include <queue>

using std::vector, std::string, std::size_t, std::cout, std::cin, std::queue;

using std::endl;

static void print(const vector<size_t>& v) {
    for (auto i : v) {
        cout << i << endl;
    }
    cout << endl;
}

vector<size_t> sort_lex(const string& s) {
    size_t n = s.size();
    vector<size_t> v(n);
    for (size_t i = 0; i < n; i++) {
        v[i] = n - 1 - i;
    }

    queue<size_t> queue;
    for (size_t i : v) {
        queue.push(i);
    }

    vector<std::queue<size_t>> q_vec(26);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            size_t ind = queue.front();
            queue.pop();
            if (ind + i >= n) {
                queue.push(ind);
            }
            else {
                q_vec[s[ind + i] - 97].push(ind);
            }
        }
        for (auto& j : q_vec) {
            while (!j.empty()) {
                queue.push(j.front());
                j.pop();
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        v[i] = queue.front();
        queue.pop();
    }
    return v;
}

int main() {
    size_t n = 0;
    string s;
    cin >> n;
    cin >> s;
    n = s.size();

    vector<size_t> v = sort_lex(s);
    vector<size_t> vec_same(n, 0);
    for (size_t i = 1; i < n; i++) {
        size_t j1 = v[i - 1];
        size_t j2 = v[i];
        if (j1 > j2) std::swap(j1, j2); // j1 < j2
        size_t j = 0;
        for (; j2 < n; ++j, ++j1, ++j2) {
            if (s[j1] != s[j2]) {
                vec_same[i] = j;
                break;
            }
        }
        vec_same[i] = j;
    }

    unsigned long long result = 0;
    size_t len_same = 0;
    size_t met = 0;
    for (size_t i = 1; i < n; i++) {
        len_same = 0;
        met = 0;
        for (size_t j = 0; j < n; j++) {
            if (n - v[j] < i) continue;
            if (vec_same[j] >= i) {
                result += met;
                len_same++;
            }
            else {
                met += len_same;
                result += met;
                len_same = 1;
            }
        }
    }
    cout << result << endl;
    return 0;
}