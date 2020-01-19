#include <iostream>
#include <queue>

using namespace std;

char map[10][10];
int n, m;
struct ball {
	int ry, rx, by, bx;
};

ball current;
bool visit[10][10][10][10];
int dy[] = { 0, 1, 0, -1 };
int dx[] = { 1, 0, -1, 0 };

void bfs() {
	queue<ball> q;
	visit[current.ry][current.rx][current.by][current.bx] = true;
	bool escapable = false;
	q.push(current);
	int count = 0;

	while (q.size()) {
		int cnt = q.size();
		while (cnt--) {
			ball cur = q.front();
			q.pop();
			if (map[cur.ry][cur.rx] == 'O') {
				escapable = true;
				break;
			}
			for (int dir = 0; dir < 4; dir++) {
				// 0���� ������, 1���� �Ķ���
				// ���� ���ۿ� ������ �� ������ ����
				bool outFlag[2] = { false, };
				// �̵� �Ÿ�. �ϴ� ����ؼ� �̵��Ѵٰ� �����ϱ� ������
				// ���� ��ġ�� �������� ��, �� �� �̵��Ÿ��� ������ �� ĭ back �ؾ� ��.
				int movingDistance[2] = { 0, };
				vector<pair<int, int>> v;
				v.push_back({ cur.ry, cur.rx });
				v.push_back({ cur.by, cur.bx });

				for (int color = 0; color < 2; color++) {
					while (map[v[color].first + dy[dir]][v[color].second + dx[dir]] != '#') {
						movingDistance[color]++;
						v[color].first += dy[dir];
						v[color].second += dx[dir];

						// ���ۿ� ���ٸ� outFlag�� �����ϰ� ����
						if (map[v[color].first][v[color].second] == 'O') {
							outFlag[color] = true;
							break;
						}
					}
				}
				// �Ķ����� ������ ť�� �� ����
				if (outFlag[1]) continue;

				if (v[0].first == v[1].first && v[0].second == v[1].second) {
					if (movingDistance[0] > movingDistance[1]) {
						v[0].first -= dy[dir];
						v[0].second -= dx[dir];
					}
					else {
						v[1].first -= dy[dir];
						v[1].second -= dx[dir];
					}
				}
				// �̹� �湮�ߴ� ��ġ��� ť�� ���� �ʿ䰡 ����
				if (visit[v[0].first][v[0].second][v[1].first][v[1].second]) {
					continue;
				}
				visit[v[0].first][v[0].second][v[1].first][v[1].second] = true;

				ball next = { v[0].first, v[0].second, v[1].first, v[1].second };
				q.push(next);
			}
		}
		if (escapable) break;
		count++;
		if (count > 10) break;
	}
	if (escapable) {
		cout << count;
	}
	else {
		cout << -1;
	}
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			cin >> c;
			if (c == 'R') {
				current.ry = i;
				current.rx = j;
				c = '.';
			}
			else if (c == 'B') {
				current.by = i;
				current.bx = j;
				c = '.';
			}
			map[i][j] = c;
		}
	}
	bfs();
}