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

int N, pt, res, ans;
int A[300010];
int st[300010], ne[600010], go[600010];
multiset <int > s;
multiset <int > :: iterator cp;

void Add(int x, int y){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
}

int main(){
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
		s.insert(A[i]);
	}
	for (int i = 1; i < N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		Add(x, y);
		Add(y, x);
	}
	ans = 2e9;
	for (int i = 1; i <= N; i++){
		res = A[i];
		s.erase(s.find(A[i]));
		for (int j = st[i]; j; j = ne[j]){
			int y = go[j];
			res = max(res, A[y] + 1);
			s.erase(s.find(A[y]));
		}
		cp = s.end();
		if (cp != s.begin()){
			cp--;
			res = max(res, (*cp) + 2);
		}
		s.insert(A[i]);
		for (int j = st[i]; j; j = ne[j]){
			int y = go[j];
			s.insert(A[y]);
		}
		ans = min(ans, res);
	}
	cout << ans << endl;
}
