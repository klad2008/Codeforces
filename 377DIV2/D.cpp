#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M;
bool vis[100010];
int A[100010], D[100010];

bool check(int tail){
	memset(vis, 0, sizeof(vis));
	LL rest = 0;
	for (int i = tail; i > 0; i--)
		if (!vis[D[i]] && D[i]){
			rest += A[D[i]];
			vis[D[i]] = 1;
		}
		else if (rest > 0) rest--;
	for (int i = 1; i <= M; i++)
		if (!vis[i]) return 0;
	if (rest > 0) return 0;
	return 1;
}

int main(){
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &D[i]);
	for (int i = 1; i <= M; i++)
		scanf("%d", &A[i]);
	int l = 0, r = N + 1;
	while (l < r){
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	if (r == N + 1) printf("-1\n");
	else printf("%d\n", r);
	return 0;
}