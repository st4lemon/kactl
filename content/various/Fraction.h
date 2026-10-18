/**
 * Author: David Qiao
 * Date: 2026-10-18
 * License: CC0
 * Source: myself
 * Description: Signed fraction class
 *  T must be a signed integer
 * Status: untested
 */

#pragma once

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Fraction {
    typedef Fraction F;
    T n, d;
    Fraction(T n, T d) : n(n), d(d) { reduce(); }
    Fraction(T x) : n(x), d(1) { }
    void reduce() { 
        ll g = gcd(n, d) * sgn(d);
        n /= g, d /= g;
    }
    F operator+(F f) const { return F(n*f.d + f.n*d, f.d*d); }
    F operator-(F f) const { return F(n*f.d - f.n*d, f.d*d); }
    F operator-() const { return F(-n, d); }
    F operator*(F f) const { return F(n*f.n, d*f.d); }
    F operator/(F f) const { return F(n*f.d, d*f.n); }
    F recp() const { return F(d, n); }
};