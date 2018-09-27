//https://szkopul.edu.pl/problemset/problem/oNnWY6ZuzzhvG-jCmijiXkIk/site/?key=statement


#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int sq = 316;

struct Query {
    int start;
    int d;
    int jupmCount;
};

int n, k;
int ans[N];

void getAnswerForFixedD(vector <Query> queries, int d) {

    int vec[d][n / d + 3];
    for (int i = 0; i < d; i++) {
        int initialSum = 0;
        for (int j = 0; j < n / d + 3; j++) {
            vec[i][j] = 0;
        }
    }
    for (int i = 0; i < queries.size(); i++) {
        Query q = queries[i];
        vec[q.start % d][q.start / d]++;
        vec[q.start % d][q.start / d + q.jupmCount]--;
    }

    for (int i = 0; i < d; i++) {
        int initialSum = 0;
        for (int j = 0; j < n / d + 3; j++) {
            initialSum += vec[i][j];
            ans[j * d + i] += initialSum;
        }
    }

}


void solveForBig(vector <Query> queries) {
    for (int i = 0; i < queries.size(); i++) {
        Query q = queries[i];
        for (int j = 0; j < q.jupmCount; j++) {
            ans[q.start + j * q.d]++;
        }
    }
}

void solveForSmall(vector <Query> queries) {
    vector <Query> queriesForD[sq + 1];
    for (int i = 0; i < queries.size(); i++) {
        Query q = queries[i];
        queriesForD[q.d].push_back(q);
    }

    for (int i = 1; i <= sq; i++) {
        if (queriesForD[i].size() > 0) {
            getAnswerForFixedD(queriesForD[i], i);
        }
    }
}


void print() {
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}
int main() {

    cin >> n >> k;

    vector <Query> queriesForSmallD;
    vector <Query> queriesForBigD;

    for (int i = 1; i <= k; i++) {
        Query qq;
        cin >> qq.start >> qq.jupmCount >> qq.d;
        if (qq.d <= sq) {
            queriesForSmallD.push_back(qq);
        } else {
            queriesForBigD.push_back(qq);
        }
    }


    solveForBig(queriesForBigD);
    
    solveForSmall(queriesForSmallD);

    print();
}