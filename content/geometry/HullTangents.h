/**
 * Author: David Qiao
 * Date: 2026-10-18
 * License: none
 * Description: Returns the two tangent points on the convex hull 
 * with respect to an external points. Requires hull[0] to be the leftmost point. 
 * Status: untested
 * Time: O(log N);
 */

#pragma once
#include "Point.h"

typedef Point<ll> P;
array<int, 2> hullTangents(vector<P> S, P p) {
    int n = sz(S), l=0, r=n-1;
    while(l < r) {
        int m = (l+r)/2;
        if(m < n-1 && S[m+1].x > S[m].x) l = m+1;
        else if(m > 0 && S[m-1].x > S[m].x) r = m-1;
        else l = r = m;
    }    // l is the rightmost node
    auto fin = [&](int l, int r, P p, bool ccw) -> int {
        while (l < r) {
            int m = (l+r)/2;
            auto &a = S[m], &b = S[m+1];
            if(((a-p).cross(b-p) > 0) == ccw) r = m;
            else l = m+1;
        }
        return l;
    };
    auto spl = [&](int l, int r, P p, bool inc) -> int {
        while(l < r) {
            int m = (l+r)/2;
            if((S[m].x < p.x) == inc) r = m;
            else l = m+1;
        }
        return l;
    };
    if(p.x < S[0].x) {
        return {fin(0, l, p, true), fin(l, S.size()-1, p, false)};
    }
    else if(p.x > S[l].x) {
        return {fin(0, l, p, false), fin(l, S.size()-1, p, true)};
    }
    else if((S[l] - S[0]).cross(p-S[0]) > 0) {
        int m = spl(l, S.size()-1, p, false);
        return {fin(l, m, p, false), fin(m+1, S.size()-1, p, true)};
    }
    else {
        int m = spl(0, l, p, true);
        return {fin(0, m, p, false), fin(m+1, l, p, true)};
    }
}