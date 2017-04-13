#include <bits/stdc++.h>

using namespace std;

#define LL long long

LL x;
int N;
char ch;
int num[300010];

int main(){
//	freopen("A.in", "r", stdin);
//	freopen("A.out", "w", stdout);
	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++){
		scanf("%c%I64d\n", &ch, &x);
		if (ch == '+' || ch == '-'){
			int t = 0;
			for (int j = 0; j < 18; j++){
				int y = x % 10;
				x = x / 10;
				y = y & 1;
				t = (t << 1) + y;
			}
			if (ch == '+')	num[t]++;
			else num[t]--;
		}else{
			int t = 0;
			for (int j = 0; j < 18; j++){
				int y = x % 10;
				x = x / 10;
				y = y & 1;
				t = (t << 1) + y;
			}
			printf("%d\n", num[t]);
		}
	}
}
