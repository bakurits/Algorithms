/*
 * Black White Tree
 * https://www.hackerrank.com/contests/university-codesprint-3/challenges/black-white-tree
 *
 */

#include <iostream>
#include <vector>
#include <stdio.h>

const int N = 1e5 + 10;

using namespace std;

struct edge {
    int first;
    int second;
    int col;
};

int n, q;
edge edges[N];

long long sumForCol[N * 10], componentSum[N];

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
    while (v < N) {
        sumForCol[v] += val;
        v += (v & -v);
    }
}

void update(int edgeInd, int curCol) {
    int u = edges[edgeInd].first;
    int v = edges[edgeInd].second;
    int prevCol = edges[edgeInd].col;

    if (prevCol == curCol) return;

    
}

int main() {
    scanf("%d %d", &n, &q);

    for (int i = 1; i < n; i++) {
        componentSum[i] = (long long) n * (n - 1) / 2; 
    }
    updateSum(1, n * (n - 1) / 2);

    for (int i = 0; i < n; i++) {
        scanf ("%d %d %d", &edges[i].first, &edges[i].second, &edges[i].col);
        edge curEdge = edges[i]; 
        curEdge.col = 1;
        curEdge.second = i;
        g[edges[i].second].push_back(curEdge);
        curEdge.first = edges[i].second;
        g[edges[i].first].push_back(curEdge);
    }

    for (int i = 1; i < n; i++) {
        update(i, edges[i].col);
    }

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