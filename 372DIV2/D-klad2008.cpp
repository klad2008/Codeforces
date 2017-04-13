#include <bits/stdc++.h>
using namespace std;
#define LL long long

int N, M, L, S, T, pt, l, r;
int q[1000010];
bool vis[1010];
int st[1010], ne[20010], go[20010], w[20010];
LL dist_S[1010], dist_T[1010];

class line{
	public:
	int x, y, w;
}P[10010];

void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

void spfa(LL *dist){
	for (;l <= r; l++){
		int x = q[l];
		vis[x] = 0;
		for (int i = st[x]; i; i = ne[i])
			if (dist[go[i]] > dist[x] + w[i]){
				dist[go[i]] = dist[x] + w[i];
				if (!vis[go[i]]){
					vis[go[i]] = 1;
					q[++r] = go[i];
				}
			}
	}
}

int main(){
	scanf("%d%d%d%d%d", &N, &M, &L, &S, &T);
	pt = 1;
	for (int i = 1; i <= M; i++){
		scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].w);
		if (P[i].w){
			Add(P[i].x, P[i].y, P[i].w);
			Add(P[i].y, P[i].x, P[i].w);
		}
	}
	memset(dist_S, 10, sizeof (dist_S));
	memset(dist_T, 10, sizeof (dist_T));
	dist_S[S] = dist_T[T] = 0;
	q[l = r = 0] = S;
	vis[S] = 1;
	spfa(dist_S);
	q[l = r = 0] = T;
	vis[T] = 1;
	spfa(dist_T);
	if (dist_S[T] < L){
		printf("NO\n");
		return 0;
	}
	bool flag = 1;
	if (dist_S[T] == L){
		for (int i = 1; i <= M; i++)
			if (!P[i].w)
				P[i].w = 1073741820;
		flag = 0;
	}
	for (int i = 1; i <= M; i++)
		if (!P[i].w){
			LL res1 = dist_S[P[i].x] + dist_T[P[i].y];
			LL res2 = dist_S[P[i].y] + dist_T[P[i].x];
			if (min(res1, res2) < L){
				P[i].w = L - min(res1, res2);
				for (int j = i + 1; j <= M; j++)
					if (!P[j].w)P[j].w = 1073741820;
				flag = 0;
				break;
			}else{
				P[i].w = 1;
				Add(P[i].x, P[i].y, P[i].w);
				Add(P[i].y, P[i].x, P[i].w);
				q[l = 0] = P[i].x;
				q[r = 1] = P[i].y;
				vis[P[i].x] = 1;
				vis[P[i].y] = 1;
				spfa(dist_S);
				q[l = 0] = P[i].x;
				q[r = 1] = P[i].y;
				vis[P[i].x] = 1;
				vis[P[i].y] = 1;
				spfa(dist_T);
			}
		}
	if (flag)printf("NO\n");
	else{
		printf("YES\n");
		for (int i = 1; i <= M; i++)
			printf("%d %d %d\n", P[i].x, P[i].y, P[i].w);
	}
}