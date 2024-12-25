#include <bits/stdc++.h>
using namespace std;

constexpr int N = 101;
int before[N][N]{};

bool valid(vector<int>& updates) {
    int n = updates.size();
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(before[updates[i]][updates[j]]) return false;
        }
    }
    return true;
}

void fix(vector<int>& updates) {
    int n = updates.size();
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(before[updates[i]][updates[j]]) {
                swap(updates[i], updates[j]);
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    string line;
    bool getRelations = true;
    int ans = 0, ans2 = 0;
    while(getline(cin,line)) {
        if(line.empty()) {
            getRelations = false;
            continue;
        }
        stringstream ss(line);
        if(getRelations) {
            int a, b;
            char _;
            ss >> a >> _ >> b;
            before[b][a] = 1;
        } else {
            vector<int> updates;
            string x;
            while(getline(ss, x, ',')) {
                updates.push_back(stoi(x));
            }
            int n = updates.size();
            if(valid(updates)) {
                ans += updates[n/2];
            } else {
                do { fix(updates); } while(!valid(updates));
                ans2 += updates[n/2];
            }
        }
    }
    cout << ans << '\n';
    cout << ans2 << '\n';
    return 0;
}
