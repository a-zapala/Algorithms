#include <iostream>
#include <climits>

using namespace std;

int main() {

    string napis;
    cin >> napis;

    int i;
    int currentLength;
    int minLength = INT_MAX;
    char currentCharacter;

    for (i = 0; i < napis.size(); ++i) {
        if (napis[i] != '*') {
            break;
        }
    }

    if (i == napis.size()) {
        cout << 1;
        return 0;
    }

    currentCharacter = napis[i];
    currentLength = 0;
    i++;

    for (; i < napis.size(); ++i) {
        if (napis[i] == '*') {
            currentLength++;
        }
        else {
            if (currentCharacter != napis[i]) {
                minLength = min(currentLength, minLength);
                currentCharacter = napis[i];
            }
            currentLength = 0;
        }
    }

    if ( minLength == INT_MAX) {
        cout << 1;
        return 0;
    }

    cout << napis.size() - minLength;

    return 0;
}