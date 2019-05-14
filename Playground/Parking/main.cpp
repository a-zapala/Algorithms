#include <iostream>
#include <map>
#include <list>
#include <unordered_map>

using namespace std;

unordered_map< int, pair<bool,bool>> wolne_odwiedzone;
unordered_map<int , list<int>> koledzy;

int main() {
    int n,m;
    cin>>n;
    cin>>m;

    for (int i = 1; i < n+1; ++i) {
        bool x;
        cin>>x;
        wolne_odwiedzone[i] = make_pair(x,false);
    }

    for (int j = 0; j < m; ++j) {
        int first,second;
        cin>>first;
        cin>>second;
        koledzy.find()

    }

    for( auto element : koledzy) {
        for( auto x : element.second) {
            cout<< ' ' << x;
        }
        cout<< endl;
    }

}