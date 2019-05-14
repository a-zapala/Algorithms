#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

constexpr int LOG = 12;

using code_type = unsigned long long int;
std::vector<code_type> subword_labeling[LOG];
std::vector<char> word;
int n;

inline int log_2(int x) {
    int ans = 0;
    while (x >>= 1) ans++;
    return ans;
}

inline int pow_2(int x) {
    return (x > 0 ? 2 << (x - 1) : 1);
}

template<typename T>
T optimize_labeling(std::vector<T> &vector) {
    std::vector<std::pair<T, int>> tmp;
    
    for (int i = 0; i < vector.size(); ++i) {
        tmp.emplace_back(vector[i], i);
    }
    
    std::sort(tmp.begin(), tmp.end());
    T cur_num = 1;
    T cur_value = tmp[0].first;
    
    for (auto it = tmp.begin(); it != tmp.end(); ++it) {
        if (it->first == cur_value) {
            vector[it->second] = cur_num;
        }
        else {
            cur_value = it->first;
            vector[it->second] = ++cur_num;
        }
    }
    return cur_num;
}

void preprocesing_word() {
    for (int i = 0; i < n; ++i) {
        subword_labeling[0].push_back(word[i] - 96);
    }
    
    code_type max_number = 27;
    
    for (int i = 0; i < std::min(log_2(n), LOG); ++i) {
        
        max_number++;
        for (int j = 0; j < subword_labeling[i].size() - pow_2(i); ++j) {
            subword_labeling[i + 1].push_back(subword_labeling[i][j] * max_number + subword_labeling[i][j + pow_2(i)]);
        }
        
        if (i > 0) {
            max_number = optimize_labeling(subword_labeling[i + 1]);
        } else {
            max_number*=std::pow(27,i+1);
        }
    }
}

int same_len_query(int a, int b, int c, int d) {
    assert(b - a == d - c);
    int level = std::min(log_2(b - a), LOG);
    
    int i = 0;
    
    while (a + i + pow_2(level) <= b) {
        if (subword_labeling[level][a + i] < subword_labeling[level][c + i]) {
            return -1;
        }
        else if (subword_labeling[level][a + i] > subword_labeling[level][c + i]) {
            return 1;
        }
        else {
            i += pow_2(level);
        }
    }
    
    if (subword_labeling[level][b - pow_2(level) + 1] < subword_labeling[level][d - pow_2(level) + 1]) {
        return -1;
    }
    else if (subword_labeling[level][b - pow_2(level) + 1] == subword_labeling[level][d - pow_2(level) + 1]) {
        return 0;
    }
    else {
        return 1;
    }
}

int query(int a, int b, int c, int d) {
    if (b - a == d - c) {
        return same_len_query(a, b, c, d);
    }
    else if (b - a > d - c) {
        int res = same_len_query(a, a + (d - c), c, d);
        if (res == 0) {
            return 1;
        }
        else {
            return res;
        }
    }
    else {
        return (-1) * query(c, d, a, b);
    }
}

int main() {
    
    std::ios_base::sync_with_stdio(false);
    int m;
    
    std::cin >> n >> m;
    char s;
    
    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        word.push_back(s);
    }
    
    preprocesing_word();
    
    int a, b, c, d;
    for (int j = 0; j < m; ++j) {
        std::cin >> a >> b >> c >> d;
        int res = query(a - 1, b - 1, c - 1, d - 1);
        if (res == -1) {
            std::cout << "<";
        }
        else if (res == 0) {
            std::cout << "=";
        }
        else {
            std::cout << ">";
        }
        std::cout << std::endl;
    }
    
}