/*
 * Black White Tree
 * https://www.hackerrank.com/contests/university-codesprint-3/challenges/black-white-tree
 *
 */

#include <iostream>
#include <vector>
#include <stdio.h>
#include <map>

const int N = 1.2 * 1e5 + 10;

using namespace std;

int n, q;
pair<int, int> edges[N], prec[N];

int colOfEdge[N];

long long sumForCol[N * 10], componentSum[N], cC[N];

vector < pair<int, int> > g[N];
map <int, int> subTreeCount[N];

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
        int curCol = colOfEdge[g[v][i].second];
        if (to != p && Col == curCol) {
            pat.push_back(g[v][i].second);
            dfs(to, v, pat, Col);
        }
    }
}

void updUp(int v, int col, int val) {
    while (colOfEdge[prec[v].second] == col) {
        subTreeCount[prec[v].first][col] += val;
        v = prec[v].first;
    }
}

int getChildCount(int curEdge, int col) {
    int u = edges[curEdge].first;
    int v = edges[curEdge].second;
    if (prec[v].first == u) swap(u, v);
    while (colOfEdge[prec[u].second] == col) {
        u = v;
        v = prec[v].first;
    }
    return subTreeCount[u][col];
}

void update(int edgeInd, int newCol) {
    int u = edges[edgeInd].first;
    int v = edges[edgeInd].second;
    if (prec[v].first == u) swap(u, v);

    int prevCol = colOfEdge[edgeInd];

    if (prevCol == newCol) return;

    long long oldCnt = getChildCount(edgeInd, prevCol) + 1;
    long long leftCnt = subTreeCount[u][prevCol] + 1;
    long long rightCnt = oldCnt - leftCnt;

    updateSum(prevCol, -(oldCnt * (oldCnt - 1) / 2));
    updateSum(prevCol, leftCnt * (leftCnt - 1) / 2);
    updateSum(prevCol, rightCnt * (rightCnt - 1) / 2);

    updUp(u, prevCol, -leftCnt);

    colOfEdge[edgeInd] = newCol;

    long long newRightCnt = getChildCount(edgeInd, newCol) + 1;
    long long newLeftCnt = subTreeCount[u][newCol] + 1;

    updateSum(newCol, -(newRightCnt * (newRightCnt - 1) / 2));
    updateSum(newCol, -(newLeftCnt * (newLeftCnt - 1) / 2));
    long long newCnt = newLeftCnt + newRightCnt;
    updateSum(newCol, (newCnt * (newCnt - 1) / 2));

    updUp(u, newCol, newLeftCnt);

}

void precalc(int v, int p) {
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i].first;
        if (to != p) {
            prec[to].first = v;
            prec[to].second = g[v][i].second;
            precalc(to, v);
            subTreeCount[v][colOfEdge[g[v][i].second]] +=
                subTreeCount[to][colOfEdge[g[v][i].second]] + 1;
        }
    }
}


int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        componentSum[i] = (long long) n * (n - 1) / 2;
    }
    updateSum(1, (long long) n * (n - 1) / 2);

    for (int i = 1; i < n; i++) {
        scanf ("%d %d %d", &edges[i].first, &edges[i].second, &colOfEdge[i]);
        cC[i] = colOfEdge[i];
        colOfEdge[i] = 1;
        pair<int, int> curEdge = edges[i];
        curEdge.second = i;
        g[edges[i].second].push_back(curEdge);
        curEdge.first = edges[i].second;
        g[edges[i].first].push_back(curEdge);
    }

    precalc(1, 0);

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
            long long cnt = getChildCount(curEdge, colOfEdge[curEdge]);
            printf ("%lld\n", cnt * (cnt + 1) / 2);
        }
    }
}
