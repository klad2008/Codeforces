#include <bits/stdc++.h>
using namespace std;

#define LL long long

const int pp = (1e9) + 7;

int N, M, len;
LL res;
char s[1000010], ans[1000010];
int P[1000010];
bool used[1000010];
int fail[1000010];

void get_KMP(){
	fail[1] = 0;
	for (int i = 2; i <= len; i++){
		int x = fail[i - 1];
		for (; x && s[x + 1] != s[i]; x = fail[x]);
		if (s[x + 1] == s[i])fail[i] = x + 1;
		else fail[i] = 0;
	}
	int x = len;
	while (x){
		used[x] = 1;
		x = fail[x];
	}
	used[0] = 1;
}

int main(){
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	scanf("%d%d", &N, &M);
	scanf("%s", s + 1);
	len = strlen(s + 1);
	for (int i = 1; i <= M; i++){
		scanf("%d", &P[i]);
	}
	get_KMP();
	sort(P + 1, P + M + 1);
	int r = 0;
	for (int i = 1; i <= M; i++){
		int head = 0;
		if (P[i] <= r)head = r - P[i] + 1;
		else r = P[i] - 1;
		if (!used[head]){
			printf("0\n");
			return 0;
		}
		else head++;
		for (; head <= len; head++)
			ans[++r] = s[head];
	}
	res = 1;
	for (int i = 1; i <= N; i++)
		if (ans[i] == 0)
			res = res * 26 % pp;
	cout << res;
}