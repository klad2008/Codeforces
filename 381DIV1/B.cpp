#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, pt, len;
int ans[200010];
int A[200010], L1[200010], L2[200010];
int st[200010], ne[200010], go[200010], w[200010];
LL dep[200010], D[200010];
int dfn[200010], in[200010], out[200010];
int f[200010];

int lowbit(int x){
	return x & -x;
}

bool cmpA(const int &x, const int &y){
	return A[x] < A[y];
}

bool cmpdep(const int &x, const int &y){
	return dep[x] < dep[y];
}

bool cmpD(const int &x, const int &y){
	return D[x] < D[y];
}

void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

void Init(int x, int data){
	for (; x <= N; x += lowbit(x))
		f[x] += data;
}

int calc(int x){
	int res = 0;
	for (; x; x -= lowbit(x))
		res += f[x];
	return res;
}

void dfs(int x){
	dfn[++len] = x;
	in[x] = len;
	for (int i = st[x]; i; i = ne[i]){
		dep[go[i]] = dep[x] + w[i];
		dfs(go[i]);
	}
	out[x] = len;
}

int main(){
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	for (int i = 2; i <= N; i++){
		int x, w;
		scanf("%d%d", &x, &w);
		Add(x, i, w);
	}
	dfs(1);
	for (int i = 1; i <= N; i++)
		D[i] = dep[i] - A[i];
	for (int i = 1; i <= N; i++)
		L1[i] = L2[i] = i;
	sort(L1 + 1, L1 + N + 1, cmpdep);
	sort(L2 + 1, L2 + N + 1, cmpD);
	int j = 1;
	for (int i = 1; i <= N; i++){
		int x = L1[i];
		while (j <= N){
			int y = L2[j];
			if (D[y] <= dep[x]){
				Init(in[y], 1);
				j++;
			}
			else break;
		}
		if (in[x] < out[x])
			ans[x] = calc(out[x]) - calc(in[x]);
	}
	for (int i = 1; i <= N; i++){
		printf("%d", ans[i]);
		if (i < N)printf(" ");
		else printf("\n");
	}
}
