#include <bits/stdc++.h>

using namespace std;

#define LL long long

int N, len, x;

class rec{
	public:
	int sx, sy, tx, ty;
}q[10];

int ask(int sx, int sy, int tx, int ty){
	printf("? %d %d %d %d\n", sx, sy, tx, ty);
	fflush(stdout);
	scanf("%d", &x);
	if (len){
		if (q[1].sx >= sx && q[1].tx <= tx && q[1].sy >= sy && q[1].ty <= ty)
			x--;
	}
	return x;
}

void work1(int sx, int sy, int tx, int ty){
	int l, r;
	l = sx, r = tx;
	while (l < r){
		int mid = (l + r + 1) >> 1;
		if (ask(mid, sy, tx, ty)) l = mid;
		else r = mid - 1;
	}
	sx = l;
	
	l = sx, r = tx;
	while (l < r){
		int mid = (l + r) >> 1;
		if (ask(sx, sy, mid, ty)) r = mid;
		else l = mid + 1;
	}
	tx = l;
	
	l = sy, r = ty;
	while (l < r){
		int mid = (l + r + 1) >> 1;
		if (ask(sx, mid, tx, ty)) l = mid;
		else r = mid - 1;
	}
	sy = l;
	
	l = sy, r = ty;
	while (l < r){
		int mid = (l + r) >> 1;
		if (ask(sx, sy, tx, mid)) r = mid;
		else l = mid + 1;
	}
	ty = l;
	++len;
	q[len].sx = sx;
	q[len].tx = tx;
	q[len].sy = sy;
	q[len].ty = ty;
}

void work2(int sx, int sy, int tx, int ty){
	int midx = (sx + tx) >> 1;
	int midy = (sy + ty) >> 1;
	if (sx != tx){
		printf("? %d %d %d %d\n", sx, sy, midx, ty);
		fflush(stdout);
		scanf("%d", &x);
		if (x == 2){
			work2(sx, sy, midx, ty);
			return;
		}
		if (x == 1){
			work1(sx, sy, midx, ty);
			work1(sx, sy, tx, ty);
			return;
		}
		printf("? %d %d %d %d\n", midx + 1, sy, tx, ty);
		fflush(stdout);
		scanf("%d", &x);
		if (x == 2){
			work2(midx + 1, sy, tx, ty);
			return;
		}
		if (x == 1){
			work1(midx + 1, sy, tx, ty);
			work1(sx, sy, tx, ty);
			return;
		}
	}
		if (sy != ty){
		printf("? %d %d %d %d\n", sx, sy, tx, midy);
		fflush(stdout);
		scanf("%d", &x);
		if (x == 2){
			work2(sx, sy, tx, midy);
			return;
		}
		if (x == 1){
			work1(sx, sy, tx, midy);
			work1(sx, sy, tx, ty);
			return;
		}
		printf("? %d %d %d %d\n", sx, midy + 1, tx, ty);
		fflush(stdout);
		scanf("%d", &x);
		if (x == 2){
			work2(sx, midy + 1, tx, ty);
			return;
		}
		if (x == 1){
			work1(sx, midy + 1, tx, ty);
			work1(sx, sy, tx, ty);
			return;
		}
	}
}

int main(){
	scanf("%d", &N);
	work2(1, 1, N, N);
	printf("!");
	for (int i = 1; i <= len; i++)
		printf(" %d %d %d %d", q[i].sx, q[i].sy, q[i].tx, q[i].ty);
	printf("\n");
//	fflush(stdout);
}
