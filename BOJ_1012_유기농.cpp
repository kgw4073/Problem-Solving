#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

int test, n, m, k;

using namespace std;
int map[50][50];
bool visit[50][50];
vector<pair<int, int> > vec;

const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

int bfs() {
	int answer = 0;
	for (auto p : vec) {
		int y = p.first, x = p.second;
		if (visit[y][x]) continue;
		queue<pair<int, int>> q;
		visit[y][x] = true;
		q.push({ y, x });
		answer++;

		while (!q.empty()) {
			int y = q.front().first, x = q.front().second;
			q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int ny = y + dy[dir], nx = x + dx[dir];
				if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
					continue;
				}
				if (!visit[ny][nx] && map[ny][nx]) {
					visit[ny][nx] = true;
					q.push({ ny, nx });
				}
			}
		}
	}
	return answer;
}
int main() {
	cin >> test;
	while (test--) {
		cin >> m >> n >> k;
		memset(map, 0, sizeof(map));
		memset(visit, 0, sizeof(visit));
		vec.clear();
		while (k--) {
			int x, y;
			cin >> x >> y;
			vec.emplace_back(y, x);
			map[y][x] = 1;
		}
		cout << bfs() << '\n';
	}
}