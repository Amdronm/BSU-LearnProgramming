#include <vector>
#include <iostream>

using namespace std;

void bin_search_prnt(const std::vector<int>& vec, int key) {
  if (vec.empty()) {
        cout << "0 0 0\n";
        return;
    }
    int b = 0;
    int l = 0;
    int r = vec.size() - 1;
    int m = 0;
    int nResL = 0;
    while (l < r) {
        m = (r + l) / 2;
        if (key <= vec[m]) {
            r = m;
        }
        else {
            if (l + 1 == r && m == l) {
                l++;
                break;
            }
            else {
                l = m;
            }
        }
    }
    r = vec.size() - 1;
    if (vec[l] < key)
        l++;
    nResL = l;
    while (l < r) {
        m = (r + l) / 2 + (r + l) % 2;
        if (key >= vec[m]) {
            l = m;
        }
        else {
            if (l + 1 == r && m == r) {
                r--;
                break;
            }
            else {
                r = m;
            }
        }
    }
    if (vec[r] <= key)
        r++;
    if (nResL == r) {
        cout << "0 " << r << " " << r << "\n";
    }
    else {
        cout << "1 " << nResL << " " << r << "\n";
    }
}

int main() {
    int n = 0;
        int a = 0;
    cin >> n;
    std::vector<int> vec;
    for (int i = 0; i < n; i++) {
        cin >> a;
        vec.push_back(a);
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a;
        bin_search_prnt(vec, a);
    }
    return 0;
}