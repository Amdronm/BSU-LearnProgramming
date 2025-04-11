#pragma once

#include <vector>
#include <iostream>

class disjoint_set_union {
public:
    disjoint_set_union() = default;
    disjoint_set_union(const std::vector<size_t>&);
    ~disjoint_set_union() = default;
    bool equivalent(size_t, size_t);
    void unite(size_t, size_t);
    size_t sets() const;

    friend std::ostream& operator<<(std::ostream&, const disjoint_set_union&);

private:
    size_t find_root(size_t);

    size_t sets_number = 1;
    std::vector<size_t> data;
};