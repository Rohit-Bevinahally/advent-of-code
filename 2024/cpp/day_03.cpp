#include <bits/stdc++.h>
#include <regex>
using namespace std;
using ll = long long int;

ll calc(string s) {
    ll n1 = 0, n2 = 0;
    int i = 4;
    while(s[i] != ',') {
        n1 = n1 * 10 + (s[i] - '0');
        i++;
    }
    i++;
    while(s[i] != ')') {
        n2 = n2 * 10 + (s[i] - '0');
        i++;
    }
    return n1 * n2;
}
ll solve(string text) {
    std::regex pattern(R"(mul\(\d{1,3},\d{1,3}\))");
    auto mb = std::sregex_iterator(text.begin(), text.end(), pattern);
    auto me = std::sregex_iterator();

    ll ans = 0;
    map<int,string> matches;
    for (std::sregex_iterator i = mb; i != me; ++i) {
        std::smatch match = *i;
        cout << match.size() << '\n';
        string s = match.str();
        matches[match.position()] = s;
    }
    bool shouldDo = true;
    for(int i = 0; i < (int)text.size(); i++) {
        string s1 = text.substr(i, 4);
        string s2 = text.substr(i, 7);
        if(s1 == "do()") {
            shouldDo = true;
        }
        if(s2 == "don't()") {
            shouldDo = false;
        }
        if(matches.contains(i) && shouldDo) {
            ans += calc(matches[i]);
        }
    }
    return ans;
}
int main() {
    freopen("../input/part_1.txt", "r", stdin);
    string line;
    string text;
    while (getline(cin, line)) {
        stringstream ss(line);
        text += line;
    }
    cout << solve(text) << '\n';
}
