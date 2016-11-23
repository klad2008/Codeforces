#include <bits/stdc++.h>
using namespace std;

#define LL long long 

int N, len, pt;
int f[400010], L[400010];
int st[400010], ne[400010], go[400010];
class rec{
	public:
	int l, r, x, w;
}P[200010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

int main(){
	freopen("2.in", "r", stdin);
	freopen("2.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		scanf("%d%d", &P[i].x, &P[i].w);
		P[i].l = P[i].x - P[i].w;
		P[i].r = P[i].x + P[i].w;
		L[++len] = P[i].l;
		L[++len] = P[i].r;
	}
	sort(L + 1, L + len + 1);
	len = unique(L + 1, L + len + 1) - L - 1;
	for (int i = 1; i <= N; i++){
		P[i].l = lower_bound(L + 1, L + len + 1, P[i].l) - L;
		P[i].r = lower_bound(L + 1, L + len + 1, P[i].r) - L;
		Add(P[i].r, i);
	}
	f[0] = 0;
	for (int i = 1; i <= len; i++){
		f[i] = f[i - 1];
		for (int j = st[i]; j; j = ne[j]){
			int y = go[j];
			f[i] = max(f[i], f[P[y].l] + 1);
		}
	}
	printf("%d\n", f[len]);
}
