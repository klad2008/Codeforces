#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, len;
char s[310];
bool used[310], HaveCir[310];
int q[310], go[310], Pre[310], Cir[310];

void Read(int &x){
	scanf("%s", s);
	if (s[0] == '?') x = -1;
	else{
		x = 0;
		int len = strlen(s);
		for (int i = 0;i < len; i++)
			x = x * 10 + s[i] - '0';
	}
}

int find(int head, int p, int c, bool ff){
	for (int j = head; j <= N; j++)
		if (p == Pre[j] && c == Cir[j] && (!used[j] || ff))
			return j;
	return 0;
}

bool work(){
	while (1){//将 0 X 连环
		bool flag = 1;
		for (int i = 1; i <= N; i++)
			if (Pre[i] == 0 && Cir[i] > 0 && !used[i]){
				flag = 0;
				len = 1;
				q[len] = i;
				used[i] = 1;
				int x = i + 1;
				while (len < Cir[i] && (x = find(x, 0, Cir[i], 0)))
					q[++len] = x, used[x] = 1;
				x = 1;
				while (len < Cir[i] && (x = find(x, -1, Cir[i], 0))){
					q[++len] = x;
					used[x] = 1;
					Pre[x] = 0;
				}
				x = 1;
				while (len < Cir[i] && (x = find(x, 0, -1, 0))){
					q[++len] = x;
					used[x] = 1;
					Cir[x] = Cir[i];
				}
				x = 1;
				while (len < Cir[i] && (x = find(x, -1, -1, 0))){
					q[++len] = x;
					used[x] = 1;
					Pre[x] = 0;
					Cir[x] = Cir[i];
				}
				if (len < Cir[i])
					return 0;
				for (int j = 1; j <= len; j++)
					go[q[j]] = q[j % len + 1];
				HaveCir[len] = 1;
			}
		if (flag)
			break;
	}
	while (1){//将 未出现的环长度 连环
		bool flag = 1;
		for (int i = 1; i <= N; i++)
			if (Cir[i] != -1 && !HaveCir[Cir[i]] && !used[i]){
				flag = 0;
				len = 0;
				if (Pre[i] == -1){
					q[++len] = i;
					used[i] = 1;
				}
				int x = 1;
				while (len < Cir[i] && (x = find(x, -1, Cir[i], 0))){
					q[++len] = x;
					used[x] = -1;
					Pre[x] = 0;
				}
				while (len < Cir[i] && (x = find(x, -1, -1, 0))){
					q[++len] = x;
					used[x] = -1;
					Pre[x] = 0;
					Cir[x] = Cir[i];
				}
				if (len < Cir[i])
					return 0;
				for (int j = 1; j <= len; j++)
					go[q[j]] = q[j % len + 1];
				HaveCir[len] = 1;
			}
		if (flag)
			break;
	}
	while (1){//将 X Y 构造边
		bool flag = 1;
		for (int i = 1; i <= N; i++)
			if (!used[i] && Cir[i] != -1 && Pre[i] != -1){
				flag = 0;
				int x = find(1, Pre[i] - 1, Cir[i], 1);
				if (!x){
					x = find(1, Pre[i] - 1, -1, 1);
					if (x) Cir[x] = Cir[i];
				}
				if (!x){
					x = find(1, -1, Cir[i], 1);
					if (x) Pre[x] = Pre[i] - 1;
				}
				if (!x){
					x = find(1, -1, -1, 1);
					if (x){
						Cir[x] = Cir[i];
						Pre[x] = Pre[i] - 1;
					}
				}
				if (!x)
					return 0;
				go[i] = x;
				used[i] = 1;
			}
		if (flag)
			break;
	}
	while (1){//将 X -1 连边
		bool flag = 1;
		for (int i = 1; i <= N; i++)
			if (!used[i] && Pre[i] != -1){
				flag = 0;
				bool ff = 1;
				if (Pre[i] == 0){
					Cir[i] = 1;
					used[i] = 1;
					go[i] = i;
					continue;
				}
				for (int j = 1; j <= N; j++)
					if (used[j] && Pre[i] == Pre[j] + 1){
						go[i] = j;
						Cir[i] = Cir[j];
						used[i] = 1;
						ff = 0;
						break;
					}
				if (ff)
					return 0;
			}
		if (flag)
			break;
	}
	while (1){//将 -1 X 连边
		bool flag = 1;
		for (int i = 1; i <= N; i++)
			if (!used[i] && Cir[i] != -1){
				flag = 0;
				if (Cir[i] == 1){
					Pre[i] = 0;
					used[i] = 1;
					go[i] = i;
					continue;
				}
				bool ff = 1;
				for (int j = 1; j <= N; j++)
					if (used[j] && Cir[i] == Cir[j]){
						go[i] = j;
						Pre[i] = Pre[j] + 1;
						used[i] = 1;
						ff = 0;
						break;
					}
				if (ff)
					return 0;
			}
		if (flag)
			break;
	}
	for (int i = 1; i <= N; i++)//将 -1 -1 连自环
		if (!used[i] && Pre[i] == -1 && Cir[i] == -1){
			Pre[i] = 0;
			Cir[i] = 1;
			go[i] = i;
			used[i] = 1;
		}
	for (int i = 1; i <= N; i++)
		if (!used[i])
			return 0;
	return 1;
}

int main(){
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		Read(Pre[i]);
		Read(Cir[i]);
	}
	if (!work())
		printf("-1\n");
	else{
		for (int i = 1; i <= N; i++){
			printf("%d", go[i]);
			if (i < N) printf(" ");
			else printf("\n");
		}
	}
}
