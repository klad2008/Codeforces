#include <bits/stdc++.h>
using namespace std;

int N, M, ans;

int a[100010];

class rec{
	public:
	int l, r;
}P[100010];

bool cmplr(const rec &A, const rec &B){
	return (A.l < B.l) || (A.l == B.l && A.r < B.r);
}

int main(){
	scanf("%d%d", &N, &M);
	ans = N;
	for (int i = 1; i <= M; i++){
		scanf("%d%d", &P[i].l, &P[i].r);
		ans = min(ans, P[i].r - P[i].l + 1);
	}
	printf("%d\n", ans);
	for (int i = 1; i <= N; i++){
		printf("%d", i % ans);
		if (i < N) printf(" ");
		else printf("\n");
	}
}
