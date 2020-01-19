#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n, m;
// ������ ���� ��
int map[8][8];
// virus�� virus�� �ִ� ��ǥ�� ����
vector<pair<int, int>> virus;
// clean�� �������� ���� ��ǥ�� ����
vector<pair<int, int>> clean;
// wall�� ���� ���� ���̴�(������ ������ �� �ƴ�)
vector<pair<int, int>> wall;
// ���� ��ǥ
int dy[] = { 0, 1, 0, -1 };
int dx[] = { 1, 0, -1, 0 };
// safeArea�� ���� ���̷����� ������ ���� ���¿��� �������� ���� ���� ��
int safeArea = 0;
// ���� ū safeArea�� ����
int maxSafeArea = 0;

void bfs(int map[][8], int safeArea) {
	// virus�� �ִ� ������ ���� bfs�� ����
	for (pair<int, int> vir : virus) {
		queue<pair<int, int>> q;
		int y = vir.first;
		int x = vir.second;
		q.push({ y, x });
		while (!q.empty()) {
			y = q.front().first;
			x = q.front().second;
			q.pop();
			for (int dir = 0; dir < 4; dir++) {
				int ny = y + dy[dir], nx = x + dx[dir];
				// �ش� �ʿ� ���� �ְų� ���̷����� �ְų� �ε����� ����� ���̷��� �� ����
				if (map[ny][nx] || ny < 0 || ny >= n || nx < 0 || nx >= m) {
					continue;
				}
				// ���̷��� ����
				map[ny][nx] = 2;
				q.push({ ny, nx });
				safeArea--;
			}
		}
	}
	// ���̷����� ��� ���� ���¿��� maxSafeArea�� ��
	maxSafeArea = max(maxSafeArea, safeArea);
	return;
}

// �������� ���� ���� ���� ���� 
void dfs(int idx, int depth) {
	// �� ���� �������� ���� ���̷����� ������ ��.
	if (depth == 3) {
		// �ٸ� ��Ȳ�� Ž���ؾ� �ϹǷ� map�� ���̷����� ������ ���θ� �ȵ�
		// temp���ٰ� �����ؼ� �ѱ���!
		int temp[8][8];
		memcpy(temp, map, sizeof(temp));
		// safeArea - 3�� �ѱ� ������ ���� �� �� �������ϱ�
		bfs(temp, safeArea - 3);
		return;
	}

	// clean�� �� �߿� �� ���� ���� �������� ��Ʈ��ŷ
	for (int i = idx + 1; i < clean.size(); i++) {
		wall.push_back(clean[i]);
		map[clean[i].first][clean[i].second] = 1;
		dfs(i, depth + 1);
		map[clean[i].first][clean[i].second] = 0;
		wall.pop_back();
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			// �������� ���� ���̹Ƿ� safeArea ����, clean vector�� ��ǥ ����
			if (map[i][j] == 0) {
				clean.emplace_back(i, j);
				safeArea++;
			}
			// ���̷��� ������ virus vector�� ����
			else if (map[i][j] == 2) {
				virus.emplace_back(i, j);
			}
		}
	}
	// dfs�� �� �� �� ����
	dfs(-1, 0);
	cout << maxSafeArea;
}