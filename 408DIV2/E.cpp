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

int N, P, K, ans;
int f[2][5010][50];
bool A[5010], B[5010];

void MAX(int &a, int b){
	a = max(a, b);
}

void Read(bool a[]){
	int R;
	scanf("%d", &R);
	for (int i = 1; i <= R; i++){
		int x;
		scanf("%d", &x);
		a[x] = 1;
	}
}

int code(int a, int b){
	return a * K + b;
}

int main(){
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	scanf("%d%d%d", &N, &P, &K);
	P = min(P, ((N + K - 1) / K) * 2);
	Read(A);
	Read(B);
	ans = 0;
	memset(f, 128, sizeof(f));
	int now = 0, pre = 1;
	f[now][0][0] = 0;
	for (int i = 1; i <= N; i++){
		swap(now, pre);
		memset(f[now], 128, sizeof(f[now]));
		for (int j = 0; j <= P; j++)
			for (int a = 0; a < K; a++)
				for (int b = 0; b < K; b++)
					if (f[pre][code(j, a)][b] >= 0){
						if ((a > 0) || (b > 0))
							MAX(f[now][code(j, max(a - 1, 0))][max(b - 1, 0)], f[pre][code(j, a)][b] + ((a > 0 && A[i]) || (b > 0 && B[i])));
						MAX(f[now][code(j + 1, K - 1)][max(b - 1, 0)], f[pre][code(j, a)][b] + A[i]);
						MAX(f[now][code(j + 1, max(a - 1, 0))][K - 1], f[pre][code(j, a)][b] + B[i]);
						MAX(f[now][code(j + 2, K - 1)][K - 1], f[pre][code(j, a)][b] + (A[i] || B[i]));
						if (!a && !b)
							MAX(f[now][code(j, 0)][0], f[pre][code(j, 0)][0]);
					}
	}
	for (int j = 0; j <= P; j++)
		for (int a = 0; a < K; a++)
			for (int b = 0; b < K; b++)
				ans = max(ans, f[now][code(j, a)][b]);
	cout << ans << endl;
}
