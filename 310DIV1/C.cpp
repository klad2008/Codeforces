#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define PII pair<int, int>

int N, Q, ans;

class rec{
	public:
	char c;
	int t;
}p;

map <int, rec> H;
map <int, rec> :: iterator tt;

int main(){
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= Q; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		char ch = getchar();
		while (ch != 'U' && ch != 'L')
			ch = getchar();
		if (H.find(x) != H.end()){
			printf("0\n");
			continue;
		}
		tt = H.lower_bound(x);
		if (ch == 'U' && tt == H.end()) ans = N + 1 - x;
		else if (ch == 'L' && tt == H.begin()) ans = x;
		else{
			if (ch == 'L') tt--;
			p = tt -> second;
			if (p.c == ch) ans = p.t + abs((tt -> first) - x);
			else ans = abs((tt -> first) - x);
		}
		printf("%d\n", ans);
		p.c = ch;
		p.t = ans;
		H[x] = p;
	}
}