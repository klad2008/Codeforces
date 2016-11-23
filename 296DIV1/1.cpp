#include <bits/stdc++.h>
using namespace std;

#define LL long long 

int N, M, Q;

class rec{
	public:
	char c;
	int x, res[2];
}q[200010];
char ss[110];

set <int > HH;
typedef set <int > :: iterator cp;

bool cmp(bool flag, char ch){
	return (flag && ch == 'H') || (!flag && ch == 'V');
}


void work(bool flag){
	HH.clear();
	HH.insert(0);
	if (flag)HH.insert(M);
	else HH.insert(N);
	for (int i = 1; i <= Q; i++)
		if (cmp(flag, q[i].c))
			HH.insert(q[i].x);
	for (cp t = HH.begin(); t != HH.end(); t++){
		cp tt = t;
		tt++;
		if (tt == HH.end())
			continue;
		q[Q].res[flag] = max(q[Q].res[flag], (*tt) - (*t));
	}
	for (int i = Q - 1; i > 0; i--){
		q[i].res[flag] = q[i + 1].res[flag];
		if (cmp(flag, q[i + 1].c)){
			cp t = HH.find(q[i + 1].x);
			cp tl = t;
			cp tr = t;
			tl--;
			tr++;
			q[i].res[flag] = max(q[i].res[flag], (*tr) - (*tl));
			HH.erase(q[i + 1].x);
		}
	}
}

int main(){
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 1; i <= Q; i++){
		int x;
		scanf("%s%d", ss, &x);
		q[i].c = ss[0];
		q[i].x = x;
	}
	work(0);
	work(1);
	for (int i = 1; i <= Q; i++)
		cout << (LL)q[i].res[0] * q[i].res[1] << endl;
}
