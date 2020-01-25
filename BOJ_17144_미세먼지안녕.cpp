#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

using pii = pair<int, int>;

int r, c, t;
int map[50][50];
const int dy[] = { 0, -1, 0, 1 };
const int dx[] = { 1, 0, -1, 0 };
int cleaner_y, cleaner_x;
queue<pii> q;

int answer = 0;

void bfs() {
	while (!q.empty()) {
		if (!t--) break;
		int temp[50][50];
		memset(temp, 0, sizeof(temp));

		int cnt = q.size();
		// ť�� �ִ� ���� ���� Ȯ���Ŵ
		while(cnt--) {
			int y = q.front().first, x = q.front().second;
			q.pop();
			
			for (int dir = 0; dir < 4; dir++) {
				// ������ �����ų� û�ұ�� �ȵ�
				if (y + dy[dir] < 0 || y + dy[dir] > r - 1 || x + dx[dir]<0 || x + dx[dir]>c - 1 || map[y + dy[dir]][x + dx[dir]] == -1) {
					continue;
				}
				int flow = map[y][x] / 5;
				temp[y + dy[dir]][x + dx[dir]] += flow;
				temp[y][x] -= flow;
			}
		}
		
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				map[i][j] += temp[i][j];
			}
		}
		//���� û������
		for (int i = 0; i < 2; i++) {
			int yy = cleaner_y + i, xx = cleaner_x;
			int y_end = (i == 0) ? -1 : r;
			int dirchange = (i == 0) ? 1 : 3;

			int dir = 0;
			int prev = 0;

			while (1) {
				yy += dy[dir], xx += dx[dir];
				if (xx >= c) {
					if (i == 0) {
						yy--;
					}
					else yy++;
					xx = c - 1;
					dir = (dir + dirchange) % 4;
				}
				else if (yy == y_end) {
					if (i == 0) {
						yy = 0;
					}
					else {
						yy = r - 1;
					}
					xx--;
					dir = (dir + dirchange) % 4;
				}

				else if (xx < 0) {
					if (i == 0) {
						yy++;
					}
					else yy--;
					xx = 0;
					dir = (dir + dirchange) % 4;
				}
				// û�ұ⿡ �����ϸ� Ż��
				if (map[yy][xx] == -1) {
					break;
				}
				int cur = map[yy][xx];
				map[yy][xx] = prev;
				prev = cur;
			}
		}
		// �����ִ� �� �ٽ� Ȯ����Ѿ� �ϹǷ� ť�� ��´�.
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (map[i][j] > 0) {
					q.emplace(i, j);
				}
			}
		}
	}
	
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] > 0) {
				answer += map[i][j];
			}
		}
	}
}
int main() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> r >> c >> t;

	// û�ұ� ��ġ üũ flag
	bool flag = false;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1 && !flag) {
				flag = true;
				cleaner_y = i, cleaner_x = j;
			}
			else if (map[i][j] > 0) {
				q.emplace(i, j);
			}
		}
	}
	bfs();
	cout << answer;
}