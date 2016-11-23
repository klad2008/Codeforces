#include <bits/stdc++.h>
using namespace std;

#define LL long long

int N, Q, pt, idx;
int F[100010];
int st[100010], ne[200010], go[200010], w[200010], fa[100010];
int TreeSize[100010], Depth[100010], HeavyChild[100010];
int Block[100010], NodeID[100010], IndexToNode[100010];
int BlockLeft[100010], BlockRight[100010];

class segleaf{
	public:
	int l, r, s, sum;
	void clr(){
		l = r = s = sum = 0;
	}
	void swp(){
		swap(l, r);
	}
	void calc_sum(){
		if (l == s && r == s)
			sum += F[s];
		else sum += F[l] + F[r];
		l = r = 0;
	}
}seg[1000010], resl, resr;

segleaf operator + (const segleaf &A, const segleaf &B){
	segleaf C;
	C.clr();
	C.s = A.s + B.s;
	C.sum = A.sum + B.sum;
	if (A.l == A.s && B.r == B.s){
		C.l = A.s + B.s;
		C.r = A.s + B.s;
	}else if (A.l < A.s && B.r == B.s){
		C.l = A.l;
		C.r = B.s + A.r;
	}else if (A.l == A.s && B.r < B.s){
		C.l = A.s + B.l;
		C.r = B.r;
	}else{
		C.l = A.l;
		C.r = B.r;
		C.sum += F[A.r + B.l];
	}
	return C;
}


class line{
	public:
	int x, y, w;
}L[100010];

class que{
	public:
	int x, y, l, ans, t;
}q[100010];

bool cmpl(const que &A, const que &B){
	return A.l < B.l;
}

bool cmpt(const que &A, const que &B){
	return A.t < B.t;
}

bool cmpw(const line &A, const line &B){
	return A.w < B.w;
}

void Add(int x, int y, int ww){
	ne[++pt] = st[x];
	st[x] = pt;
	go[pt] = y;
	w[pt] = ww;
}

void dfs_size (int x) {
	TreeSize[x] = 1;
	for (int i = st[x]; i; i = ne[i]) {
		int y = go[i];
		if (y == fa[x]) continue;
		fa[y] = x;
		Depth[y] = Depth[x] + 1;
		dfs_size (y);
		TreeSize[x] += TreeSize[y];
		if (TreeSize[HeavyChild[x]] < TreeSize[y])
			HeavyChild[x] = y;
	}
}

void dfs_lh (int x, int block) {
	Block[x] = block;
	NodeID[x] = ++idx;
	IndexToNode[idx] = x;
	if (!BlockLeft[block])
		BlockLeft[block] = idx;
	BlockRight[block] = idx;
	if (HeavyChild[x])
		dfs_lh (HeavyChild[x], block);
	for (int i = st[x]; i; i = ne[i]) {
		int y = go[i];
		if (y == fa[x] || y == HeavyChild[x])
			continue;
		dfs_lh (y, y);
	}
}

void Decomposition (int s, int N) {
	idx = 0;
	fa[s] = 0;
	memset (HeavyChild, 0, sizeof (HeavyChild) );
	dfs_size (s);
	dfs_lh (s, s);
}

void build(int x, int l, int r){
	if (l < r){
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build((x << 1) + 1, mid + 1, r);
		seg[x] = seg[x << 1] + seg[(x << 1) + 1];
	}else{
		seg[x].l = seg[x].r = 1;
		seg[x].sum = 0;
	}
	seg[x].s = r - l + 1;
}

void change(int x, int l, int r, int t){
	if (l == r){
		seg[x].l = seg[x].r = 0;
		seg[x].sum = 0;
		return;
	}
	int mid = (l + r) >> 1;
	if (t <= mid)change(x << 1, l, mid, t);
	else change((x << 1) + 1, mid + 1, r, t);
	seg[x] = seg[x << 1] + seg[(x << 1) + 1];
}

segleaf calc(int x, int l, int r, int ll, int rr){
	if (l == ll && r == rr)
		return seg[x];
	int mid = (l + r) >> 1;
	if (rr <= mid)return calc(x << 1, l, mid, ll, rr);
	else if (ll > mid)return calc((x << 1) + 1, mid + 1, r, ll, rr);
	else return calc(x << 1, l, mid, ll, mid) + calc((x << 1) + 1, mid + 1, r, mid + 1, rr);
}

int main(){
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	scanf("%d%d", &N, &Q);
	for (int i = 1; i < N; i++)
		scanf("%d", &F[i]);
	for (int i = 1; i < N; i++){
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		Add(x, y, w);
		Add(y, x, w);
		L[i].x = x;
		L[i].y = y;
		L[i].w = w;
	}
	Decomposition(1, N);
	build(1, 1, N);
	for (int i = 1; i <= Q; i++){
		scanf("%d%d%d", &q[i].x, &q[i].y, &q[i].l);
		q[i].t = i;
	}
	sort(L + 1, L + N, cmpw);
	sort(q + 1, q + Q + 1, cmpl);
	int j = 1;
	for (int i = 1; i <= Q; i++){
		for (; j < N && L[j].w < q[i].l; j++){
			int x = L[j].x;
			int y = L[j].y;
			if (Depth[x] < Depth[y])swap(x, y);
			int p = NodeID[x];
			change(1, 1, N, p);
		}
		int x = q[i].x;
		int y = q[i].y;
		resl.clr();
		resr.clr();
		while (Block[x] != Block[y]){
			if (Depth[Block[x]] < Depth[Block[y]]){
				swap(x, y);
				swap(resl, resr);
			}
			int b = Block[x];
			int p = NodeID[x];
			resl = calc(1, 1, N, BlockLeft[b], p) + resl;
			x = fa[Block[x]];
		}
		if (x != y){
			if (Depth[x] < Depth[y]){
				swap(x, y);
				swap(resl, resr);
			}
			resl = calc(1, 1, N, NodeID[y] + 1, NodeID[x]) + resl;
		}
		resl.swp();
		resl = resl + resr;
		resl.calc_sum();
		q[i].ans = resl.sum;
	}
	sort(q + 1, q + Q + 1, cmpt);
	for (int i = 1; i <= Q; i++)
		printf("%d\n", q[i].ans);
}