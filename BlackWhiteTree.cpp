/*
 * Black White Tree
 * https://www.hackerrank.com/contests/university-codesprint-3/challenges/black-white-tree
 *
 */

#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

const int N = 1e5 + 10;

using namespace std;

int n, ans, startV, ansCol;
int col[N], blackMax[N], whiteMax[N], P[N];
vector <int> g[N];

void solve(int v, int p = 0) {
    P[v] = p;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to != p) {
            solve(to, v);
            blackMax[v] += max(blackMax[to], 0);
            whiteMax[v] += max(whiteMax[to], 0);
        }
    }

    if (col[v]) {
        whiteMax[v]++;
        blackMax[v]--;
    } else {
        whiteMax[v]--;
        blackMax[v]++;
    }
    if (whiteMax[v] > ans) {
        ans = whiteMax[v];
        startV = v;
        ansCol = 1;
    }
    if (blackMax[v] > ans) {
        ans = blackMax[v];
        startV = v;
        ansCol = 0;
    }
}

vector <int> path;

void getPath(int v) {
    path.push_back(v);
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to != P[v]) {
            if (ansCol == 0 && blackMax[to] > 0)
                getPath(to);
            if (ansCol == 1 && whiteMax[to] > 0)
                getPath(to);
        }   
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &col[i]);
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    solve(1);
    getPath(startV);
    sort(path.begin(), path.end());

    printf("%d\n", ans);
    printf("%d\n", path.size());

    for (int i = 0; i < path.size(); i++) {
        printf("%d ", path[i]);
    }

}