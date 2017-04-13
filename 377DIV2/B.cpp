#include <bits/stdc++.h>
using namespace std;

int N, K, ty;
int A[510], B[510];
int dp[510][510], pre[510][510];

void dfs(int x, int y){
	if (x > 1)
		dfs(x - 1, pre[x][y]);
	printf("%d ", max(B[x], y));
}

int main(){
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
		B[i] = A[i];
		A[i] = min(A[i], K);
	}
	memset(dp, 127, sizeof(dp));
	dp[1][A[1]] = 0;
	for (int i = 1; i < N; i++){
		for (int j = 1; j <= K; j++)
			if (dp[i][j] > dp[i][j - 1] + 1){
				dp[i][j] = dp[i][j - 1] + 1;
				pre[i][j] = pre[i][j - 1];
			}
		for (int j = 0; j <= K; j++)
			if (dp[i][j] < 1e9){
				int k = max(A[i + 1], K - j);
				int now = dp[i][j] + k - A[i + 1];
				if (dp[i + 1][k] > now){
					dp[i + 1][k] = now;
					pre[i + 1][k] = j;
				}
			}
	}
	ty = 0;
	for (int i = 1; i <= K; i++)
		if (dp[N][i] < dp[N][ty])
			ty = i;
	printf("%d\n", dp[N][ty]);
	dfs(N, ty);
	return 0;
}