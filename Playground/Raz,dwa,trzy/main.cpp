#include <iostream>

using namespace std;
struct Node {
    bool jedynka;
    bool dwojka;
    bool trojka;
    bool jeden_dwa;
    bool dwa_trzy;
    bool jeden_dwa_trzy;
};


constexpr int M = 524288;
Node tree[2*M-1];


void aktu(int u) {
    tree[u].jedynka = tree[2*u].jedynka || tree[2*u+1].jedynka;
    tree[u].dwojka = tree[2*u].dwojka || tree[2*u+1].dwojka;
    tree[u].trojka = tree[2*u].trojka || tree[2*u+1].trojka;
    tree[u].jeden_dwa = tree[2*u].jeden_dwa || tree[2*u+1].jeden_dwa || (tree[2*u].jedynka &&  tree[2*u+1].dwojka);
    tree[u].dwa_trzy = tree[2*u].dwa_trzy || tree[2*u+1].dwa_trzy || (tree[2*u].dwojka &&  tree[2*u+1].trojka);
    tree[u].jeden_dwa_trzy = tree[2*u].jeden_dwa_trzy || tree[2*u+1].jeden_dwa_trzy || (tree[2*u].jedynka && tree[2*u+1].dwa_trzy) || (tree[2*u].jeden_dwa && tree[2*u+1].trojka);
}
void insert(int x, int val) {
    int v = M+x;
    tree[v].jedynka=false;
    tree[v].dwojka=false;
    tree[v].trojka = false;
    if(val==1)
        tree[v].jedynka=true;
    else if (val == 2)
        tree[v].dwojka=true;
    else
        tree[v].trojka = true;
    do {
        v /=2;
        aktu(v);
    } while(v!=1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n,m;
    cin >> n;

    for (int i = 1; i <=n ; ++i) {
        int v;
        cin >> v;
        insert(i,v);
    }

    if(tree[1].jeden_dwa_trzy){
        cout << "TAK" << endl;
    } else {
        cout << "NIE" << endl;
    }

    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x,val;
        cin >> x >> val;
        insert(x,val);

        if(tree[1].jeden_dwa_trzy){
            cout << "TAK" << endl;
        } else {
            cout << "NIE" << endl;
        }

    }
}