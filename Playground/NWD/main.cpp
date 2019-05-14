#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int,int> mapa;

int NWD(int a, int b) {
    if(b == 0)
        return a;
    else return NWD(b, a % b);
}
constexpr int M = 131072;
int tree[2*M-1];

void aktu(int u) {
  tree[u] = NWD(tree[2*u],tree[2*u+1]);
}
void insert(int x, int val) {
    int v = M+x;
    tree[v] = val;
    do {
        v /=2;
        aktu(v);
    } while(v!=1);
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        char c;
        int x;
        cin >> c >> x;

        if(mapa.find(x) == mapa.end())
            mapa[x] = i;

        if(c == '-')
            insert(mapa[x],0);
        else
            insert(mapa[x],x);

        cout << max(tree[1],1) << endl;
    }
    return 0;
}