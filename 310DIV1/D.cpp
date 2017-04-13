#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define PII pair<int, int>

int N, M;
int P[200010], Pc[200010];
map <int, int> Hash;

int main(){
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++){
		scanf("%d", &P[i]);
		Hash[P[i]] = i;
	}
	memcpy(Pc, P, sizeof(Pc));
	sort(P + 1, P + N + 1);
	for (int i = 1; i <= M; i++){
		int x, l;
		scanf("%d%d", &x, &l);
		int dir = 1;
		int y = Pc[x] + dir * l;
		int k = upper_bound(P + 1, P + N + 1, y) - P - 1;
		x = k;
		l = y - P[k];
		dir = -1;
		while (1){
			y = P[x] + dir * l;
			if (dir == 1)
				k = upper_bound(P + 1, P + N + 1, y) - P - 1;
			else k = lower_bound(P + 1, P + N + 1, y) - P;
			if (x == k)
				break;
			int dis = abs(P[x] - P[k]);
			int tim = l / dis;
			l = l - dis * tim;
			if (tim & 1){
				x = k;
				dir = -dir;
			}
		}
		printf("%d\n", Hash[P[x]]);
	}
}