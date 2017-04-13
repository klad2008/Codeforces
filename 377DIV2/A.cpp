#include <bits/stdc++.h>
using namespace std;

int K, R;

int main(){
	scanf("%d%d", &K, &R);
	for (int i = 1; i <= 10; i++)
		if (K * i % 10 == R || K * i % 10 == 0){
			printf("%d\n", i);
			break;
		}
	return 0;
}