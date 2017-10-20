#include <iostream>

using namespace std;

char a[200005];

int main() {
    int n; cin >> n;

    for (int i = 1; i < n; i++) {
        cin >> a[i];
    }
    a[n] = '-';

    for (int i = 1; i < n; i++) {
        if (a[i] == '-' && a[i - 1] == '+') cout << ")";
        cout << "-";
        if (a[i] == '-' && a[i + 1] == '+') cout << "(";
    }
    if (a[n] == '-' && a[n - 1] == '+') cout << ")";

}
