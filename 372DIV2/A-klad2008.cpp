#include <bits/stdc++.h>
using namespace std;

int N, C;
int A[100010];

int main(){
	scanf("%d%d", &N, &C);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	int M = N;
	while (M > 1 && A[M] - A[M - 1] <= C)
		M--;
	printf("%d\n", N - M + 1);
}