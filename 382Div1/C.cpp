#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int pp = (1e9) + 7;
int N, K, pt;
int st[110], ne[220], go[220];
LL ans, g[24][24], dp[110][24][24];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void DP(int x, int p){
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != p)
			DP(go[i], x);
	dp[x][1][K + 1] = 1;
	dp[x][0][0] = 1;
	for (int i = st[x]; i; i = ne[i])
		if (go[i] != p){
			int y = go[i];
			memset(g, 0, sizeof(g));
			for (int a = 0; a <= K + 1; a++)
				for (int b = 0; b <= K + 1; b++)
					for (int c = 0; c <= K + 1; c++)
						for (int d = 0; d <= K + 1; d++){
							int xx = c;
							if (c != 0) xx++;
							xx = max(xx, a);
							int yy = d;
							if (d != K + 1) yy++;
							yy = min(yy, b);
							g[xx][yy] = (g[xx][yy] + dp[x][a][b] * dp[y][c][d] % pp) % pp;
						}
			for (int a = 0; a <= K + 1; a++)
				for (int b = 0; b <= K + 1; b++)
					dp[x][a][b] = g[a][b];
		}
	for (int a = 1; a <= K + 1; a++)
		for (int b = 0; b <= K + 1; b++)
			if (a - 1 + b <= K){
				dp[x][0][b] =(dp[x][0][b] + dp[x][a][b]) % pp;
				dp[x][a][b] = 0;
			}
}

int main(){
	scanf("%d%d", &N, &K);
	for (int i = 1; i < N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	DP(1, 0);
	ans = 0;
	for (int i = 0; i <= K + 1; i++)
		ans = (ans + dp[1][0][i]) % pp;
	cout << ans;
}