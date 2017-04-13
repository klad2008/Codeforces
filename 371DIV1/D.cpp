#include <bits/stdc++.h>

using namespace std;

#define LL long long

int N, M, Q;

int A[1010][1010];
int dp[1010][1010];
int ST[1010][1010][10][10];

int get_MAX(int sx, int sy, int tx, int ty){
	int t1 = log(tx - sx + 1) / log(2);
	int t2 = log(ty - sy + 1) / log(2);
	int res = ST[sx][sy][t1][t2];
	res = max(res, ST[tx - (1 << t1) + 1][sy][t1][t2]);
	res = max(res, ST[sx][ty - (1 << t2) + 1][t1][t2]);
	res = max(res, ST[tx - (1 << t1) + 1][ty - (1 << t2) + 1][t1][t2]);
	return res;
}

int main(){
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &A[i][j]);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (A[i][j]){
				dp[i][j] = dp[i - 1][j - 1];
				dp[i][j] = min(dp[i][j], dp[i - 1][j]);
				dp[i][j] = min(dp[i][j], dp[i][j - 1]);
				dp[i][j]++;
			}else dp[i][j] = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			ST[i][j][0][0] = dp[i][j];
	for (int t1 = 0; t1 <= 9; t1++)
		for (int t2 = 0; t2 <= 9; t2++){
			if (!t1 && !t2) continue;
			int dx = 1 << t1;
			int dy = 1 << t2;
			for (int i = 1; i + dx - 1 <= N; i++)
				for (int j = 1; j + dy - 1 <= M; j++)
					if (t1) ST[i][j][t1][t2] = max(ST[i][j][t1 - 1][t2], ST[i + (dx >> 1)][j][t1 - 1][t2]);
					else ST[i][j][t1][t2] = max(ST[i][j][t1][t2 - 1], ST[i][j + (dy >> 1)][t1][t2 - 1]);
		}
	scanf("%d", &Q);
	for (; Q--;){
		int sx, sy, tx, ty;
		scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
		int l = 0, r = min(tx - sx, ty - sy) + 1;
		while (l < r){
			int mid = (l + r + 1) >> 1;
			if (get_MAX(sx + mid - 1, sy + mid - 1, tx, ty) >= mid) l = mid;
			else r = mid - 1;
		}
		printf("%d\n", l);
	}
}
