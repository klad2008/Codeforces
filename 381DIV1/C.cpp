#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, M, ans;
LL A[300010], f[300010];

class segleaf{
	public:
	int L0, R0, L2, R2, L02, R20, len, ans;
}seg[3000010];

int lowbit(int x){
	return x & -x;
}

void Init(int x, int data){
	for (; x <= N; x += lowbit(x))
		f[x] += data;
}

LL calc(int x){
	LL res = 0;
	for (; x; x -= lowbit(x))
		res += f[x];
	return res;
}

void build(int x, int l, int r){
	if (l < r){
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build((x << 1) + 1, mid + 1, r);
	}
	seg[x].L0 = 0;
	seg[x].L2 = 0;
	seg[x].R0 = 0;
	seg[x].R2 = 0;
	seg[x].L02 = 0;
	seg[x].R20 = 0;
	seg[x].len = r - l + 1;
	seg[x].ans = 0;
}

segleaf operator + (const segleaf &A, const segleaf &B){
	segleaf C;
	C.L0 = (A.L0 < A.len) ? A.L0 : A.len + B.L0;
	C.L2 = (A.L2 < A.len) ? A.L2 : A.len + B.L2;
	C.R0 = (B.R0 < B.len) ? B.R0 : B.len + A.R0;
	C.R2 = (B.R2 < B.len) ? B.R2 : B.len + A.R2;
	C.L02 = A.L02;
	if (A.L0 == A.len){
		C.L02 = max(C.L02, A.len + B.L02);
		C.L02 = max(C.L02, A.len + B.L0);
		C.L02 = max(C.L02, A.len + B.L2);
	}
	if (A.L02 == A.len)
		C.L02 = max(C.L02, A.len + B.L2);
	C.R20 = B.R20;
	if (B.R2 == B.len){
		C.R20 = max(C.R20, B.len + A.R20);
		C.R20 = max(C.R20, B.len + A.R0);
		C.R20 = max(C.R20, B.len + A.R2);
	}
	if (B.R20 == B.len)
		C.R20 = max(C.R20, B.len + A.R0);
	C.ans = max(A.ans, B.ans);
	C.ans = max(C.ans, A.R0 + B.L2);
	C.ans = max(C.ans, A.R0 + B.L02);
	C.ans = max(C.ans, A.R20 + B.L2);
	C.len = A.len + B.len;
	return C;
}

void change(int x, int l, int r, int t, int data){
	if (l == r){
		seg[x].L0 = seg[x].R0 = (data == 0);
		seg[x].L2 = seg[x].R2 = (data == 2);
		seg[x].L02 = seg[x].R20 = (data != 1);
		seg[x].ans = (data != 1);
		return;
	}
	int mid = (l + r) >> 1;
	if (t <= mid) change(x << 1, l, mid, t, data);
	else change((x << 1) + 1, mid + 1, r, t, data);
	seg[x] = seg[x << 1] + seg[(x << 1) + 1];
}

void renew(int i){
	if (A[i + 1] > A[i])
		change(1, 1, N - 1, i, 0);
	if (A[i + 1] == A[i])
		change(1, 1, N - 1, i, 1);
	if (A[i + 1] < A[i])
		change(1, 1, N - 1, i, 2);
}

int main(){
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		int x;
		scanf("%d", &x);
		A[i] = x;
	}
	for (int i = 1; i <= N + 1; i++)
		Init(i, A[i] - A[i - 1]);
	build(1, 1, N - 1);
	for (int i = 1; i < N; i++)
		renew(i);
	scanf("%d", &M);
	for (int i = 1; i <= M; i++){
		int l, r, d;
		scanf("%d%d%d", &l, &r, &d);
		Init(l, d);
		Init(r + 1, -d);
		A[l] = calc(l);
		A[l - 1] = calc(l - 1);
		A[r] = calc(r);
		A[r + 1] = calc(r + 1);
		if (l > 1)
			renew(l - 1);
		if (r < N)
			renew(r);
		ans = seg[1].ans + 1;
		printf("%d\n", ans);
	}
}
