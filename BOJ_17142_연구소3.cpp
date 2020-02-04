#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <deque>

using namespace std;
using pii = pair<int, int>;
int n, m;

int map[50][50], times[50][50];

int target = 0;
const int inf = 2e9;
int answer = inf;

vector<pii> virus;
vector<pii> selected;

const int dy[] = { 0, 1, 0, -1 };
const int dx[] = { 1, 0, -1, 0 };

void bfs() {
	memset(times, -1, sizeof(times));
	queue<pii> q;
	for (auto& p : selected) {
		q.emplace(p);
		times[p.first][p.second] = 0;
	}
	int time = 0;
	int count = 0;
	while (q.size()) {
		int cnt = q.size();
		while (cnt--) {
			int y = q.front().first, x = q.front().second;
			q.pop();
			for (int dir = 0; dir < 4; dir++) {
				int ny = y + dy[dir], nx = x + dx[dir];
				if (ny < 0 || ny >= n || nx < 0 || nx >= n || times[ny][nx] != -1) continue;
				if (map[ny][nx] == 1) continue;
				times[ny][nx] = times[y][x] + 1;
				if (map[ny][nx] == 0) {
					count++;
					time = times[ny][nx];
				}
				q.emplace(ny, nx);
			}
		}
	}
	if (count == target) {
		answer = min(answer, time);
	}
}
void solve(int idx, int depth) {
	if (depth == m) {
		bfs();
		return;
	}
	for (int i = idx + 1; i < virus.size(); i++) {
		selected.emplace_back(virus[i]);
		solve(i, depth + 1);
		selected.pop_back();
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
				virus.emplace_back(i, j);
			}
			else if (map[i][j] == 0) {
				target++;
			}
		}
	}
	solve(-1, 0);
	if (answer == inf) {
		answer = -1;
	}
	cout << answer;
}