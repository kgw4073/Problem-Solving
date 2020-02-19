#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;
int n, m;
const int dy[] = { 0, 1, 0, -1 };
const int dx[] = { 1, 0, -1, 0 };
char map[1001][1001];
int answer[1001][1001][2];
struct P {
	int y, x, state;
	P(int _y, int _x, int _state) : y(_y), x(_x), state(_state) {}
};
int bfs() {

	queue<P> q;
	q.emplace(0, 0, 0);
	answer[0][0][0] = 1;

	while (!q.empty()) {
		int y = q.front().y, x = q.front().x, state = q.front().state;
		q.pop();
		if (y == n - 1 && x == m - 1) return answer[y][x][state];
		for (int dir = 0; dir < 4; dir++) {
			int ny = y + dy[dir], nx = x + dx[dir];
			if (ny < 0 || ny >= n || nx < 0 || nx >= m || answer[ny][nx][state]) continue;
			if (map[ny][nx] == '0') {
				answer[ny][nx][state] = answer[y][x][state] + 1;
				q.emplace(ny, nx, state);
			}
			if (map[ny][nx] == '1') {
				if (state == 0) {
					answer[ny][nx][1] = answer[y][x][state] + 1;
					q.emplace(ny, nx, 1);
				}
			}
		}
	}
	return -1;
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	cout << bfs();
}