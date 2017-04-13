#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define PII pair<int, int >

int N, M, pt, MAX, root, last, tot, num;
int dfn[400010], low[400010], sta[400010], vis[400010], mark[400010];
int st[400010], ne[800010], go[800010];
vector <PII > L;
set <PII > have_road;

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void tarjan (int x, int p) {
	dfn[x] = low[x] = ++tot;
	sta[++last] = x;
	vis[x] = 1;
	for (int i = st[x]; i; i = ne[i]){
		if (go[i] == p) continue;
		if (vis[go[i]] == 0) {
			tarjan (go[i], x);
			low[x] = min (low[x], low[go[i]]);
		} else if (vis[go[i]] == 1) low[x] = min (low[x], dfn[go[i]]);
	}
	if (dfn[x] == low[x]) {
		++num;
		int ss = 0;
		int p;
		do {
			++ss;
			p = sta[last];
			mark[p] = num;
			vis[p] = 2;
			sta[last--] = 0;
		} while (p != x);
		if (ss > MAX){
			MAX = ss;
			root = x;
		}
	}
}

void dfs(int x, int p){
	vis[x] = 1;
	for (int i = st[x]; i; i = ne[i]){
		int y = go[i];
		if (have_road.find(make_pair(x, y)) != have_road.end())
			continue;
		if (have_road.find(make_pair(y, x)) != have_road.end())
			continue;
		have_road.insert(make_pair(y, x));
		if (!vis[go[i]])
			dfs(go[i], x);
	}
}

int main(){
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
		L.push_back(make_pair(x, y));
	}
	tarjan(1, 0);
	memset(vis, 0, sizeof(vis));
	dfs(root, 0);
	printf("%d\n", MAX);
	for (int i = 0; i < M; i++)
		if (have_road.find(L[i]) != have_road.end())
			printf("%d %d\n", L[i].first, L[i].second);
		else
			printf("%d %d\n", L[i].second, L[i].first);
	return 0;
}