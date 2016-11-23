#include <bits/stdc++.h>
using namespace std;

#define LL long long 

const double pi = acos(-1.0);

int N;
double ans;

class line{
	public:
	double a, b, c, selta;
	void read(){
		scanf("%lf%lf%lf", &a, &b, &c);
	}
	void get_selta(){
		selta = atan2(b, a);
		if (selta < -pi / 2)selta += pi;
		if (selta >= pi / 2)selta -= pi;
	}
	void rotate(double selta){
		double aa = a * cos(selta) - b * sin(selta);
		double bb = a * sin(selta) + b * cos(selta);
		a = aa;
		b = bb;
	}
}L[3010];

bool cmps(const line &A, const line &B){
	return A.selta < B.selta;
}

double getS(line A, line B){
	double Y = (A.a * B.c - A.c * B.a) / (A.b * B.a - B.b * A.a);
	double DX = A.c / A.a - B.c / B.a;
	return fabs(DX * Y) / 2;
}

int main(){
	freopen("5.in", "r", stdin);
	freopen("5.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		L[i].read();
		L[i].rotate(0.233);
		L[i].get_selta();
	}
	sort(L + 1, L + N + 1, cmps);
	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++){
			double S = getS(L[i], L[j]);
			int mid = j - i - 1;
			int out = N - mid - 2;
			ans += S * (out - mid);
		}
	ans = ans * 6 / N / (N - 1) / (N - 2);
	printf("%.6lf\n", ans);
}
