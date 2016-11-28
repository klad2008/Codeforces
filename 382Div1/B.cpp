#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M, ans, delta;

const LL pp = 1000000007;
LL pri[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

LL gcd (LL x, LL y) {
	while (y) {
		LL t = x % y;
		x = y;
		y = t;
	}
	return x;
}

LL product_mod (LL x, LL y, LL n) {
	LL s = 0, t = x;
	for (; y; y >>= 1) {
		if (y & 1) s = (s + t) % n;
		t = t * 2 % n;
	}
	return s;
}

LL power_mod (LL x, LL y, LL n) {
	x %= n;
	LL s = 1, t = x;
	for (; y; y >>= 1) {
		if (y & 1) s = product_mod (s, t, n);
		t = product_mod (t, t, n);
	}
	return s;
}

bool Miller_Rabin (LL N) {
	if (N < 2) return false;
	if (N == 2) return true;
	if (! (N & 1) ) return false;
	LL m, k = 0, a;
	m = N - 1;
	while (! (m & 1) ) k++, m = m / 2;
	for (LL i = 0; i < 10; i++) {
		if (pri[i] >= N) break;
		a = power_mod (pri[i], m, N);
		if (a == 1) continue;
		LL j;
		for (j = 0; j < k; j++) {
			if (a == N - 1) break;
			a = product_mod (a, a, N);
		}
		if (j == k) return false;
	}
	return true;
}

int main(){
	cin >> N;
	if (Miller_Rabin(N))cout << 1;
	else if (!(N & 1))cout << 2;
	else if (Miller_Rabin(N - 2))cout << 2;
	else cout << 3;
}
