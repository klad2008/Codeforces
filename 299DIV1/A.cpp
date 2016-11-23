#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int maxn = 1e6;

LL A, B, N;

class rec{
	public:
	LL l, r, t, m, n;
}Q[1000010];

bool cmpl(const rec &A, const rec &B){
	return A.l < B.l;
}

bool cmpt(const rec &A, const rec &B){
	return A.t > B.t;
}

bool cmpn(const rec &A, const rec &B){
	return A.n < B.n;
}

LL S[1000010], a[1000010];

int find(int l, int r, LL data){
	while (l < r){
		int mid = (l + r + 1) >> 1;
		if (S[mid] > data)r = mid - 1;
		else l = mid;
	}
	return l;
}

void work1(){
	sort(Q + 1, Q + N + 1, cmpl);
	int j = 1;
	for (int i = 1; i <= maxn; i++)
		for (; j <= N && Q[j].l == i; j++){
			int t = find(i, maxn, S[i - 1] + Q[j].m * Q[j].t);
			Q[j].r = t;
		}
}

void work2(){
	sort(Q + 1, Q + N + 1, cmpt);
	int j = 1;
	for (int i = maxn; i; i--){
		for (; j <= N && Q[j].t >= a[i]; j++)
			Q[j].r = min(Q[j].r, (LL) i);
	}
	for (; j <= N; j++)
		Q[j].r = 0;
}

int main(){
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	scanf("%I64d%I64d%I64d", &A, &B, &N);
	for (int i = 1; i <= N; i++){
		scanf("%I64d%I64d%I64d", &Q[i].l, &Q[i].t, &Q[i].m);
		Q[i].n = i;
	}
	a[1] = A;
	S[1] = a[1];
	for (int i = 2; i <= maxn; i++){
		a[i] = a[i - 1] + B;
		S[i] = S[i - 1] + a[i];
	}
	work1();
	work2();
	sort(Q + 1, Q + N + 1, cmpn);
	for (int i = 1; i <= N; i++)
		if (Q[i].l <= Q[i].r)
			printf("%I64d\n", Q[i].r);
		else printf("-1\n");
}