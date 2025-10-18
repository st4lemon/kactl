/**
 * Author: pimenta on Codeforces
 * License: CC0
 * Source: https://codeforces.com/blog/entry/49812
 * Description: Suppose a multiset $\{(a_i, m_i)\}$ of pairs of elements and the number of occurrences they have is given, with $\sum_{i} a_i \cdot m_i = N$.
 * Performs 0-1 knapsack quickly. Set MAXK to be greater than the largest required sum.
 * Usage: vi a(k), m(k); 
 * Time: O(N\sqrt{N}/32)
 */
 
bitset<MAXK> dp;
dp[0] = 1;
rep(i,0,k) {
	for (int x = 0; (1<<x) <= m[i]; x++) {
		dp |= (dp << (a[i]*(1<<x)));
		m[i] -= (1<<x);
	}
	dp |= (dp << (a[i]*m[i]));
}
 
