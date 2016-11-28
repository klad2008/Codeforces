#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, r;
int b[200010];

class poi{
	public:
	int x, y, t;
	bool operator < (const poi &X)const{
		return x < X.x || (x == X.x && y < X.y);
	}
}P[200010];

set <poi> Hash;

bool cmpx(const poi &A, const poi &B){
	return A.x > B.x || (A.x == B.x && A.y > B.y);
}

int sgn(LL x){
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

int calc(int i, int j, int k){
	double xi = 1.0/P[i].x;
	double yi = 1.0/P[i].y;
	double xj = 1.0/P[j].x;
	double yj = 1.0/P[j].y;
	double xk = 1.0/P[k].x;
	double yk = 1.0/P[k].y;
	double tx = (xj - xi) * (yk - yi) - (xk - xi) * (yj - yi);
	LL res = (LL)(P[i].x * P[k].x - P[j].x * P[k].x) * (P[i].y * P[j].y - P[j].y * P[k].y);
	res -= (LL)(P[i].x * P[j].x - P[j].x * P[k].x) * (P[i].y * P[k].y - P[j].y * P[k].y);
	int tt = sgn(P[i].x * P[j].x * P[k].x) *sgn(P[i].y * P[j].y * P[k].y);
	return sgn(res) * tt;
}

bool better(int i, int j){
	if (P[i].x == P[j].x && P[i].y == P[j].y)
		return 0;
	if (P[i].x >= P[j].x && P[i].y >= P[j].y)
		return 1;
	return 0;
}

int main(){
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		scanf("%d%d", &P[i].x, &P[i].y);
		P[i].t = i;
	}
	sort(P + 1, P + N + 1, cmpx);
	b[r = 1] = 1;
	for (int i = 2; i <= N; i++){
		if (P[i].x == P[b[r]].x && P[i].y == P[b[r]].y)
			continue;
		while (r > 1 && calc(b[r - 1], b[r], i) < 0)
			b[r--] = 0;
		b[++r] = i;
	}
	while (r > 1 && better(b[r - 1], b[r]))
		b[r--] = 0;
	for (int i = 1; i <= r; i++)
		Hash.insert(P[b[i]]);
	r = 0;
	for (int i = 1; i <= N; i++)
		if (Hash.find(P[i]) != Hash.end())
			b[++r] = P[i].t;
	sort(b + 1, b + r + 1);
	for (int i = 1; i <= r; i++){
		printf("%d", b[i]);
//		if (i < N)
		printf(" ");
//		else printf("\n");
	}
}