#include <bits/stdc++.h>
using namespace std;

#define LL long long

LL N, K, S, T, Max_D;
LL ans;
LL X, Y;
class rec{
	public:
	LL c, v;
}P[200010];

LL g[200010], D[200010];

bool cmpv(const rec &A, const rec &B){
	return A.v < B.v;
}

int main(){
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	scanf("%I64d%I64d%I64d%I64d", &N, &K, &S, &T);
	for (LL i = 1; i <= N; i++)
		scanf("%I64d%I64d", &P[i].c, &P[i].v);
	sort(P + 1, P + N + 1, cmpv);
	for (LL i = 1; i <= K; i++)
		scanf("%I64d", &g[i]);
	sort(g + 1, g + K + 1);
	g[K + 1] = S;
	Max_D = 0;
	for (LL i = 1; i <= K + 1; i++){
		D[i] = g[i] - g[i - 1];
		Max_D = max(Max_D, D[i]);
	}
	sort(D + 1, D + K + 2);
	LL x = 1;
	while (x <= N && P[x].v < Max_D) x++;
	X = 0;
	Y = 0;
	for (LL i = 1; i <= K + 1; i++){
		LL xx = D[i] * 2 - P[x].v;
		LL yy = P[x].v - D[i];
		if (xx < 0)
			xx = 0, yy = D[i];
		X += xx;Y += yy;
	}
	LL j = 1;
	while (j <= K + 1 && D[j] * 2 < P[x].v)
		j++;
	ans = 2e9;
	if (X * 2 + Y <= T)
		ans = min(ans, P[x].c);
	x++;
	while (x <= N){
		Y += (LL)(K - j + 2) * (P[x].v - P[x - 1].v);
		X -= (LL)(K - j + 2) * (P[x].v - P[x - 1].v)	;
		while (j <= K + 1 && D[j] * 2 < P[x].v){
			LL xx = D[j] * 2 - P[x].v;
			LL yy = P[x].v - D[j];
			X -= xx;Y -= yy;
			if (xx < 0)
				xx = 0, yy = D[j];
			X += xx;Y += yy;
			j++;
		}
		if (X * 2 + Y <= T)
			ans = min(ans, P[x].c);
		x++;
	}
	if (ans == 2e9) cout << -1 << endl;
	else cout << ans << endl;
}
