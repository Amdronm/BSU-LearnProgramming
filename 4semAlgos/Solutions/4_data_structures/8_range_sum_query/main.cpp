#include <iostream>
#include <vector>
#include <string>

#include "segment_tree.h"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    size_t n = 0;
    std::cin >> n;
    std::vector<ll> a(n);
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    segment_tree st(a);
    size_t q = 0;
    std::cin >> q;
    std::string query;
    int l = 0, r = 0;
    for (size_t i = 0; i < q; i++) {
        std::cin >> query >> l >> r;
        if (query == "Add") {
            st.update(l, r);
        }
        else {
            std::cout << st.get(l, r) << "\n";
        }
    }
    return 0;
}