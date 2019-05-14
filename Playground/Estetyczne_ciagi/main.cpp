#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

int main() {
   int n;
   cin >> n;
   vector<int> wyrazy;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        wyrazy.push_back(x);
    }

    sort (wyrazy.begin(), wyrazy.end());

    if(n == 0 ) {
        cout<< 0;
        return 0;
    }

    int last_value = wyrazy[0];
    int len = 0;
    map<int, int> mapa;

    for(int i = 0 ; i< n ;i++) {
        if(wyrazy[i] != last_value){
            mapa[last_value] = len;
            last_value = wyrazy[i];
            len = 1;
        } else {
            len++;
        }
    }
    mapa[last_value] = len;

    int maxLenght = INT_MIN;
    int currentLenght = mapa.begin()->second;
    last_value = mapa.begin()->first;

    for ( auto iter = mapa.begin()++; iter != mapa.end(); iter++ ){
        auto element = *iter;
        if( last_value +1 == element.first) {
            last_value = element.first;
            currentLenght+=element.second;
        } else {
            maxLenght = max(maxLenght,currentLenght);
            currentLenght = element.second;
            last_value = element.first;
        }
    }
    maxLenght = max(maxLenght,currentLenght);
    cout<<maxLenght;


}