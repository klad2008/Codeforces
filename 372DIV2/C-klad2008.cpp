#include <bits/stdc++.h>
using namespace std;
#define LL long long

LL N, u, ans, t, tt;
int main(){
	scanf("%I64d", &N);
	u = 2;
	for (int k = 1; k <= N; k++){
		tt = sqrt(k);
		if (tt * tt == k)
			t = tt;
			else t = k;
		ans = t * t * k + 2 * t * t + t * t / k - u;
		printf("%I64d\n",ans);
		u = t;
	}
}