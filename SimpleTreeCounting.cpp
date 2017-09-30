/*
 * Black White Tree
 * https://www.hackerrank.com/contests/university-codesprint-3/challenges/black-white-tree
 *
 */

#include <iostream>
#include <vector>
#include <stdio.h>

const int N = 1.2 * 1e5 + 10;

using namespace std;

struct edge {
    int first;
    int second;
    int col;
};

int n, q;
edge edges[N];

long long sumForCol[N * 10], componentSum[N], cC[N];

vector <edge> g[N];

long long getSum(int v) {
    long long ans = 0;
    while (v > 0) {
        ans += sumForCol[v];
        v -= (v & -v);
    }
    return ans;
}

void updateSum(int v, long long val) {
    while (v < N * 10) {
        sumForCol[v] += val;
        v += (v & -v);
    }
}

void dfs(int v, int p, vector <int> &pat, int Col) {
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i].first;
        int curCol = edges[g[v][i].second].col;
        if (to != p && Col == curCol) {
            pat.push_back(g[v][i].second);
            dfs(to, v, pat, Col);
        }
    }
}

vector <int> fi, se;

void update(int edgeInd, int curCol) {
    int u = edges[edgeInd].first;
    int v = edges[edgeInd].second;
    int prevCol = edges[edgeInd].col;

    if (prevCol == curCol) return;

    fi.clear(); se.clear();

    dfs(u, v, fi, prevCol);
    dfs(v, u, se, prevCol);
    updateSum(prevCol, -componentSum[edgeInd]);
    updateSum(prevCol, (long long) fi.size() * (fi.size() + 1) / 2);
    updateSum(prevCol, (long long) se.size() * (se.size() + 1) / 2);

    for (int i = 0; i < fi.size(); i++) {
        componentSum[fi[i]] = (long long) fi.size() * (fi.size() + 1) / 2;
    }
    for (int i = 0; i < se.size(); i++) {
        componentSum[se[i]] = (long long) se.size() * (se.size() + 1) / 2;
    }

    fi.clear(); se.clear();
    dfs(u, v, fi, curCol);
    dfs(v, u, se, curCol);
    if (fi.size()) {
        updateSum(curCol, -componentSum[fi[0]]);
    }
    if (se.size()) {
        updateSum(curCol, -componentSum[se[0]]);
    }
    int newCcount = fi.size() + se.size() + 2;
    updateSum(curCol, (long long) newCcount * (newCcount - 1) / 2);

    for (int i = 0; i < fi.size(); i++) {
        componentSum[fi[i]] = (long long) newCcount * (newCcount - 1) / 2;
    }
    for (int i = 0; i < se.size(); i++) {
        componentSum[se[i]] = (long long) newCcount * (newCcount - 1) / 2;
    }
    componentSum[edgeInd] = (long long) newCcount * (newCcount - 1) / 2;

    edges[edgeInd].col = curCol;

}

int main() {
    //freopen("input.txt", "r", stdin);

    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        componentSum[i] = (long long) n * (n - 1) / 2;
    }
    updateSum(1, (long long) n * (n - 1) / 2);

    for (int i = 1; i < n; i++) {
        scanf ("%d %d %d", &edges[i].first, &edges[i].second, &edges[i].col);
        cC[i] = edges[i].col;
        edges[i].col = 1;
        edge curEdge = edges[i];
        curEdge.second = i;
        g[edges[i].second].push_back(curEdge);
        curEdge.first = edges[i].second;
        g[edges[i].first].push_back(curEdge);
    }
    for (int i = 1; i < n; i++) {
        update(i, cC[i]);
    }
    scanf ("%d", &q);
    while (q--) {
        int type;
        scanf ("%d", &type);

        if (type == 1) {
            int curEdge, curCol;
            scanf ("%d %d", &curEdge, &curCol);
            update(curEdge, curCol);
        } else if (type == 2) {
            int l, r;
            scanf ("%d %d", &l, &r);
            printf ("%lld\n", getSum(r) - getSum(l - 1));
        } else {
            int curEdge;
            scanf ("%d", &curEdge);
            printf ("%lld\n", componentSum[curEdge]);
        }
    }

}
