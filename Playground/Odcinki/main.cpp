#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    unordered_map<int, vector<pair<int, bool>>> str;
    
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y1, y2;
        cin >> x >> y1 >> y2;
        str[x].push_back({y1, true});
        str[x].push_back({y2, false});
    }
    long long int suma = 0;
    
    for (auto &pair : str) {
        auto &vec = pair.second;
        sort(vec.begin(),vec.end());
        long long int temp = 0;
        for (  auto itr = vec.begin();  itr != vec.end(); itr++) {
            if(itr->second){
               temp++;
            } else {
                suma+=--temp;
            }
        }
    }
    
    cout <<suma;
}