/**
 * Author: Om Mahesh
 * Date: 2025-09-04
 * Source: https://codeforces.com/blog/entry/91632
 * Description: Counts primes up till n in O(n^{3/4})
 * Time: n=10^11 $\approx$ 1 seconds, n=10^12 $\approx$ 5 seconds
 * Status: Tested
 */

ll count_primes(ll n) {
    vector<ll> v;
    for (ll i = 1; i <= n; i = n / (n / i) + 1) v.push_back(n / i);
    reverse(all(v));

    int sq = sqrt(n);
    auto geti = [&](ll x) { return x <= sq ? x - 1 : sz(v) - n / x; };

    vector<ll> dp = v;
    for (ll p = 2, a = 0; p <= sq; p++) {
        if (dp[geti(p)] == dp[geti(p - 1)]) continue;
        a++;
        double inv = 1.0 / p;
        for (int i = sz(v) - 1; i >= 0 && p * p <= v[i]; i--) {
            dp[i] -= dp[geti(v[i] * inv + 1e-9)] - a;
        }
    }

    return dp[geti(n)] - 1;
}