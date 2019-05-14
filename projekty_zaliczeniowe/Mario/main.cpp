#include <iostream>
#include <climits>
#include <vector>
#include <array>
#include <cmath>
#include <set>
#include <queue>
#include <tuple>

constexpr int MAXN = 100000;
constexpr int MAXS = 20;

using namespace std;
char tor[MAXN];
int n, K, U;

bool history[MAXS][MAXN];
using Step = tuple<int, int, int>; // i, s, time
int pow_of_2[MAXS];

void fill_pow() {
    pow_of_2[0] = 1;
    for (int i = 1; i < MAXS; ++i) {
        pow_of_2[i] = 2 * pow_of_2[i - 1];
    }
}

struct compare {
    bool operator()(const Step &step1, const Step &step2) const {
        return get<2>(step1) > get<2>(step2);
    }
};

int value_of_s(int s) {
    s = s > MAXS-1 ? MAXS -1 : s;
    return pow_of_2[s];
}

bool check_history(Step &step) {
    
    int i = get<0>(step);
    int s = get<1>(step);
    
    if (value_of_s(s) > n) {
        s = MAXS - 1;
    }
    
    if (history[s][i]) {
        return false;
    }
    
    history[s][i] = true;
    
    return true;
}

void next_step(Step &step, vector<Step> &toReturn) {
    int i = get<0>(step);
    int s = get<1>(step);
    int time = get<2>(step);
    
    toReturn.clear();
    
    if (i >= 0 && i < n - 1) {
        
        char sign = tor[i];
        
        if (sign == '.') {
            time++;
            toReturn.emplace_back(i + value_of_s(s), s, time);
            toReturn.emplace_back(i + 1, s, time);
        }
        else if (sign == '*') {
            time++;
            toReturn.emplace_back(i + 1, s + 1, time);
            toReturn.emplace_back(i + value_of_s(s + 1), s + 1, time);
        }
        else if (sign == '>') {
            toReturn.emplace_back(i + K, s, time);
        }
        else if (sign == '<') {
            toReturn.emplace_back(i - K, s, time);
        }
        else if (sign == 'U') {
            time += U;
            time++;
            toReturn.emplace_back(i + 1, s, time);
            toReturn.emplace_back(i + value_of_s(s), s, time);
        }
    }
}

void simulation() {
    Step firstStep = make_tuple(0, 1, 0);
    priority_queue<Step, vector<Step>, compare> queue;
    queue.emplace(firstStep);
    vector<Step> pomV;
    
    while (!queue.empty()) {
        Step current = queue.top();
        queue.pop();
        
        int i = get<0>(current);
        
        if (i >= 0 && i < n - 1) {
            if (check_history(current)) {
                next_step(current, pomV);
                for (auto e : pomV) {
                    queue.emplace(e);
                }
            }
        }
        else if (i == n - 1) {
            cout << get<2>(current);
            return;
        }
    }
    cout << "-1";
}

int main() {
    
    cin >> n;
    cin >> K;
    cin >> U;
    
    for (int i = 0; i < n; ++i) {
        cin >> tor[i];
    }
    
    fill_pow();
    simulation();
}