#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>

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

    size_t sets_number = 1;
    std::vector<size_t> data;
};

disjoint_set_union::disjoint_set_union(const std::vector<size_t>& vec)
    : data(vec), sets_number(vec.size()) {
}

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
        data[a_ind] = b_ind;
    }
    else {
        data[b_ind] = a_ind;
    }
    sets_number--;
}

size_t disjoint_set_union::sets() const {
    return sets_number - 1;
}

size_t disjoint_set_union::find_root(size_t a) {
    size_t a_ind = a;
    std::vector<size_t> v;
    while (data[a_ind] != a_ind) {
        v.push_back(a_ind);
        a_ind = data[a_ind];
    }
    for (size_t i : v) {
        data[i] = a_ind;
    }
    return a_ind;
}

struct road {
    size_t a;
    size_t b;
};

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

static void give_answer(size_t lim, size_t q) {
    for (size_t i = 0; i < lim; i++)
        fout << "1";
    for (size_t i = lim; i < q; i++)
        fout << "0";
}

int main() {
    size_t n = 0, m = 0, q = 0;
    fin >> n >> m >> q;
    std::vector<size_t> v(n + 1);
    for (size_t i = 1; i <= n; i++)
        v[i] = i;
    disjoint_set_union dsu(v);
    std::vector<road> roads(m + 1);
    roads.front() = { 0, 0 };
    size_t a = 0, b = 0;
    for (size_t i = 1; i <= m; i++) {
        fin >> a >> b;
        roads[i] = { a, b };
    }
    std::vector<size_t> earthquakes(q + 1);
    earthquakes.front() = 0;
    for (size_t i = 1; i <= q; i++) {
        fin >> a;
        earthquakes[i] = a;
    }
    std::vector<road> roads_rem(roads);
    std::for_each(earthquakes.begin(), earthquakes.end(), [&roads_rem](size_t i) {
        roads_rem[i] = { 0, 0 }; });
    for (const auto& i : roads_rem)
        if (i.a != 0)
            dsu.unite(i.a, i.b);

    if (dsu.sets() == 1) {
        give_answer(q, q);
        return 0;
    }
    for (size_t i = q; i > 0; i--) {
        road r = roads[earthquakes[i]];
        dsu.unite(r.a, r.b);
        if (dsu.sets() == 1) {
            give_answer(i - 1, q);
            return 0;
        }
    }
    give_answer(0, q);
    return 0;
}
