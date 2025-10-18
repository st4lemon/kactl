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

typedef array<ll, 3> at;
struct LiChao {
	const int INF = 1e9 + 7;
	int n;
	vector<pii> t;
	LiChao (int _n) {
		n = _n;
		t = vector<pii> (2 * n, {-INF,-INF});
	}
	void add (int l, int r, int x, int y, int cl = 0, int cr = MAXN - 1, int p = 1) {
		if (cr < l || cl > r) {
			return;
		}
		int cm = (cl + cr)/2;
		if (l <= cl && cr <= r) {
			at pv = {cl,cm,cr};
			at cv = {cl,cm,cr};
			for (int i = 0; i < 3; i++) {
				pv[i] *= t[p].first, pv[i] += t[p].second;
				cv[i] *= x, cv[i] += y;
			}
			if (pv[0] <= cv[0] && pv[2] <= cv[2]) {
				t[p] = {x,y};
				return;
			} else if (pv[0] >= cv[0] && pv[2] >= cv[2]) {
				return;
			} else {
				add(l,r,x,y,cl,cm,p*2);
				add(l,r,x,y,cm+1,cr,p*2+1);
			}
			return;
		}
		add(l,r,x,y,cl,cm,p*2);
		add(l,r,x,y,cm+1,cr,p*2+1);
	}
	ll query (int x, int cl = 0, int cr = MAXN - 1, int p = 1) {
		ll cc = 0;
		if (t[p].first == -INF && t[p].second == -INF) {
			cc = -1ll * INF * INF;
		} else {
			cc = 1ll * t[p].first * x + t[p].second;
		}
		if (cl == cr) {
			return cc;
		}
		int cm = (cl + cr)/2;
		if (x <= cm) {
			return max(cc, query(x,cl,cm,p*2));
		} else {
			return max(cc, query(x,cm+1,cr,p*2+1));
		}
	} 
};
