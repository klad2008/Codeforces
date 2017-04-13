#include <set>
#include <map>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

#define LL long long

int N, K, D, l, r, ans, pt;
int dist[300010], q[600010];
bool used[600010];
int st[300010], ne[600010], go[600010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

int main(){
	scanf("%d%d%d", &N, &K, &D);
	for (int i = 1; i <= N; i++)
		dist[i] = 2e9;
	l = 1; r = 0; pt = 1;
	for (int i = 1; i <= K; i++){
		int x;
		scanf("%d", &x);
		dist[x] = 0;
		q[++r] = x;
	}
	for (int i = 1; i < N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	ans = 0;
	for (; l <= r; l++){
		int x = q[l];
		if (dist[x] == D) continue;
		for (int i = st[x]; i; i = ne[i])
			if (dist[go[i]] == 2e9){
				dist[go[i]] = dist[x] + 1;
				q[++r] = go[i];
				used[i] = 1;
				used[i ^ 1] = 1;
				ans++;
			}
	}
	printf("%d\n", N - 1 - ans);
	for (int i = 1; i < N; i++)
		if (!used[i << 1])
			printf("%d ", i);
}
