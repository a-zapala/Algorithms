#include <iostream>
#include <set>
#include <climits>

using namespace std;

struct compare {
    bool operator() (const pair<int,int>& lhs, const pair<int,int> rhs) const {
        return lhs.second < rhs.first;
    }
};

set<pair<int,int>,compare> zbior;

int main()
{
    ios_base::sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int a,b;
        cin >> a >> b;
        auto p = zbior.insert({a,b});
        if(!p.second) {
            cout << 0;
            return 0;
        }
    }

    int minV = INT_MAX;
    for (auto itr = next(zbior.begin()); itr != zbior.end(); ++itr) {
        auto itr_prev = prev(itr);
        minV = min(minV,itr->first-itr_prev->second);
    }

    cout << minV;
    return 0;
}