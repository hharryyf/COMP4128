#include <bits/stdc++.h>
#define MAX_SIZE 262192

using namespace std;

struct qrs {
	int l, r;
	int id;
};

vector<qrs> a;

// the range tree 
int tree[MAX_SIZE];

// the previous index for each number
int pre[MAX_SIZE >> 1];

int val[MAX_SIZE >> 1];

int ans[MAX_SIZE >> 1];

int n, q;

static bool cmp(const qrs &aa, const qrs &ab) {
	if (aa.r != ab.r) return aa.r < ab.r;
	return aa.l < ab.l;
}

void update(int pt, int l, int r, int index, int val) {
	if (pt <= 0) return;
	if (l > r) return;
	if (l == r && r == pt) {
		tree[index] = val;
		return;
	}
	
	int mid = l + (r - l) / 2; 
	if (pt <= mid) {
		update(pt, l, mid, index * 2, val);
	} else {
		update(pt, mid + 1, r, index * 2 + 1, val);
	}
	
	tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

int query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return 0;
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
}

int main() {
	int i, j;
	scanf("%d", &n);
	scanf("%d", &q);
	unordered_map<int, int> h;
	for (i = 1 ; i <= n; i++) {
		scanf("%d", &val[i]);
		
		if (h.find(val[i]) == h.end()) {
			pre[i] = 0;
		} else {
			pre[i] = h[val[i]];
		}
		
		h[val[i]] = i;
		
	}	
	
	for (i = 0 ; i < q; i++) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		a.push_back(qrs{v1, v2, i});
	}
	
	
	sort(a.begin(), a.end(), cmp);
	
	for (i = 0, j = 1 ; i < q; i++) {
		while (j <= n && j <= a[i].r) {
			update(pre[pre[j]], 1, n, 1, 0);
			update(pre[j], 1, n, 1, -1);
			update(j, 1, n, 1, 1);
			j++;
		}
		ans[a[i].id] = query(a[i].l, a[i].r, 1, n, 1);
	}
	
	for (i = 0 ; i < q; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
