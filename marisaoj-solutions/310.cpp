// ChatGPT

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<ll> A(n);
    for (int i = 0; i < n; ++i) cin >> A[i];

    ll answer = 0;
    vector<pair<ll,ll>> cur;     // (gcd_value, count_of_segments_ending_here_with_that_gcd)
    vector<pair<ll,ll>> nxt;
    cur.reserve(40);
    nxt.reserve(40);

    for (int i = 0; i < n; ++i) {
        nxt.clear();
        // new segment consisting of A[i] alone
        nxt.emplace_back(A[i], 1);

        for (auto &p : cur) {
            ll g = std::gcd(p.first, A[i]);
            if (nxt.back().first == g) {
                nxt.back().second += p.second;    // merge counts for same gcd
            } else {
                nxt.emplace_back(g, p.second);
            }
        }

        // add contributions from segments ending at i
        for (auto &p : nxt) {
            ll g = p.first % MOD;
            ll cnt = p.second % MOD;
            answer = (answer + g * cnt) % MOD;
        }

        cur.swap(nxt);
    }

    cout << answer % MOD << '\n';
    return 0;
}