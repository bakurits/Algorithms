/*
 * Psychos in a Line
 * http://codeforces.com/problemset/problem/320/D
 *
 */

#include <iostream>
#include <stdio.h>
#include <vector>

const int N = 1e5 + 10;

using namespace std;

int n, a[N], pr[N], nx[N], ans;

vector <int> curr;
vector <int> newCurr;

void deleteCurrs() {
	newCurr.clear();
	for (int i = 0; i < curr.size();) {
		int j;
		for (j = i + 1; j < curr.size(); j++) {
			int curInd = curr[j];
			int prInd = curr[j - 1];
			if (pr[curInd] != prInd)
				break;
		}
		int curL = pr[curr[i]];
		int curR = nx[curr[j - 1]];

		nx[curL] = curR;
		pr[curR] = curL;

		if (a[curL] > a[curR])
			newCurr.push_back(curR);

		i = j;
	}

	curr.clear();
	for (int i = 0; i < newCurr.size(); i++)
		curr.push_back(newCurr[i]);
}

int main() {

	scanf ("%d", &n);

	for (int i = 0; i <= n + 1; i++) {
		if (i > 0 && i < n + 1) {
			scanf ("%d", &a[i]);
		}
		pr[i] = i - 1;
		nx[i] = i + 1;
	}
	a[0] = -n; a[n + 1] = n;

	for (int i = 1; i <= n; i++) {
		if (a[i] < a[i - 1]) {
			curr.push_back(i);
		}
	}

	while (curr.size() > 0) {
		ans++;
		deleteCurrs();
	}

	printf("%d\n", ans);
}
