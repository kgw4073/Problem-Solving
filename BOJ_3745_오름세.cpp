#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;

int n, half;
int sequence[100001];
int seg[258001];

// using segment tree

int find(int l, int r) {
	int res = 0;
	l += half, r += half;
	while (l <= r) {
		if (l % 2) {
			res = max(res, seg[l++]);
		}
		if (!(r % 2)) {
			res = max(res, seg[r--]);
		}
		l >>= 1; r >>= 1;
	}
	return res;
}
void update(int idx, int x) {
	idx += half;
	seg[idx] = x;
	idx >>= 1;
	while (idx) {
		seg[idx] = max(seg[idx * 2], seg[idx * 2 + 1]);
		idx >>= 1;
	}
}

void init() {
	for (half = 1; half < n; half <<= 1);
	memset(seg, 0, sizeof(seg));
}

int main() {
	while (scanf("%d", &n) != EOF) {
		vector<pii> vec;
		for (int i = 0; i < n; i++) {
			scanf("%d", &sequence[i]);
			vec.emplace_back(sequence[i], -i);
		}
		sort(vec.begin(), vec.end());
		init();
		for (int i = 0; i < n; i++) {
			int val = vec[i].first, idx = -vec[i].second;
			int lis = find(0, idx);
			update(idx, lis + 1);
		}
		printf("%d\n", seg[1]);
	}
}
