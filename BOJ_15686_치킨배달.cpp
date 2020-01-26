#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;
// 1252
const int inf = 2e9;
int n, m;
int map[50][50];
vector<pii> vec;
vector<pii> house;
vector<pii> selected;
bool visit[14];
int minDistance = inf;

int calculate() {
	int totalDist = 0;
	for (auto& home : house) {
		int eachChickDistance = inf;
		for (auto& chick : selected) {
			eachChickDistance = min(eachChickDistance, 
				abs(chick.first - home.first) + abs(chick.second - home.second));
		}
		totalDist += eachChickDistance;
	}
	return totalDist;
}
void solve(int depth, int idx) {
	if (depth == m) {
		minDistance = min(minDistance, calculate());
		return;
	}
	for (int i = idx; i < vec.size(); i++) {
		if (!visit[i]) {
			visit[i] = true;
			selected.emplace_back(vec[i].first, vec[i].second);
			solve(depth + 1, i);
			visit[i] = false;
			selected.pop_back();
		}

	}
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				vec.emplace_back(i, j);
			}
			else if (map[i][j] == 1) {
				house.emplace_back(i, j);
			}
		}
	}
	solve(0, 0);
	cout << minDistance;
}