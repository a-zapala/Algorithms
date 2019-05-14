#include <iostream>
#include <unordered_set>

using namespace std;

constexpr int MAXA = 1000000000;
int main()
{
    ios_base::sync_with_stdio(0);
    int n,d;
    unordered_set<int> zbior;
    cin >> n >> d;
    int suma = 0;

    for (int i = 0; i < n; ++i) {
        int c,a,l,p;
        cin >> c >> a;

        l = a-d;
        p = a+d;

        if(c == 1) {

            zbior.insert(a);

            if(l >= 0 && zbior.find(l) != zbior.end())
                suma++;

            if(p<=MAXA && zbior.find(p) != zbior.end() )
                suma++;
        } else {
            zbior.erase(a);

            if(l >= 0 && zbior.find(l) != zbior.end())
                suma--;

            if(p<=MAXA && zbior.find(p) != zbior.end() )
                suma--;
        }
        if(suma > 0 ) {
            cout << "TAK" << endl;
        } else {
            cout << "NIE" << endl;
        }
    }

}