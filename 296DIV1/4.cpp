#include <bits/stdc++.h>
using namespace std;

#define LL long long 

LL P = 998244353;
LL G = 3;
int N, M, K, m, ans;
char s0[800010], s1[800010];
int pre[800010], suc[800010];
LL A[800010], B[800010], C[800010];
LL W[2][800010], rev[800010], res[800010];

LL quick (LL x, LL y) {
	LL s = 1, t = x;
	for (; y ; y >>= 1){
		if (y & 1)s = s * t % P;
		t = t * t % P;
	}
	return s;
}

void FFT (LL *a, int f) {
	for (int i = 0; i < m; i++)
		if (i < rev[i]) swap (a[i], a[rev[i]]);
	for (int i = 1; i < m; i <<= 1)
		for (int j = 0, t = m / (i << 1); j < m; j += i << 1)
			for (int k = 0, l = 0; k < i; k++, l += t) {
				LL x, y;
				x = W[f][l] * a[j + k + i] % P;
				y = a[j + k];
				a[j + k] = (y + x) % P;
				a[j + k + i] = (y - x + P) % P;
			}
	if (f)
		for (int i = 0, x = quick (m, P - 2); i < m; i++)
			a[i] = a[i] * x % P;
}

void work() {
	for (m = 1; m <= N; m <<= 1);
	m <<= 1;
	for (int i = 0; i < m; i++) {
		int x = i, y = 0;
		for (int k = 1; k < m; x >>= 1, k <<= 1) (y <<= 1) |= x & 1;
		rev[i] = y;
	}
	W[0][0] = W[1][0] = 1;
	LL x = quick (G, (P - 1) / m), y = quick (x, P - 2);
	for (int i = 1; i < m; i++) {
		W[0][i] = x * W[0][i - 1] % P;
		W[1][i] = y * W[1][i - 1] % P;
	}
}

void DOIT(){
	work();
	FFT (A, 0);
	FFT (B, 0);
	for (int i = 0; i < m; i++) C[i] = A[i] * B[i] % P;
//	FFT (A, 1);
//	FFT (B, 1);
	FFT (C, 1);
}

void work(char ch){
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));
	for (int i = 0; i < N; i++)
		A[i] = (s0[i] == ch);
	int p = -K - 1;
	for (int i = 0; i < N; i++){
		if (A[i])p = i;
		pre[i] = p;
	}
	p = N + K;
	for (int i = N - 1; i >= 0; i--){
		if (A[i])p = i;
		suc[i] = p;
	}
	for (int i = 0; i < N; i++)
		if (((i - pre[i]) <= K) || ((suc[i] - i) <= K))
			A[i] = 1;
	int tar = 0;
	for (int i = 0; i < M; i++){
		int t = (s1[i] == ch);
		B[M - i - 1] = t;
		tar += t;
	}
	DOIT();
	for (int i = M - 1; i < N; i++)
		if (C[i] == tar)
			res[i]++;
}
int main(){
	freopen("4.in", "r", stdin);
	freopen("4.out", "w", stdout);
	scanf("%d%d%d", &N, &M, &K);
	scanf("%s%s", s0, s1);
	work('A');
	work('C');
	work('G');
	work('T');
	ans = 0;
	for (int i = M - 1; i < N; i++)
		ans += (res[i] == 4);
	printf("%d\n", ans);
}
