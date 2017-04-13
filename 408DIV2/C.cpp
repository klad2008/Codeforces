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

int N, pt, sta, res, ans;
int A[300010];
int st[300010], ne[600010], go[600010];

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

int main(){
	scanf("%d", &N);
	sta = -2e9;
	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
		sta = max(sta, A[i] - 2);
	}
	for (int i = 1; i < N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	ans = 2e9;
	for (int i = 1; i <= N; i++){
		res = max(sta, A[i]);
		for (int j = st[i]; j; j = ne[j])
			res = max(sta, A[go[j]] - 1);
		ans = min(ans, res);
	}
	cout << ans;
}
