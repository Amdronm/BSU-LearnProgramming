#include "disjoint_set_union.h"

#include <ctime>

disjoint_set_union::disjoint_set_union(const std::vector<size_t> &vec)
	: data(vec), sets_number(vec.size()) {}

bool disjoint_set_union::equivalent(size_t a, size_t b) {
	size_t a_ind = find_root(a);
	size_t b_ind = find_root(b);
	return a_ind == b_ind;
}

void disjoint_set_union::unite(size_t a, size_t b) {
	if (equivalent(a, b)) return;
	std::srand(time(NULL));
	bool r = static_cast<bool>(std::rand() % 2);
	size_t a_ind = find_root(a);
	size_t b_ind = find_root(b);
	if (r) {
		data[a_ind - 1] = b_ind;
	}
	else {
		data[b_ind - 1] = a_ind;
	}
	sets_number--;
}

size_t disjoint_set_union::sets() const {
	return sets_number;
}

size_t disjoint_set_union::find_root(size_t a) {
	size_t a_ind = a;
	std::vector<size_t> v;
	while (data[a_ind - 1] != a_ind) {
		v.push_back(a_ind);
		a_ind = data[a_ind - 1];
	}
	for (size_t i : v) {
		data[i - 1] = a_ind;
	}
	return a_ind;
}