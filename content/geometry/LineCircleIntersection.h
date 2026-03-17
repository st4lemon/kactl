/**
 * Author: Om
 * Date: 2026-03-17
 * Description:\\
\begin{minipage}{75mm}
Computes the intersection between a circle and a segment. Outputs {0, {-1,-1}} if no intersection exists. 
If there are two intersections, outputs the one in the direction of (s-e). 
\end{minipage}
 * Usage:
 * auto [y, inter] = inter(c, r, s, e);
 * if(!y) cout << "No intersection";
 */

#pragma once

#include "Point.h"
#include "OnSegment.h"

typedef double T;
typedef Point<T> P;
pair<bool, P> inter(P c, T r, P s, P e) {
    P v1 = (e-s).unit(), v2 = c-s;
    T d = v1.dot(v2);
    T h = sqrt(v2.dist2()-d*d);
    if (h >= r) return {0,P(-1,-1)};
    T ch = sqrt(r*r-h*h);
    P it = s+v1*(d-ch);
    if (!onSegment(s,e,it)) return {0,P(-1,-1)};
    return {1,it};
}