#include <bits/stdc++.h>
using namespace std;

#define LL long long

LL F[100010];
LL N, ans;

int main(){
	F[0] = 1;
	F[1] = 2;
	N = 1;
	for (; F[N] < 1e18;){
		++N;
		F[N] = F[N - 1] + F[N - 2];
	}
	cin >> N;
	ans = 1;
	while (F[ans + 1] <= N)
		ans++;
	cout << ans;
}
