#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, A, B;
double ans, res;
double T1[2010][2010], T2[2010][2010];
priority_queue <double, vector<double>, greater<double > > Heap;
class rec{
	public:
	double p, u;
} P[2010];

bool cmpu(const rec &A, const rec &B){
	return A.u > B.u || (A.u == B.u && A.p < B.p);
}

bool cmpp(const rec &A, const rec &B){
	return A.p > B.p || (A.p == B.p && A.u < B.u);
}

bool cmpup(const rec &A, const rec &B){
	return (1 - A.p) * A.u > (1 - B.p) * B.u;
}

int main(){
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	scanf("%d%d%d", &N, &A, &B);
	for (int i = 1; i <= N; i++) scanf("%lf", &P[i].p);
	for (int i = 1; i <= N; i++) scanf("%lf", &P[i].u);
	if (!A){
		sort(P + 1, P + N + 1, cmpu);
		for (int i = 1; i <= B; i++)
			ans += P[i].u;
		printf("%.6lf\n", ans);
		return 0;
	}
	if (!B){
		sort(P + 1, P + N + 1, cmpp);
		for (int i = 1; i <= A; i++)
			ans += P[i].p;
		printf("%.6lf\n", ans);
		return 0;
	}
	sort(P + 1, P + N + 1, cmpu);
	for (int i = B; i <= min(N, A + B); i++){
		sort(P + 1, P + i + 1, cmpup);
		while (!Heap.empty()) Heap.pop();
		res = 0;
		for (int j = i; j >= 1; j--){
			res += P[j].p - P[j].u;
			Heap.push(P[j].p - P[j].u);
			if (Heap.size() > i - B){
				res -= Heap.top();
				Heap.pop();
			}
			T1[j][i] = res;
		}
		T1[i + 1][i] = 0;
	}
	sort(P + 1, P + N + 1, cmpu);
	for (int i = B; i <= min(N, A + B); i++){
		sort(P + 1, P + i + 1, cmpup);
		while (!Heap.empty()) Heap.pop();
		res = 0;
		for (int j = i + 1; j <= N; j++){
			res += P[j].p;
			Heap.push(P[j].p);
			if (Heap.size() > A - (i - B)){
				res -= Heap.top();
				Heap.pop();
			}
		}
		for (int j = 1; j <= i; j++){
			T2[j][i] = res;
			res += (1 - P[j].u) * P[j].p;
			Heap.push((1 - P[j].u) * P[j].p);
			if (Heap.size() > A - (i - B)){
				res -= Heap.top();
				Heap.pop();
			}
		}
		T2[i + 1][i] = res;
	}
	sort(P + 1, P + N + 1, cmpu);
	for (int i = B; i <= min(N, A + B); i++){
		sort(P + 1, P + i + 1, cmpup);
		res = 0;
		for (int j = 1; j <= i; j++)
			res += P[j].u;
		for (int j = 1; j <= min(B + 1, i); j++){
			ans = max(ans, res + T1[j][i] + T2[j][i]);
//			res += P[j].p - P[j].u;
		}
		if (i == B){
			ans = max(ans, res + T2[i + 1][i]);
		}
	}
	printf("%.6lf\n", ans);
}
