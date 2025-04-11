#pragma once

#include <vector>

using ll = long long;

class segment_tree {
public:
    segment_tree() = default;
    segment_tree(const std::vector<ll> &);
    ~segment_tree() = default;

    void update(size_t, ll);
    ll get(size_t, size_t) const;

private:
    void build(const std::vector<ll> &, size_t, size_t, size_t);
    void update(size_t, size_t, size_t, size_t, ll);
    ll get(size_t pos, size_t l, size_t r, size_t left_border, size_t right_border) const;

    size_t n = 0;
    std::vector<ll> data;
};