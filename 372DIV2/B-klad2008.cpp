#include <bits/stdc++.h>
using namespace std;

int len;
int H[1010];
char s[50010];

int main(){
	scanf("%s", s + 1);
	len = strlen(s + 1);
	for (int i = 26; i <= len; i++){
		for (int j = 'A'; j <= 'Z'; j++)
			H[j] = 0;
		bool flag = 1;
		for (int j = i - 25; j <= i; j++)
			if (s[j] != '?'){
				if (H[s[j]]) flag = 0;
				else H[s[j]] = j;
			}
		if (!flag) continue;
		for (int j = i - 25; j <= i; j++)
			if (s[j] == '?')
				for (int k = 'A'; k <= 'Z'; k++)
					if (!H[k]){
						s[j] = k;
						H[k] = j;
						break;
					}
		for (int j = 1; j <= len; j++)
			if (s[j] == '?')
				s[j] = 'A';
		printf("%s", s + 1);
		return 0;
	}
	printf("-1\n");
	return 0;
}