#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//1420

struct marker {
	int idx, y, x, dir;
};

int main() {
	int n, k;
	int map[12][12];
	marker info[10];
	vector<int> state[12][12];
	const int dy[] = { 0, 0, -1, 1 };
	const int dx[] = { 1, -1, 0, 0 };

	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < k; i++) {
		int y, x, dir;
		cin >> y >> x >> dir;
		y--; x--; dir--;
		info[i].y = y, info[i].x = x, info[i].dir = dir, info[i].idx = 0;
		state[y][x].emplace_back(i);
	}
	int turn;
	for (turn = 1; turn <= 1000; turn++) {
		for (int i = 0; i < k; i++) {
			int y = info[i].y, x = info[i].x, & dir = info[i].dir;
			int ny = y + dy[dir], nx = x + dx[dir];
			// ÆÄ¶õ»ö
			if (ny < 0 || ny >= n || nx < 0 || nx >= n || map[ny][nx] == 2) {
				if (dir == 0) dir = 1;
				else if (dir == 1) dir = 0;
				else if (dir == 2) dir = 3;
				else if (dir == 3) dir = 2;
				if (y + dy[dir] < 0 || y + dy[dir] >= n || x + dx[dir] < 0 || x + dx[dir] >= n || map[y + dy[dir]][x + dx[dir]] == 2) {
					continue;
				}
				ny = y + dy[dir], nx = x + dx[dir];
			}
			// Èò»ö
			if (map[ny][nx] == 0) {
				int cnt = 0;
				int prevIdx = info[i].idx;
				int prevNewSize = state[ny][nx].size();
				int prevSize = state[y][x].size();
				for (int k = prevIdx; k < prevSize; k++, cnt++) {
					int number = state[y][x][k];
					info[number].idx = prevNewSize + cnt;
					info[number].y = ny, info[number].x = nx;
					state[ny][nx].emplace_back(number);
					if (state[ny][nx].size() >= 4) {
						cout << turn;
						return 0;
					}
				}
				for (int k = prevSize - 1; k >= prevIdx; k--) {
					state[y][x].pop_back();
				}
			}
			// »¡°£»ö
			else if (map[ny][nx] == 1) {
				int cnt = 0;
				int prevIdx = info[i].idx;
				int prevNewSize = state[ny][nx].size();

				for (int k = state[y][x].size() - 1; k >= prevIdx; k--, cnt++) {
					int number = state[y][x][k];
					info[number].idx = prevNewSize + cnt;
					info[number].y = ny, info[number].x = nx;
					state[ny][nx].emplace_back(number);
					if (state[ny][nx].size() >= 4) {
						cout << turn;
						return 0;
					}
					state[y][x].pop_back();
				}

			}
		}
	}
	if (turn == 1001) {
		cout << -1;
	}

}