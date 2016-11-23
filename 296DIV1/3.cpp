#include <bits/stdc++.h>
using namespace std;

#define LL long long 

int N, M, pt, len;

int du[100010], q[100010];
bool used[800010];
int st[100010], ne[800010], go[800010];

class line{
	public:
	int x, y;
}L[800010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

void dfs(int x){
	while (st[x]){
		int y = st[x];
		st[x] = ne[y];
		if (used[y])continue;
		used[y] = used[y ^ 1] = 1;
		dfs(go[y]);
		++len;
		L[len].x = x;
		L[len].y = go[y];
	}
}

register char *_sp __asm__("rsp");
int main(){
	const int size=64*1024*1024;
	static char *sys, *mine(new char[size]+size-4096);
	sys=_sp;
	_sp=mine;
	
	freopen("3.in", "r", stdin);
	freopen("3.out", "w", stdout);
	scanf("%d%d", &N, &M);
	pt = 1;
	for (int i = 1; i <= M; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
		du[x]++;
		du[y]++;
	}
	for (int i = 1; i <= N; i++)
		if (du[i] & 1)
			q[++len] = i;
	for (int i = 1; i <= len; i += 2){
		Add(q[i], q[i + 1]);
		Add(q[i + 1], q[i]);
		du[q[i]]++;
		du[q[i + 1]]++;
		++M;
	}
	if (M & 1){
		Add(1, 1);
		Add(1, 1);
		du[1] += 2;
	}
	len = 0;
	dfs(1);
	printf("%d\n", len);
	for (int i = len; i >= 1; i--){
		if (i & 1)
			swap(L[i].x, L[i].y);
		printf("%d %d\n", L[i].x, L[i].y);
	}
	_sp=sys;
}
