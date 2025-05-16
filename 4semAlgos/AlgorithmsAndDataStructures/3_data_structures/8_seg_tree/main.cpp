#include <iostream>
#include <vector>
#include <string>

using ll = long long;

class segment_tree {
public:
    segment_tree(const std::vector<ll> &v) {
        n = v.size();
        data.resize(v.size() * 4 + 1, 0);
        this->build(v, 1, 0, n);
    }
    void update(size_t i, ll val) {
        update(1, 0, n, i, val);
    }
    ll get(size_t left_border, size_t right_border) const {
        return get(1, 0, n, left_border, right_border);
    }
private:
    void build(const std::vector<ll> &v,size_t pos, size_t l, size_t r) {
        if (l + 1 == r) {
            data[pos] = v[l];
            return;
        }
        size_t mid = (l + r) / 2;
        build(v, 2 * pos, l, mid);
        build(v, 2 * pos + 1, mid, r);
        data[pos] = data[pos * 2] + data[pos * 2 + 1];
    }
    void update(size_t pos, size_t l, size_t r, size_t i, ll val) {
        if (l + 1 == r) {
            data[pos] += val;
            return;
        }
        size_t mid = (l + r) / 2;
        if (i < mid) {
            update(pos * 2, l, mid, i, val);
        }
        else {
            update(pos * 2 + 1, mid, r, i, val);
        }
        data[pos] = data[pos * 2] + data[pos * 2 + 1];
    }
    ll get(size_t pos, size_t l, size_t r, size_t left_border, size_t right_border) const {
        if (l == left_border && r == right_border) {
            return data[pos];
        }
        size_t mid = (l + r) / 2;
        if (left_border >= mid) {
            return get(pos * 2 + 1, mid, r, left_border, right_border);
        }
        else if (right_border <= mid) {
            return get(pos * 2, l, mid, left_border, right_border);
        }
        else {
            return get(pos * 2, l, mid, left_border, mid)
                + get(pos * 2 + 1, mid, r, mid, right_border);
        }
    }
    size_t n = 0;
    std::vector<ll> data;
};

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
