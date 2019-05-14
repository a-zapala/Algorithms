#include <iostream>
#include <set>
#include <queue>
#include <values.h>
#include <algorithm>

using namespace std;

struct Node {
    int number, x, y;
    Node(int number, int x, int y) : number(number), x(x), y(y) {}
    Node() {}
};

bool compare_x(const Node &lhs, const Node &rhs) {
    if (lhs.x < rhs.x) {
        return true;
    }
    else if (lhs.x == rhs.x) {
        return lhs.y < rhs.y;
    }
    else {
        return false;
    }
}

bool compare_y(const Node &lhs, const Node &rhs) {
    if (lhs.y < rhs.y) {
        return true;
    }
    else if (lhs.y == rhs.y) {
        return lhs.x < rhs.x;
    }
    else {
        return false;
    }
}

constexpr int MAXN = 200001;
int n;
Node nodes[MAXN];
int dist[MAXN];
vector<Node> axis_x;
vector<Node> axis_y;
vector<int> neighbours[MAXN];
set<pair<int, int>> que;

vector<int> get_neighbours(int i) {
    vector<int> toReturn;
    Node node = nodes[i];
    
    auto itr = lower_bound(axis_x.begin(), axis_x.end(), node, compare_x);
    if (itr != axis_x.begin()) {
        itr--;
        toReturn.push_back(itr->number);
        itr++;
    }
    itr++;
    if (itr != axis_x.end()) {
        toReturn.push_back(itr->number);
    }
    
    itr = lower_bound(axis_y.begin(), axis_y.end(), node, compare_y);
    if (itr != axis_y.begin()) {
        itr--;
        toReturn.push_back(itr->number);
        itr++;
    }
    itr++;
    if (itr != axis_y.end()) {
        toReturn.push_back(itr->number);
    }
    
    return toReturn;
}

void reset_distance() {
    dist[1] = 0;
    for (int i = 2; i <= n; ++i) {
        dist[i] = MAXINT;
        neighbours[i].clear();
    }
}

int count_distance(int n1, int n2) {
    Node node1 = nodes[n1];
    Node node2 = nodes[n2];
    int x = abs(node1.x - node2.x);
    int y = abs(node1.y - node2.y);
    return min(x,y);
}

void update_distance(int u) {
    if(neighbours[u].empty())
        neighbours[u] = get_neighbours(u);
    
    for (auto v : neighbours[u]) {
        if (dist[u] + count_distance(u, v) < dist[v]) {
            if (dist[v] != MAXINT) {
                que.erase({dist[v], v});
            }
            dist[v] = dist[u] + count_distance(u, v);
            que.emplace(dist[v], v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    int x, y;
    for (int i = 1; i <= n; ++i) {
        cin >> x >> y;
        Node node{i, x, y};
        axis_x.push_back(node);
        axis_y.push_back(node);
        nodes[i] = node;
    }
    reset_distance();
    que.emplace(0, 1);
    sort(axis_x.begin(), axis_x.end(), compare_x);
    sort(axis_y.begin(), axis_y.end(), compare_y);
    
    while (!que.empty()) {
        auto itr = que.begin();
        if (dist[n] <= itr->first) {
            break;
        }
        que.erase(itr);
        update_distance(itr->second);
    }
    
    cout << dist[n];
}