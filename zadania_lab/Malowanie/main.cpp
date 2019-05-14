#include <iostream>
#include <cmath>
#include <set>

constexpr int MAXN = 1000000;
using namespace std;
int numberWhite;

struct compare {
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) const {
        
        return lhs.second < rhs.first;
    }
};

set<pair<int, int>, compare> zbior;

void colour(int pocz, int kon, set<pair<int, int>, compare> &zbior, bool bialy) {
    auto initPair = make_pair(pocz, kon);
    auto itr = zbior.find(initPair);
    pair<int, int> leftPair, rightPair;
    
    while (itr != zbior.end()) {
        
        if (itr->first < pocz) {
            leftPair = make_pair(itr->first, pocz-1);
            pocz = itr->first;
        }
        
        if (itr->second > kon) {
            rightPair = make_pair(kon+1, itr->second);
            kon = itr->second;
        }
        numberWhite -= itr->second - itr->first + 1;
        zbior.erase(itr);
        itr = zbior.find(initPair);
    }
    if (bialy) {
        numberWhite += kon - pocz + 1;
        zbior.insert(make_pair(pocz, kon));
    }
    else {
        pair<int, int> zero;
        if (leftPair != zero) {
            numberWhite += leftPair.second - leftPair.first + 1;
            zbior.insert(leftPair);
            
        }
        if (rightPair != zero) {
            numberWhite += rightPair.second - rightPair.first + 1;
            zbior.insert(rightPair);
        }
    }
}

int main() {
    numberWhite = 0;
    set<pair<int, int>, compare> zbior;
    int n, m;
    
    cin >> n;
    cin >> m;
    
    for (int i = 0; i < m; ++i) {
        int pocz, kon;
        char c;
        cin >> pocz >> kon >> c;
        colour(pocz, kon, zbior, c == 'B');
        cout << numberWhite << endl;
        
    }
}