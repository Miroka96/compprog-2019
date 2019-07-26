
#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);

    int n; cin >> n;
    auto cof = vector<vector<int>>(n, vector<int>(n));
    rep(i,n) rep(j,n) cin >> cof[i][j];
    if(n==1) {
        auto ans = 0;
        rep(i,n) ans += cof[i][0];
        cout << ans << endl;
        return 0;
    }

    /* idea: 
    - u have 2 paths that go from top left to bottom right
    - in each row path 1 is always stricly left of path 2, they never cross
    - dp[row][i][j] is the max value when both paths reach row and
        path i ends in column i and path 2 in column j (i<j)
    - we update dp row by row
    - for each row we compute dp[row][i][j] by case distinction
        depending on where each path switched from row-1 to the current row
    
    case 1: path 2 switched before j
    - result is same as path 2 ending one col earlier (dp[i][j-1]) and adding cell[row][j]
    - if j-1 becomes i, then this option is not available because luckily dp[i][i] will return 0

    case 2: path 2 switched from row-1 to row at column j
    - consider all columns 0<=k<=i where path 1 could switch 
    - result is max over all k of
        dp[row-1][k][j] + // all that both paths pick up until row-1
        cell[row][k..i] + // what path 1 picks up in current row
        cell[row][j] // what path 2 picks up in current row
    - if we fix j and go by increasing i, this term must consider only one new k at each step
    - namely consider path 1 switching at exactly column i 
    */

    auto prev = vector<vector<int>>(n, vector<int>(n));
    auto cur = vector<vector<int>>(n, vector<int>(n));
    rep(row,n) {
        swap(cur, prev);
        for (int j = 1; j < n; ++j) {
            auto bestK = 0; // best p1 switch if p2 switches at j
            for (int i = 0; i < j; ++i) {
                bestK = cof[row][i] + max(bestK, prev[i][j]); // switch p1 at i or before
                cur[i][j] = cof[row][j] + max(cur[i][j-1], bestK); // switch p2 at j or before
            }
        }
    }

    cout << cur[n-2][n-1] << endl;

    return 0;
}
