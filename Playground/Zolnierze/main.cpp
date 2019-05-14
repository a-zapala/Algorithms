#include <iostream>


using namespace std;

constexpr int MAXN = 500004;

int P[MAXN];
int L[MAXN];

int find(int a, int *u)
{
    if (u[a] == a)
        return a;
    else {
        int r = find(u[a], u);
        u[a] = r;
        return r;
    }
}

void unio(int a, int b, int *u)
{
    u[find(a, u)] = find(b, u);
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i <= n + 1; ++i) {
        P[i] = i;
        L[i] = i;
    }

    for (int j = 0; j < n; ++j) {
        int x;
        cin >> x;
        int l = find(x - 1, L);
        int r = find(x + 1, P);

        unio(x, x - 1, L);
        unio(x, x + 1, P);

        if (l == 0)
            l = -1;

        if (r == n + 1)
            r = -1;

        cout << l << " " << r << endl;
    }
}
