#include <iostream>
#include <vector>
#include <climits>

using namespace std;

constexpr int MAXN = 500001;

int leftChild[MAXN];
int rightChild[MAXN];
int deeperPathDown[MAXN];
int jump[20][MAXN]
int parent[MAXN];
int high[MAXN];
int maxDistance[MAXN];
int distJunction[MAXN];
bool sideJunction[MAXN];
int junction[MAXN];
int n, m;

void check_prepocesing(int n) {
    for (int i = 1; i <= n; ++i) {
        cout << " " << i << ": "
             << " Parent " << parent[i]
             << " Left Child " << leftChild[i]
             << " Right Child " << rightChild[i]
             << " Height " << high[i]
             << " DeeperPathDown " << deeperPathDown[i]
             << " Max Distance " << maxDistance[i]
             << " Junction " << junction[i] << endl;
    }
}

void clear() {
    for (int i = 1; i <= n; ++i) {
        high[i] = -1;
    }
}

void setHigh(int i, int v, int child) {
    if (i != -1) {
        if (high[i] == -1 || high[i] < v) {
            deeperPathDown[i] = child;
            high[i] = v;
            setHigh(parent[i], v + 1, i);
        }
    }
}

void setHigh() {
    vector<int> leafes;
    for (int i = 1; i <= n; ++i) {
        if (leftChild[i] == -1 && rightChild[i] == -1) {
            leafes.push_back(i);
        }
    }
    for (int i  : leafes) {
        setHigh(i, 0, -1);
    }
}

void setDistance(int i, int maxCurrentDistance, int junctionWithMaxCurrentDistance, int distFromJ, bool side) {
    
    if (high[i] < maxCurrentDistance) {
        maxDistance[i] = maxCurrentDistance;
        junction[i] = junctionWithMaxCurrentDistance;
        distJunction[i] = distFromJ;
        sideJunction[i] = side;
    }
    else {
        maxDistance[i] = high[i];
        junction[i] = -1;
    }
    
    if (leftChild[i] != -1) {
        if (rightChild[i] != -1) {
            if (maxCurrentDistance < high[rightChild[i]] + 1) {
                setDistance(leftChild[i], high[rightChild[i]] + 2, i,1, false);
            }
            else {
                setDistance(leftChild[i], maxCurrentDistance + 1, junctionWithMaxCurrentDistance,distFromJ+1, side);
            }
        }
        else {
            setDistance(leftChild[i], maxCurrentDistance + 1, junctionWithMaxCurrentDistance, distFromJ+1, side);
        }
    }
    
    if (rightChild[i] != -1) {
        if (leftChild[i] != -1) {
            if (maxCurrentDistance < high[leftChild[i]] + 1) {
                setDistance(rightChild[i], high[leftChild[i]] + 2, i, 1, true);
            }
            else {
                setDistance(rightChild[i], maxCurrentDistance + 1, junctionWithMaxCurrentDistance, distFromJ +1, side);
            }
        }
        else {
            setDistance(rightChild[i], maxCurrentDistance + 1, junctionWithMaxCurrentDistance, distFromJ +1, side);
        }
    }
    
}

void setDistance() {
    setDistance(1, 0, 0, 0, false);
}

void proprocesing() {
    clear();
    setHigh();
    setDistance();
}

int retChild(int i, int d) {
    while (d != 0) {
        i = deeperPathDown[i];
        d--;
    }
    return i;
}

int returnMaxDis(int i, int d) {
    
    if( d == distJunction[i]) {
        return junction[i];
    }
    
    if( d > distJunction[i]) {
        if(sideJunction[i]) {
            return retChild(leftChild[junction[i]], d - distJunction[i]-1);
        } else {
            return retChild(rightChild[junction[i]], d - distJunction[i]-1);
        }
    }
    
    while (d != 0) {
        i = parent[i];
        d--;
    }
    
    return i;
    
}

int query(int i, int d) {
    if (maxDistance[i] < d) {
        return -1;
    }
    else {
        if (junction[i] == -1) {
            return retChild(i, d);
        }
        else {
            return returnMaxDis(i, d);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    parent[1] = -1;
    
    for (int i = 1; i <= n; ++i) {
        cin >> leftChild[i];
        cin >> rightChild[i];
        parent[leftChild[i]] = i;
        parent[rightChild[i]] = i;
    }
    
    proprocesing();
    //check_prepocesing(n);
    
    cin >> m;
    int a, d;
    
    for (int j = 0; j < m; ++j) {
        cin >> a >> d;
        cout << query(a, d) << endl;
    }
    
    
}

