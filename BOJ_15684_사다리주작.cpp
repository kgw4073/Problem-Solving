#include <iostream>
#include <algorithm>

using namespace std;

int n, m, h;
int map[32][11];
int rmap[32][11];

const int inf = 2e9;
int answer = inf;

void solve(int start, int y, int x, int add, int rmap[][11], int map[][11]) {
	// ��� ���� ���� �� Ž���ϰ� �����ߴٸ� answer�� ����
	if (start == n + 1) {
		answer = min(answer, add);
		return;
	}
	// ������ ����ų� ���� �����ߴ� ���� ���� �������� ���ߴٸ� ����
	if (x <= 0 || x > n || (y >= h + 1 && x != start)) return;
	// ���� ���� �����Դµ� ������ ���� ���̶�� ���� ���� ���� Ž��
	if (y >= h + 1 && x == start) {
		solve(start + 1, 1, start + 1, add, rmap, map);
		return;
	}
	// ������ ���� �� �ִٸ� Ÿ�� ������
	if (map[y][x]) {
		solve(start, y + 1, x + 1, add, rmap, map);
	}
	// ���� ���� �� �ִٸ� Ÿ�� ������
	if (rmap[y][x]) {
		solve(start, y + 1, x - 1, add, rmap, map);
	}
	// �� �� ������
	if (!map[y][x] && !rmap[y][x]) {
		// ���� �߰��� ��ٸ��� 2������ ���� �ϳ� �� ���� �� ����
		if (add <= 2) {
			if (!map[y][x + 1]) {
				map[y][x] = 1;
				rmap[y][x + 1] = 1;
				solve(start, y + 1, x + 1, add + 1, rmap, map);
				rmap[y][x + 1] = 0;
				map[y][x] = 0;
			}
			if (!rmap[y][x - 1]) {
				map[y][x - 1] = 1;
				rmap[y][x] = 1;
				solve(start, y + 1, x - 1, add + 1, rmap, map);
				map[y][x - 1] = 0;
				rmap[y][x] = 0;
			}
		}
		// �׳� ������ ��
		solve(start, y + 1, x, add, rmap, map);
	}
}
int main() {
	cin >> n >> m >> h;
	// ���������� ���� ���� �������� ���� ���� map�� rmap���� ����
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		map[u][v] = 1;
		rmap[u][v + 1] = 1;
	}
	solve(1, 1, 1, 0, rmap, map);
	if (answer == inf) {
		cout << -1;
	}
	else {
		cout << answer;
	}
}