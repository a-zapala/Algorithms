#include <iostream>
#include <tuple>
#include <list>
#include <set>
#include <cassert>


using namespace std;

constexpr int MAXN = 100001;
constexpr int MAXINDEX = 131072;

struct Session {
    int number;
    int first;
    int last;
    
    Session() : number(0), first(0), last(0) {};
    
    Session(int number, int first, int last) : number(number), first(first), last(last) {}
};

struct Node {
    bool exist;
    int number;
    int value;
    
    Node() : exist(false) {}
    
    Node(const Session &s) : exist(true), number(s.number), value(s.last) {}
    
    Node(int number, int value) : number(number), value(value), exist(true) {}
    
};

struct compareMin {
    bool operator()(const Session &lhs, const Session &rhs) const {
        
        if (lhs.first != rhs.first) {
            return lhs.first < rhs.first;
        }
        else if (lhs.last != rhs.last) {
            return lhs.last < rhs.last;
        }
        else {
            return lhs.number < rhs.number;
        }
    }
};

struct compareMax {
    bool operator()(const Session &lhs, const Session &rhs) const {
        if (lhs.first != rhs.first) {
            return lhs.first < rhs.first;
        }
        else if (lhs.last != rhs.last) {
            return lhs.last > rhs.last;
        }
        else {
            return lhs.number < rhs.number;
        }
    }
};

int n;
Session sessions[MAXN];
Node treeMaxLast[2 * MAXINDEX];
Node treeMinLast[2 * MAXINDEX];
set<Session, compareMin> minSession;
set<Session, compareMax> maxSession;

void removeFromMinTree(int i) {
    Session session = sessions[i];
    int v = MAXINDEX + session.first;
    treeMinLast[v] = Node();
    v /= 2;
    
    while (v != 0) {
        if (treeMinLast[v].number == session.number) {
            if (treeMinLast[2 * v].exist && treeMinLast[2 * v + 1].exist) {
                if (treeMinLast[2 * v].value < treeMinLast[2 * v + 1].value) {
                    treeMinLast[v] = treeMinLast[2 * v];
                }
                else {
                    treeMinLast[v] = treeMinLast[2 * v + 1];
                }
            }
            else if (treeMinLast[2 * v].exist) {
                treeMinLast[v] = treeMinLast[2 * v];
            }
            else if (treeMinLast[2 * v + 1].exist) {
                treeMinLast[v] = treeMinLast[2 * v + 1];
            }
            else {
                treeMinLast[v] = Node();
            }
        }
        else {
            return;
        }
        v /= 2;
    }
    
}

void removeFromMaxTree(int i) {
    Session session = sessions[i];
    int v = MAXINDEX + session.first;
    treeMaxLast[v] = Node();
    v /= 2;
    
    while (v != 0) {
        if (treeMaxLast[v].number == session.number) {
            if (treeMaxLast[2 * v].exist && treeMaxLast[2 * v + 1].exist) {
                if (treeMaxLast[2 * v].value > treeMaxLast[2 * v + 1].value) {
                    treeMaxLast[v] = treeMaxLast[2 * v];
                }
                else {
                    treeMaxLast[v] = treeMaxLast[2 * v + 1];
                }
            }
            else if (treeMaxLast[2 * v].exist) {
                treeMaxLast[v] = treeMaxLast[2 * v];
            }
            else if (treeMaxLast[2 * v + 1].exist) {
                treeMaxLast[v] = treeMaxLast[2 * v + 1];
            }
            else {
                treeMaxLast[v] = Node();
            }
        }
        else {
            return;
        }
        v /= 2;
    }
}

void putToMinTree(int i) { //OK
    assert(1 <= i && i <= n);
    Session session = sessions[i];
    int v = MAXINDEX + session.first;
    Node toInput = Node(session);
    
    while (v != 0) {
        if (!treeMinLast[v].exist || (treeMinLast[v].exist && treeMinLast[v].value > toInput.value)) {
            treeMinLast[v] = toInput;
        }
        else {
            return;
        }
        v /= 2;
    }
}

void putToMaxTree(int i) { //OK
    assert(1 <= i && i <= n);
    Session session = sessions[i];
    int v = MAXINDEX + session.first;
    Node toInput = Node(session);
    
    while (v != 0) {
        if (!treeMinLast[v].exist || (treeMinLast[v].exist && treeMaxLast[v].value < toInput.value)) {
            treeMaxLast[v] = session;
        }
        else {
            return;
        }
        v /= 2;
    }
}

void buildTree() { 
    int recentFirst = -1;
    
    for (auto session : minSession) {
        if (session.first != recentFirst) {
            recentFirst = session.first;
            putToMinTree(session.number);
        }
    }
    
    recentFirst = -1;
    for (auto session : maxSession) {
        if (session.first != recentFirst) {
            recentFirst = session.first;
            putToMaxTree(session.number);
        }
    }
}

void remove(int i) {
    Session s = sessions[i];
    auto itr = minSession.find(s);
    auto before = itr;
    before--;
    auto after = itr;
    after++;
    
    assert(itr != minSession.end());
    
    
    if ((itr != minSession.begin() && before->first != s.first) || itr == minSession.begin()) {
        removeFromMinTree(s.number);
        if (after != minSession.end() && after->first == s.first) {
            putToMinTree(after->number);
        }
    }
    minSession.erase(s);
    
    itr = maxSession.find(s);
    before = itr;
    before--;
    after = itr;
    after++;
    
    assert(itr != maxSession.end());
    
    if ((itr != maxSession.begin() && before->first != s.first) || itr == maxSession.begin()) {
        removeFromMaxTree(s.number);
        if (after != maxSession.end() && after->first == s.first) {
            putToMaxTree(after->number);
        }
    }
    maxSession.erase(s);
}

int in_query(int a, int b) {
    int va = MAXINDEX + a, vb = MAXINDEX + b;
    
    if (treeMinLast[va].exist && treeMinLast[va].value <= b) {
        return treeMinLast[va].number;
    }
    
    if (treeMinLast[vb].exist && treeMinLast[vb].value <= b) {
        return treeMinLast[vb].number;
    }
    
    while (va / 2 != vb / 2) {
        if (va % 2 == 0 && treeMinLast[va + 1].exist && treeMinLast[va + 1].value <= b) {
            return treeMinLast[va + 1].number;
        }
        if (vb % 2 == 1 && treeMinLast[vb - 1].exist && treeMinLast[vb - 1].value <= b) {
            return treeMinLast[vb - 1].number;
        }
        va /= 2;
        vb /= 2;
    }
    return -1;
}

int over_query(int a, int b) {
    int v = MAXINDEX + a;
    
    if (treeMaxLast[v].exist && treeMaxLast[v].value >= b) {
        return treeMaxLast[v].number;
    }
    
    while (v != 1) {
        if (v % 2 == 1 && treeMaxLast[v-1].exist && treeMaxLast[v-1].value >= b) {
            return treeMaxLast[v-1].number;
        }
        v/=2;
    }
    
    return -1;
}

int none_query(int a, int b) {
    int ret = -1;
    if (a >= 1) {
        ret = in_query(0, a - 1);
    }
    if (ret == -1) {
        ret = in_query(b + 1, MAXN + 1);
    }
    return ret;
}

int some_query(int a, int b) {
    int ret = in_query(a, b);
    
    if (ret == -1) {
        ret = over_query(a, a);
    }
    
    if (ret == -1) {
        ret = over_query(b, b);
    }
    
    return ret;
}

int query(string &str, int a, int b) {
    int ret = -1;
    if (str == "in") {
        ret = in_query(a, b);
    }
    else if (str == "over") {
        ret = over_query(a, b);
    }
    else if (str == "none") {
        ret = none_query(a, b);
    }
    else if (str == "some") {
        ret = some_query(a, b);
    }
    
    if (ret != -1) {
        remove(ret);
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int q;
    cin >> n;
    int a, b;
    
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b;
        sessions[i] = Session(i, a, b);
        minSession.insert(sessions[i]);
        maxSession.insert(sessions[i]);
    }
    
    for (int i = 0; i < 2 * MAXINDEX; ++i) {
        treeMinLast[i] = Node();
        treeMaxLast[i] = Node();
    }
    
    buildTree();
    
    cin >> q;
    string str;
    for (int i = 1; i <= q; ++i) {
        cin >> str >> a >> b;
        cout << query(str, a, b) << endl;
        
    }
}