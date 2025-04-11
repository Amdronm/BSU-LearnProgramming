#include "disjoint_set_union.h"

#include <fstream>
#include <algorithm>

struct road {
    size_t a;
    size_t b;
    friend std::ostream& operator<<(std::ostream& out, const road& r) {
        out << r.a << " " << r.b;
        return out;
    }
};

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");

static void give_answer(size_t lim, size_t q) {
    for (size_t i = 0; i < lim; i++)
        fout << "1";
    for (size_t i = lim; i < q; i++)
        fout << "0";
}

template<typename T> static void print_vec(const std::vector<T>& v) {
    std::for_each(v.begin(), v.end(), [](T i) {std::cout << i << "\n"; });
    std::cout << std::endl;
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

    //print_vec(roads_rem);
    if (dsu.sets() == 1) {
        give_answer(q, q);
        return 0;
    }
    //std::cout << dsu;
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