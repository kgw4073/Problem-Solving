#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;
int n, m;
const int dy[] = { 0, -1, 0, 1 };
const int dx[] = { -1, 0, 1, 0 };

int map[20][20];
bool visit[20][20];
struct Shark {
	int y, x, size, eat;
};
Shark root;

// 아기 상어가 기어갈 수 있는 범위 내에서 먹을 것이 남아 있는지 체크
bool check() {
	queue<pii> q;
	q.emplace(root.y, root.x);
	bool visited[20][20] = { false, };
	// bfs로 탐색
	while (!q.empty()) {
		int cnt = q.size();
		while (cnt--) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();
			for (int dir = 0; dir < 4; dir++) {
				int ny = y + dy[dir];
				int nx = x + dx[dir];
				if (ny < 0 || ny >= n || nx < 0 || nx >= n || visited[ny][nx]) {
					continue;
				}
				if (map[ny][nx] > root.size) continue;
				// 하나라도 먹을 게 있으니까 가능
				if (map[ny][nx] && (map[ny][nx] < root.size)) return true;
				q.emplace(ny, nx);
				visited[ny][nx] = true;
			}
		}
	}
	// 다 탐색해도 먹을 게 없으므로 불가능
	return false;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				map[i][j] = 0;
				root.y = i; root.x = j; root.size = 2, root.eat = 0;
			}
		}
	}
	// 좌표를 기준으로 우선 순위 큐를 이용하여 먹을 수 있는 것 넣어둠
	queue<pii> q;
	priority_queue<pii, vector<pii>, greater<> > eatable;
	q.emplace(root.y, root.x);
	visit[root.y][root.x] = true;
	int time = 0;
	int y, x;
	// 처음에 먹을 게 없으면 엄마 부름
	if (!check()) {
		cout << time;
	}
	else {
		while (q.size()) {
			int cnt = q.size();
			time++;
			while (cnt--) {
				y = q.front().first, x = q.front().second;
				q.pop();
				for (int dir = 0; dir < 4; dir++) {
					int ny = y + dy[dir], nx = x + dx[dir];
					if (ny < 0 || ny >= n || nx < 0 || nx >= n || visit[ny][nx]) {
						continue;
					}
					if (map[ny][nx] > root.size) {
						continue;
					}
					else {
						q.emplace(ny, nx);
						if (1 <= map[ny][nx] && map[ny][nx] < root.size) {
							eatable.emplace(ny, nx);
						}
					}
					visit[ny][nx] = true;
				}
			}
			// 먹을 거 하나라도 담겼으면 먹음
			if (!eatable.empty()) {
				y = eatable.top().first, x = eatable.top().second;
				root.y = y, root.x = x;
				// 먹고나서 root를 그쪽으로 옮김
				map[y][x] = 0;
				root.eat++;
				if (root.eat == root.size) {
					root.eat = 0;
					root.size++;
				}
				// 이제 root 위치에서 먹을 게 남았나 확인
				if (!check()) {
					cout << time;
					return 0;
				}
				// 먹을 거 남아있으면 bfs 처음부터 시작해야 함
				memset(visit, 0, sizeof(visit));
				while (!q.empty()) q.pop();
				while (!eatable.empty()) eatable.pop();
				q.emplace(y, x);
				visit[y][x] = true;
			}
		}
	}
}