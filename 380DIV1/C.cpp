#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, S, ans, res, Remain;
int A[200010], num[200010];

int main(){
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	scanf("%d%d", &N, &S);
	ans = 2e9;
	res = 0;
	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
		if (i == S && A[i]){
			A[i] = 0;
			res++;
		}
		if (i != S && !A[i])
			A[i] = N;
	}
	sort(A + 1, A + N + 1);
	Remain = 0;
	for (int i = 1; i <= N; i++){
		num[A[i]]++;
		Remain++;
	}
	int r = N;
	for (int i = 0; i < N && Remain; i++){
		if (!num[i]){
			while (!num[r])
				r--;
			num[r]--;
			res++;
			num[i]++;
		}
		Remain -= num[i];
		ans = min(ans, res + Remain);
	}
	cout << ans<< endl;
}
