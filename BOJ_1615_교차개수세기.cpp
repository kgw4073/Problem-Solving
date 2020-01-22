#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// using Segment tree
const int max_vertices = 2000;
int seg[max_vertices * (max_vertices - 1) / 2 + 1];
int n, m, half;

// for sorting input edges
vector<pair<int, int> > vec;

// bottom-up approach
long long sum(int l, int r) {
	long long res = 0;
	l += half, r += half;
	while (l <= r) {
		if (l % 2) {
			res += seg[l++];
		}
		if (!(r % 2)) {
			res += seg[r--];
		}
		l >>= 1; r >>= 1;
	}
	return res;
}
// half √ ±‚»≠
void init() {
	for (half = 1; half < n; half <<= 1);
}

void update(int idx) {
	idx += half;
	seg[idx]++;
	idx >>= 1;
	while (idx) {
		seg[idx] = seg[idx * 2] + seg[idx * 2 + 1];
		idx >>= 1;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		vec.push_back({ u - 1, v - 1 });
	}
	
	sort(vec.begin(), vec.end());
	init();

	long long answer = 0;
	for (auto p : vec) {
		int u = p.first, v = p.second;
		update(v);
		answer += sum(v + 1, half);
	}
	cout << answer;
}