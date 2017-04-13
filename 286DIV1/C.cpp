#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M, K, P;
int H[100010], A[100010];
class rec{
	public:
	LL t, n, s;
}p;

priority_queue <rec, vector <rec>, greater<rec> > Heap;

bool operator < (const rec &A, const rec &B){
	return A.t < B.t;
}

bool operator > (const rec &A, const rec &B){
	return A.t > B.t;
}


bool check(LL X){
	while (!Heap.empty())
		Heap.pop();
	for (int i = 1; i <= N; i++){
		p.t = X / A[i];
		p.n = i;
		p.s = 0;
		Heap.push(p);
	}
	LL remain = 0;
	for (int t = 1; t <= M; t++){
		for (int i = 1; i <= K; i++){
			p = Heap.top();
			Heap.pop();
			if (p.t < M){
				LL tt = X + (LL)p.s * P - (LL)A[p.n] * t;
				if (tt < 0) return 0;
				p.s++;
				p.t = (X + (LL)p.s * P) / A[p.n];
			}else remain++;
			Heap.push(p);
		}
	}
	for (int i = 1; i <= N; i++){
		p = Heap.top();
		Heap.pop();
		LL tt = X + (LL)p.s * P - (LL)A[p.n] * M;
		LL Need = (H[p.n] - tt + P - 1) / P;
		Need = max(Need, 0ll);
		tt += Need * P;
		remain -= Need;
	}
	return remain >= 0;
}

int main(){
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	scanf("%d%d%d%d", &N, &M, &K, &P);
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &H[i], &A[i]);
	LL l = 0, r = 1e15;
	while (l < r){
		LL mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l;
}