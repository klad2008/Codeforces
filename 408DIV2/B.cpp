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

int N, M, K, p;
bool flag;
bool H[1000010];

int main(){
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 1; i <= M; i++){
		int x;
		scanf("%d", &x);
		H[x] = 1;
	}
	p = 1;
	flag = 1;
	for (int i = 1; i <= K; i++){
		if (H[p]) flag = 0;
		int x, y;
		scanf("%d%d", &x, &y);
		if (flag){
			if (p == x) p = y;
			else if (p == y) p = x;
		}
	}
	printf("%d", p);
}
