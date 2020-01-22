#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// using Segment tree
// 10만 개의 숫자가 들어오는데 이를 위해 만들어야 하는
// 트리 노드의 총 개수는 2^18이다.
int maxseg[262145];
int minseg[262145];

int n, m, half;
// bottom-up approach
pair<int, int> find(int l, int r) {
	int mx = 0;
	int mn = 2e9;
	l += half, r += half;
	while (l <= r) {
		if (l % 2) {
			mx = max(mx, maxseg[l]);
			mn = min(mn, minseg[l++]);
		}
		if (!(r % 2)) {
			mx = max(mx, maxseg[r]);
			mn = min(mn, minseg[r--]);
		}
		l >>= 1; r >>= 1;
	}
	return { mx, mn };
}
// half 초기화
void init() {
	for (half = 1; half < n; half <<= 1);
}
// 최댓값, 최솟값 segment tree update
void update(int idx) {
	idx += half;
	idx >>= 1;
	while (idx) {
		maxseg[idx] = max(maxseg[idx * 2], maxseg[idx * 2 + 1]);
		minseg[idx] = min(minseg[idx * 2], minseg[idx * 2 + 1]);
		idx >>= 1;
	}
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	init();
	for (int i = 0; i < n; i++) {
		int val;
		cin >> val;
		maxseg[i + half] = val;
		minseg[i + half] = val;
	}
	// 모든 리프 노드에 대해 위로 올라가는 seg tree 갱신
	for (int i = 0; i < n; i++) {
		update(i);
	}
	while (m--) {
		int l, r;
		cin >> l >> r;
		pair<int, int> p = find(l - 1, r - 1);
		cout << p.second << ' ' << p.first << '\n';
	}
}