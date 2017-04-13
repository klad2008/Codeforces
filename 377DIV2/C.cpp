#include <bits/stdc++.h>
using namespace std;

#define LL long long

LL A[5], B[5];
LL ans, day;

int main(){
	for (int i = 0; i < 3; i++) scanf("%I64d", &B[i]);
	ans = 3e18;
	for (int t1 = 0; t1 <= 3; t1++)
		for (int t2 = 0; t2 <= 3; t2++){
			memcpy(A, B, sizeof(A));
			for (int i = 0; i < t1; i++)
				A[i]++;
			for (int i = t2; i < 3; i++)
				A[i]++;
			day = max(A[0], max(A[1], A[2]));
			ans = min(ans, day * 3 - A[0] - A[1] - A[2]);
		}
	printf("%I64d\n", ans);
	return 0;
}