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

int N, M, K, ans;
int A[110];

int main(){
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	ans = 10000;
	for (int i = 1; i <= N; i++)
		if (A[i] <= K && A[i] > 0)
			ans = min(ans, abs(i - M));
	printf("%d\n", ans * 10);
}
