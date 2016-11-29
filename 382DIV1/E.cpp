#include <bits/stdc++.h>
using namespace std;

int N, M, len, REMAIN;
int q[3010], s[3010];
char ans[3010][3010];
class rec{
	public:
	int A, B, t;
}P[3010];

bool cmpv(const int &x, const int &y){
	return x > y;
}

bool cmpBA(const int &x, const int &y){
	return (P[x].B - P[x].A) > (P[y].B - P[y].A);
}

bool cmpA(const rec &A, const rec &B){
	return A.A > B.A;
}

bool cmpt(const rec &A, const rec &B){
	return A.t < B.t;
}

int main(){
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	scanf("%d%d", &N, &M);
	REMAIN = 2 * (N - 1) * N / 2;
	for (int i = 1; i <= M; i++){
		scanf("%d", &P[i].A);
		REMAIN -= P[i].A;
	}
	sort(P + 1, P + M + 1, cmpA);
	if (M < N){
		int tt = REMAIN / (N - M);
		for (int i = M + 1; i <= N; i++)
			P[i].A= tt;
		REMAIN -= tt * (N - M);
		for (int i = M + 1; REMAIN && i <= N; i++){
			REMAIN--;
			P[i].A++;
		}
		if (REMAIN){
			printf("no\n");
			return 0;
		}
	}
	for (int i = 1; i <= N; i++){
		P[i].B = N - 1;
		P[i].t = i;
	}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (i != j)	ans[i][j] = 'D';
			else ans[i][j] = 'X';
	for (int i = 1; i <= N; i++){
		len = 0;
		for (int j = i + 1; j <= N; j++)
			q[++len] = j;
		sort(q + 1, q + len + 1, cmpBA);
		int j = 1;
		while (j <= len && P[i].A > P[i].B){
			P[i].B++;
			P[q[j]].B--;
			int x = P[i].t;	
			int y = P[q[j]].t;
			ans[x][y] = 'W';
			ans[y][x] = 'L';
			j++;
		}
		if (P[i].A != P[i].B){
			printf("no\n");
			return 0;
		}
	}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (ans[i][j] == 'W')
				s[i] += 2;
			else if (ans[i][j] == 'D')
				s[i]++;
	sort(s + 1, s + N + 1, cmpv);
	sort(P + 1, P + N + 1, cmpt);
	for (int i = 1; i <= M; i++)
		if (P[i].A != s[i]){
			printf("no\n");
			return 0;
		}
	printf("yes\n");
	for (int i = 1; i <= N; i++)
		printf("%s\n", ans[i] + 1);
}