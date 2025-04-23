#include <vector>
#include <string>
#include <cmath>
#include <fstream>

using std::vector, std::min, std::max, std::size_t;
using llong = long long;

class segment_tree {
public:
    segment_tree() = default;
    segment_tree(const vector<llong>& v) {
        length = v.size();
        data_sum.resize(length * 4 + 1, 0);
        data_min.resize(length * 4 + 1, 0);
        data_max.resize(length * 4 + 1, 0);

        data_assign.resize(length * 4 + 1, 0);
    }
    ~segment_tree() = default;

    void set_val(size_t i, llong val) {
        set_val(1, 0, length, i, val);
    }

    void add_range(size_t left_border, size_t right_border, llong val) {
        add_range(1, 0, length, left_border, right_border, val);
    }

    llong get_sum(size_t left_border, size_t right_border) {
        return get_sum(1, 0, length, left_border, right_border);
    }

    llong get_min(size_t left_border, size_t right_border) {
        return get_min(1, 0, length, left_border, right_border);
    }

    llong get_max(size_t left_border, size_t right_border) {
        return get_max(1, 0, length, left_border, right_border);
    }

private:
    void build(const vector<llong>& v, size_t pos, size_t l, size_t r) {
        if (l + 1 == r) {
            data_sum[pos] = v[l];
            data_min[pos] = v[l];
            data_max[pos] = v[l];
            return;
        }
        size_t mid = (l + r) / 2;
        build(v, 2 * pos, l, mid);
        build(v, 2 * pos + 1, mid, r);
        data_sum[pos] = data_sum[pos * 2] + data_sum[pos * 2 + 1];
        data_min[pos] = min(data_min[pos * 2], data_min[pos * 2 + 1]);
        data_max[pos] = max(data_max[pos * 2], data_max[pos * 2 + 1]);
    }

    void set_val(size_t pos, size_t l, size_t r, size_t i, llong val) {
        push(pos, l, r);
        if (l + 1 == r) {
            data_sum[pos] = val;
            data_min[pos] = val;
            data_max[pos] = val;
            return;
        }
        size_t mid = (l + r) / 2;
        push(pos * 2, l, mid);
        push(pos * 2 + 1, mid, r);
        if (i < mid) {
            set_val(pos * 2, l, mid, i, val);
        }
        else {
            set_val(pos * 2 + 1, mid, r, i, val);
        }
        data_sum[pos] = data_sum[pos * 2] + data_sum[pos * 2 + 1];
        data_min[pos] = min(data_min[pos * 2], data_min[pos * 2 + 1]);
        data_max[pos] = max(data_max[pos * 2], data_max[pos * 2 + 1]);
    }

    void add_range(size_t pos, size_t l, size_t r, size_t left_border, size_t right_border, llong val) {
        push(pos, l, r);
        if (l >= left_border && r <= right_border) {
            data_assign[pos] += val;
            push(pos, l, r);
            return;
        }
        size_t mid = (l + r) / 2;
        push(pos * 2, l, mid);
        push(pos * 2 + 1, mid, r);
        if (left_border >= mid) {
            add_range(pos * 2 + 1, mid, r, left_border, right_border, val);
        }
        else if (right_border <= mid) {
            add_range(pos * 2, l, mid, left_border, right_border, val);
        }
        else {
            add_range(pos * 2, l, mid, left_border, mid, val);
            add_range(pos * 2 + 1, mid, r, mid, right_border, val);
        }
        data_sum[pos] = data_sum[pos * 2] + data_sum[pos * 2 + 1];
        data_min[pos] = min(data_min[pos * 2], data_min[pos * 2 + 1]);
        data_max[pos] = max(data_max[pos * 2], data_max[pos * 2 + 1]);
    }

    llong get_sum(size_t pos, size_t l, size_t r, size_t left_border, size_t right_border) {
        push(pos, l, r);
        if (l == left_border && r == right_border) {
            return data_sum[pos];
        }
        size_t mid = (l + r) / 2;
        if (left_border >= mid) {
            return get_sum(pos * 2 + 1, mid, r, left_border, right_border);
        }
        else if (right_border <= mid) {
            return get_sum(pos * 2, l, mid, left_border, right_border);
        }
        else {
            return get_sum(pos * 2, l, mid, left_border, mid)
                + get_sum(pos * 2 + 1, mid, r, mid, right_border);
        }
    }

    llong get_min(size_t pos, size_t l, size_t r, size_t left_border, size_t right_border) {
        push(pos, l, r);
        if (l == left_border && r == right_border) {
            return data_min[pos];
        }
        size_t mid = (l + r) / 2;
        if (left_border >= mid) {
            return get_min(pos * 2 + 1, mid, r, left_border, right_border);
        }
        else if (right_border <= mid) {
            return get_min(pos * 2, l, mid, left_border, right_border);
        }
        else {
            return min(get_min(pos * 2, l, mid, left_border, mid),
                get_min(pos * 2 + 1, mid, r, mid, right_border));
        }
    }

    llong get_max(size_t pos, size_t l, size_t r, size_t left_border, size_t right_border) {
        push(pos, l, r);
        if (l == left_border && r == right_border) {
            return data_max[pos];
        }
        size_t mid = (l + r) / 2;
        if (left_border >= mid) {
            return get_max(pos * 2 + 1, mid, r, left_border, right_border);
        }
        else if (right_border <= mid) {
            return get_max(pos * 2, l, mid, left_border, right_border);
        }
        else {
            return max(get_max(pos * 2, l, mid, left_border, mid),
                get_max(pos * 2 + 1, mid, r, mid, right_border));
        }
    }

    void push(size_t pos, size_t l, size_t r) {
        if (data_assign[pos] != 0) {
            data_sum[pos] += data_assign[pos] * (r - l);
            data_min[pos] += data_assign[pos];
            data_max[pos] += data_assign[pos];
            if (l + 1 < r) {
                data_assign[pos * 2] += data_assign[pos];
                data_assign[pos * 2 + 1] += data_assign[pos];
            }
        }
        data_assign[pos] = 0;
    }

    size_t length = 0;
    vector<llong> data_sum;
    vector<llong> data_min;
    vector<llong> data_max;

    vector<llong> data_assign;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    fin.tie(nullptr);
    fout.tie(nullptr);

    size_t n = 0;
    fin >> n;
    vector<llong> v(n, 0);
    segment_tree st(v);

    size_t query = 0;
    llong a, b, i, val;
    while (fin >> query) {
        switch (query) {
        case 1:
            fin >> i >> val;
            st.set_val(i, val);
            break;

        case 2:
            fin >> a >> b >> val;
            st.add_range(a, b + 1, val);
            break;

        case 3:
            fin >> a >> b;
            fout << st.get_sum(a, b + 1) << "\n";
            break;

        case 4:
            fin >> a >> b;
            fout << st.get_min(a, b + 1) << "\n";
            break;

        case 5:
            fin >> a >> b;
            fout << st.get_max(a, b + 1) << "\n";
            break;

        default:
            return 0;
        }
    }
    return 0;
}

/*
5
2 0 4 7
3 2 3
1 2 -10
4 0 3
2 3 4 9
5 0 4
0

14
-10
16
*/


/*
6
3 1 4    
4 2 2    
5 0 5    
2 1 3 0  
1 5 0    
3 0 5    
2 0 5 100
1 2 0    
4 0 5    
5 0 5    
3 2 2    
0

0
0
0
0
0
100
0
*/

/*
3
3 0 2   
4 0 2   
5 0 2   
1 1 5   
2 0 0 -2
2 2 2 3 
3 0 2   
4 0 1   
5 1 2   
1 1 -8  
2 0 2 1 
3 0 2   
4 0 2   
5 0 2   
0

0
0
0
6
-2
5
-4
-7
4
*/

/*
      
8
2 0 4 10
2 3 6 -5
3 2 5   
4 0 7   
5 0 2   
1 4 100 
3 3 5   
4 3 5   
5 3 5   
2 0 7 1
3 0 7   
4 0 7   
5 0 7   
0

30
5
-5
10
100
-5
100
133
-4
101
*/

/*
10
2 0 9 5
3 0 9
4 0 9
5 0 9
1 0 -10
1 9 10
3 0 1
4 0 9
5 0 9
2 1 8 -3
3 0 9
4 5 5
5 8 9
0

50
5
5
-5
-10
10
16
2
10
*/