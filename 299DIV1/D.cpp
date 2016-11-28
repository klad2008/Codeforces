#include <bits/stdc++.h>
using namespace std;

#define LL long long

bool stt;

int N, M, S, T, pt, len;
int P[4010];
LL LS[4010];
LL W[4010][4010];
short SUM[4010][4010];
short prex[4010][4010], prey[4010][4010];
LL dp[4010][4010][2];
int st[4010], ne[200010], go[200010], w[200010];
int q[4000010];
LL dist[2][4010];
bool vis[4010];

bool enn;

void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

void spfa(int head, LL *dis){
	int l, r;
	for (int i = 1; i <= N; i++){
		dis[i] = 2e18;
		vis[i] = 0;
	}
	dis[head] = 0;
	vis[head] = 1;
	q[l = r = 0] = head;
	for (; l <= r; l++){
		int x = q[l];
		vis[x] = 0;
		for (int i = st[x]; i; i = ne[i])
			if (dis[go[i]] > dis[x] + w[i]){
				dis[go[i]] = dis[x] + w[i];
				if (!vis[go[i]]){
					vis[go[i]] = 1;
					q[++r] = go[i];
				}
			}
	}
}

int main(){
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
	scanf("%d%d", &N, &M);
	scanf("%d%d", &S, &T);
	for (int i = 1; i <= N; i++)
		scanf("%d", &P[i]);
	for (int i = 1; i <= M; i++){
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		Add(x, y, w);
		Add(y, x, w);
	}
	spfa(S, dist[0]);
	spfa(T, dist[1]);
	len = 0;
	for (int i = 1; i <= N; i++)
		LS[++len] = dist[0][i];
	for (int i = 1; i <= N; i++)
		LS[++len] = dist[1][i];
	sort(LS + 1, LS + len + 1);
	len = unique(LS + 1, LS + len + 1) - LS - 1;
	for (int i = 1; i <= N; i++){
		LL x = dist[0][i];
		x = lower_bound(LS + 1, LS + len + 1, x) - LS;
		LL y = dist[1][i];
		y = lower_bound(LS + 1, LS + len + 1, y) - LS;
		W[x][y] += P[i];
		SUM[x][y]++;
	}
	for (int i = len + 1; i >= 0; i--)
		for (int j = len + 1; j >= 0; j--){
			if (i < len + 1){
				W[i][j] += W[i + 1][j];
				SUM[i][j] += SUM[i + 1][j];
			}
			if (j < len + 1){
				W[i][j] += W[i][j + 1];
				SUM[i][j] += SUM[i][j + 1];
			}
			if (i < len + 1 && j < len + 1){
				W[i][j] -= W[i + 1][j + 1];
				SUM[i][j] -= SUM[i + 1][j + 1];
			}
		}
	memset(dp, 200, sizeof(dp));
	for (int x = len + 1; x; x--)
		for (int y = len + 1; y; y--){
			if (!SUM[x][y]){
				dp[x][y][0] = dp[x][y][1] = 0;
				prex[x][y] = x;
				prey[x][y] = y;
				continue;
			}
			int k;
			
			dp[x][y][0] = dp[x + 1][y][0] - W[x + 1][y] + W[x][y];
			k = prex[x + 1][y];
			for (; SUM[x][y] > SUM[k][y]; k--)
				dp[x][y][0] = max(dp[x][y][0], W[x][y] - dp[k][y][1]);
			prex[x][y] = k;
			
			dp[x][y][1] = dp[x][y + 1][1] - W[x][y + 1] + W[x][y];
			k = prey[x][y + 1];
			for (; SUM[x][y] > SUM[x][k]; k--)
				dp[x][y][1] = max(dp[x][y][1], W[x][y] - dp[x][k][0]);
			prey[x][y] = k;
		}
//	printf("%I64d\n", dp[1][1][0]);
	if (dp[1][1][0] > W[1][1] - dp[1][1][0])
		printf("Break a heart");
	else if (dp[1][1][0] < W[1][1] - dp[1][1][0])
		printf("Cry");
	else printf("Flowers");
}