#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy[] = {0, 1, -1, 1, -1, 0, 1, -1};

int part1(vector<string> &g) {
    int n = g.size(), m = g[0].size();
    auto valid = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] != 'X') continue;
            for(int d = 0; d < 8; d++) {
                string cur;
                int x = i, y = j;
                for(int k = 0; k < 4; k++) {
                    cur += g[x][y];
                    x += dx[d];
                    y += dy[d];
                    if(!valid(x, y)) break;
                }
                if(cur == "XMAS") {
                    cnt++;
                }
            }
        }
    }
    return cnt;
}

int part2(vector<string> &g) {
    int n = g.size(), m = g[0].size();
    auto valid = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] != 'A') continue;
            string left, right;
            if(valid(i-1, j-1)) left += g[i-1][j-1];
            if(valid(i+1, j+1)) left += g[i+1][j+1];
            if(valid(i-1, j+1)) right += g[i-1][j+1];
            if(valid(i+1, j-1)) right += g[i+1][j-1];
            sort(left.begin(), left.end());
            sort(right.begin(), right.end());
            if(left == "MS" && right == "MS") {
                cnt++;
            }
        }
    }
    return cnt;
}
int main() {
    freopen("input.txt", "r", stdin);
    string line;
    vector<string> g;
    while (getline(cin, line)) {
        g.push_back(line);
    }
    cout << part1(g) << '\n';
    cout << part2(g) << '\n';
}
