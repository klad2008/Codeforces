#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M, Q, tot;
int du[100010], A[100010];
vector <int> VC[100010];
unordered_map <int, int> Hash[100010], ans[100010];
int f[200010], ran[200010];

int findset(int x){
	if (f[x] == x) return x;
	return f[x] = findset(f[x]);
}

void merge(int x, int y){
	x = findset(x);
	y = findset(y);
	if (ran[x] > ran[y])
		swap(x, y);
	f[x] = y;
	if (ran[x] == ran[y])
		ran[y]++;
}

int main(){
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++){
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		if (Hash[x].find(c) == Hash[x].end()){
			Hash[x][c] = ++tot;
			f[tot] = tot;
			ran[tot] = 1;
			VC[x].push_back(c);
			du[x]++;
		}
		if (Hash[y].find(c) == Hash[y].end()){
			Hash[y][c] = ++tot;
			f[tot] = tot;
			ran[tot] = 1;
			VC[y].push_back(c);
			du[y]++;
		}
		merge(Hash[x][c], Hash[y][c]);
	}
	int step = 0;
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		if (du[x] > du[y]) swap(x, y);
		if (ans[x].find(y) != ans[x].end()){
			printf("%d\n", ans[x][y]);
			continue;
		}
		int res = 0;
		for (auto c : VC[x]){
			++step;
			int xx = 0, yy = 0;
			if (Hash[x].find(c) != Hash[x].end())
				xx = Hash[x][c];
				else continue;
			if (Hash[y].find(c) != Hash[y].end())
				yy = Hash[y][c];
				else continue;
			if (findset(xx) == findset(yy))
				res++;
		}
		ans[x][y] = res;
		printf("%d\n", res);
	}
	printf("\n");
}