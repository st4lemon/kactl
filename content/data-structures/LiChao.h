/**
 * Author: Ezra Furtado-Tiwari
 * Date: 2025-10-18
 * Source: folklore
 * Description: Add line with slope x, intercept y, in time range [l,r]
 * Query maximum line
 * Usage: Lichao(MAXN);
 * Time: $O(\log(N))$
 * Status: Tested on CSES
 */
#pragma once

struct LiChao {
    struct Line {
        ll a,b; // a*x+b
        ll get(ll x) { return a*x+b; }
    };
    ll n;
    static const ll INF = 1e18;
    vector<Line> t;
    vector<pair<ll, ll>> v;
    LiChao(ll _n) : n(_n), t(2*n, {0, -INF}), v(2*n) { build(); }
    void build() {
        for(ll i=0; i<n; i++) v[i+n] = {i,i+1};
        for(ll i=n-1; i>0; i--) v[i] = {v[2*i].first,v[2*i+1].second};
    }
    void add(Line l, ll L, ll R) {
        for (L+=n, R+=n; L<R; L/=2, R/=2) {
            if (L%2) add(l, L++);
            if (R%2) add(l, --R);
        }
    }
    void add(Line l, ll i) {
        if (i >= 2*n) return;
        auto [lo, hi] = v[i];
        ll m = (lo+hi)/2;
        if (t[i].get(m) < l.get(m)) swap(l, t[i]);
        if (t[i].a < l.a) {
            add(l, 2*i+1);
        } else {
            add(l, 2*i);
        }
    }
    ll q(ll x) {
        ll ans = -INF;
        for (ll i=x+n; i; i/=2) {
            ans = max(ans, t[i].get(x));
        }
        return ans;
    }
};
