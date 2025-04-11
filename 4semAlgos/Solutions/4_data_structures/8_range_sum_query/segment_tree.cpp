#include "segment_tree.h"

segment_tree::segment_tree(const std::vector<ll>& v) {
    n = v.size();
    data.resize(v.size() * 4 + 1, 0);
    this->build(v, 1, 0, n);
}

void segment_tree::update(size_t i, ll val) {
    update(1, 0, n, i, val);
}

ll segment_tree::get(size_t left_border, size_t right_border) const {
    return get(1, 0, n, left_border, right_border);
}

void segment_tree::build(const std::vector<ll>& v, size_t pos, size_t l, size_t r) {
    if (l + 1 == r) {
        data[pos] = v[l];
        return;
    }
    size_t mid = (l + r) / 2;
    build(v, 2 * pos, l, mid);
    build(v, 2 * pos + 1, mid, r);
    data[pos] = data[pos * 2] + data[pos * 2 + 1];
}

void segment_tree::update(size_t pos, size_t l, size_t r, size_t i, ll val) {
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

ll segment_tree::get(size_t pos, size_t l, size_t r, size_t left_border, size_t right_border) const {
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