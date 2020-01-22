#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// using Segment tree
// 10�� ���� ���ڰ� �����µ� �̸� ���� ������ �ϴ�
// Ʈ�� ����� �� ������ 2^18�̴�.
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
// half �ʱ�ȭ
void init() {
	for (half = 1; half < n; half <<= 1);
}
// �ִ�, �ּڰ� segment tree update
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
	// ��� ���� ��忡 ���� ���� �ö󰡴� seg tree ����
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