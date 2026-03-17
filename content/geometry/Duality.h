/**
 * Author: David Qiao
 * Date: 2026-03-17
 * License: none
 * Description: Point-line and point-plane duality primitives
 */

#include "Point.h"
#include "3dHull.h"

typedef Point3D<double>P3;
typedef Point<double> P;

// Lifting transform: (x, y) -> plane tangent to (x, y, x^2 + y^2). 
P3 lift(P p, double w = 0) { return P3(2*p.x, 2*p.y, w*w - p.x*p.x - p.y*p.y); }
P proj(P3 p) { return P(p.x/2, p.y/2); }

P3 fc2eqn(P3 p, P3 v) { return P3(-v.x/v.z, -v.y/v.z, v.dot(p)/v.z); }
P3 pt2Face(P3 p) { return P3(p.x, p.y, -p.z); }
P pt2Line(P p) { return P(p.x, -p.y); }
