#include <iostream>

using namespace std;

// 1451
int n, m;
int y, x, dir;
//                 북 동 남 서
const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };
int map[50][50];
bool visit[50][50] = { false, };
int solve() {
	int answer = 1;
	visit[y][x] = 1;
	while (true) {
		bool flag = false;
		for (int d = 0; d < 4; d++) {
			if (map[y + dy[d]][x + dx[d]] || visit[y + dy[d]][x + dx[d]]) {
				continue;
			}
			flag = true;
		}
		if (!flag) {
			if (map[y - dy[dir]][x - dx[dir]]) {
				break;
			}
			else {
				y -= dy[dir];
				x -= dx[dir];
				continue;
			}
		}

		int searchDir = (dir + 3) % 4;
		// 2-a 왼쪽 방향에 청소하지 않은 공간 존재한다면
		if (!map[y + dy[searchDir]][x + dx[searchDir]] && !visit[y + dy[searchDir]][x + dx[searchDir]]) {
			// 그 방향으로 회전하고 한칸 전진
			dir = searchDir;
			y += dy[dir], x += dx[dir];
			visit[y][x] = true;
			answer++;
			continue;
		}
		// 2-b 왼쪽 방향에 청소할 공간이 없다면
		if (visit[y + dy[searchDir]][x + dx[searchDir]] || map[y + dy[searchDir]][x + dx[searchDir]]) {
			// 왼쪽으로 회전하고 돌아감
			dir = searchDir;
			continue;
		}	
	}
	return answer;
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n >> m >> y >> x >> dir;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	cout << solve();
}