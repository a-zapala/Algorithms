#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

bool compare(const pair<int, pair<int, int>> &lhs, const pair<int, pair<int, int>> &rhs) {
    if (lhs.first < rhs.first) {
        return true;
    }
    else if (lhs.first == rhs.first) {
        if (lhs.second.first < rhs.second.first) {
            return true;
        }
        else if (lhs.second.first == rhs.second.first) {
            return lhs.second.second > rhs.second.second;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

struct compare {
    bool operator()(const pair<int, int> &lhs, const pair<int, int> rhs) const {
        return lhs.second < rhs.first;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    
    vector<pair<int, pair<int, int>>> vec;
    
    int n;
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        int p, k, w;
        cin >> p >> k >> w;
        vec.push_back({p, {k, w}});
    }
    
    sort(vec.begin(), vec.end(), compare);
    
    long long suma = 0;
    long long max_suma_akt = 0;
    int aktu_last = 0;
    map<int, long long> mapa;
    
    for (int j = 0; j < n; ++j) {
        if (aktu_last < vec[j].first) {
            suma += max_suma_akt;
            mapa.clear();
            mapa[vec[j].second.first] = vec[j].second.second;
            max_suma_akt = vec[j].second.second;
            aktu_last = vec[j].second.first;
        }
        else {
            long long max_mnie = 0;
            int index_mniej = 0;
            auto itr = mapa.begin();
            while (itr->first < vec[j].first) {
                auto prev = itr;
                if (itr->second > max_mnie) {
                    max_mnie = itr->second;
                    index_mniej = itr->first;
                }
                itr++;
                mapa.erase(prev);
               
            }
            
            mapa[index_mniej] = max_mnie;
            
            auto ptr = mapa.find(vec[j].second.first);
            
            if (ptr == mapa.end() || max_mnie + vec[j].second.second > ptr->second) {
                mapa[vec[j].second.first] = max_mnie + vec[j].second.second;
            }
            
            max_suma_akt = max(max_mnie + vec[j].second.second, max_suma_akt);
            aktu_last = max(aktu_last, vec[j].second.first);
        }
    }
    
    if (!mapa.empty()) {
        suma += max_suma_akt;
    }
    cout << suma;
    
    return 0;
}