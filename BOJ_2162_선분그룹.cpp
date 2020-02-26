#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#define x first
#define y second
using namespace std;
using pii = pair<int, int>;
int parent[3001];
int num[3001];
int n;
vector<pair<pii, pii> > vec;

int find(int a) {
	if (parent[a] == a) return a;
	else parent[a] = find(parent[a]);
}
void un(int a, int b) {
	a = find(a), b = find(b);
	
	if (a < b) parent[b] = a;
	else parent[a] = b;
}
__inline void swap(pii& a, pii& b) {
	pii tmp = a;
	a = b;
	b = tmp;
}
int ccw(pii& a, pii& b, pii& c) {
	b = { b.x - a.x, b.y - a.y };
	c = { c.x - a.x, c.y - a.y };
	int ret = b.x * c.y - b.y * c.x;
	if (ret > 0) return 1;
	else if (ret < 0) return -1;
	else return ret;
}
bool isIntersect(int i, int j) {
	pii p1 = vec[i].x;
	pii p2 = vec[i].y;
	pii p3 = vec[j].x;
	pii p4 = vec[j].y;
	int ccw1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
	int ccw2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
	if (ccw1 == 0 && ccw2 == 0) {
		if (p1 > p2) swap(p1, p2);
		if (p3 > p4) swap(p3, p4);
		return p1 <= p4 && p3 <= p2;
	}
	return ccw1 <= 0 && ccw2 <= 0;
}
void solve() {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (isIntersect(i, j)) {
				un(i, j);
			}
		}
	}
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		pii a = { x1, y1 }, b = { x2, y2 };
		vec.emplace_back(a, b);
		parent[i] = i;
		num[i] = 0;
	}
	solve();
	int mx = 0;
	int answer = 0;
	for (int i = 0; i < n; i++) {
		if (parent[i] == i) answer++;
		num[find(i)]++;
		if (num[parent[i]] > mx) {
			mx = num[parent[i]];
		}
	}
	cout << answer << '\n' << mx;
}