#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, A, B, K;
int last, len, Remain;
int q[200010], head[200010], num[200010];
char s[200010];

vector <int > ans;

int main(){
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	scanf("%d%d%d%d", &N, &A, &B, &K);
	scanf("%s", s);
	last = 0;
	len = 0;
	Remain = 0;
	s[N] = '1';
	for (int i = 0; i <= N; i++)
		if (s[i] == '1'){
			if (i > last){
				++len;
				q[len] = i - last;
				head[len] = last;
				num[len] = q[len] / B;
				Remain += num[len];
			}
			last = i + 1;
		}
	ans.clear();
	for (int i = 1; i <= len && Remain >= A; i++){
		int x = head[i];
		for (int j = 1; j <= num[i] && Remain >= A; j++){
			ans.push_back(x + B - 1);
			x = x + B;
			Remain--;
		}
	}
	len = ans.size();
	printf("%d\n", len);
	for (int i = 0; i < len; i++){
		if (i) printf(" ");
		printf("%d", ans[i] + 1);
	}
	printf("\n");
}
