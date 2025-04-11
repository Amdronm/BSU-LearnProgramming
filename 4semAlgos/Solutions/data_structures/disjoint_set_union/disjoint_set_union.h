#pragma once

#include <vector>

class disjoint_set_union {
public:
	disjoint_set_union() = default;
	disjoint_set_union(const std::vector<size_t>&);
	~disjoint_set_union() = default;
	bool equivalent(size_t, size_t);
	void unite(size_t, size_t);
	size_t sets() const;

private:
	size_t find_root(size_t);

	size_t sets_number = 0;
	std::vector<size_t> data;
};