#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M, tot, ansc, ansu;
bool vis[200010];
int A[200010], B[200010], tim[200010], To[200010];
vector <int> V[200010];
map <int, int > Hash;

int main(){
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
		if (Hash.find(A[i]) == Hash.end())
			Hash[A[i]] = ++tot;
		V[Hash[A[i]]].push_back(i);
	}
	for (int i = 1; i <= M; i++)
		scanf("%d", &B[i]);
	ansc = 0;
	ansu = 0;
	for (int t = 0; t < 32; t++){
		for (int i = 1; i <= M; i++){
			if (vis[i])
				continue;
			if (Hash.find(B[i]) == Hash.end())
				continue;
			int tt = Hash[B[i]];
			if (V[tt].empty())
				continue;
			
			int x = V[tt][V[tt].size() - 1];
			V[tt].pop_back();
			tim[i] = t;
			vis[i] = 1;
			To[x] = i;
			ansc++;
			ansu += t;
		}
		for (int i = 1; i <= M; i++)
			if (!vis[i])
				B[i] = (B[i] + 1) / 2;
	}
	printf("%d %d\n", ansc, ansu);
	for (int i = 1; i <= M; i++)
		printf("%d ", tim[i]);
	printf("\n");
	for (int i = 1; i <= N; i++)
		printf("%d ", To[i]);
	printf("\n");
	return 0;
}