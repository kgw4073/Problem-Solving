#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
// 1338
using pii = pair<int, int>;
int N, L, R;
const int dy[] = { 0, 1, 0, -1 };
const int dx[] = { 1, 0, -1, 0 };
int map[50][50];
bool visited[50][50] = { false, };
queue<pii> q;
int answer = 0;
void solve() {
	while (1) {
		int moveCounter = 0;
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visited[i][j]) {
					int sum = 0;
					vector<pii> vec;
					sum += map[i][j];
					vec.emplace_back(i, j);
					q.emplace(i, j);
					visited[i][j] = true;
					while (q.size()) {
						int cnt = q.size();
						while (cnt--) {
							int y = q.front().first, x = q.front().second;
							q.pop();
							for (int dir = 0; dir < 4; dir++) {
								if (y + dy[dir] < 0 || y + dy[dir] >= N || x + dx[dir] < 0 || x + dx[dir] >= N) {
									continue;
								}
								if (visited[y + dy[dir]][x + dx[dir]]) continue;
								int diff = abs(map[y][x] - map[y + dy[dir]][x + dx[dir]]);
								if (L <= diff && diff <= R) {
									visited[y + dy[dir]][x + dx[dir]] = true;
									q.emplace(y + dy[dir], x + dx[dir]);
									vec.emplace_back(y + dy[dir], x + dx[dir]);
									sum += map[y + dy[dir]][x + dx[dir]];
								}
							}
						}
					}
					int unity = sum / vec.size();
					for (auto p : vec) {
						map[p.first][p.second] = unity;
					}
					if (vec.size() >= 2) {
						moveCounter = 1;
					}
				}
			}
		}

		if (!moveCounter) break;
		else answer += moveCounter;
	}


}
int main() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	
	solve();
	cout << answer;
}