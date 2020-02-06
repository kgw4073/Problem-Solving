#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;

const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };

int map[10][10];
int n, m;

// visited�� �ܼ��� ���� ��ȣ�� �ű� �� dfs�� �ϱ� ����
bool visited[10][10];

// ������ �̾������� dfs�� �� �� ������ visit �迭��
bool check[7] = { false, };

// islands ��ȣ�� �ش��ϴ� ���Ϳ� ��ǥ�� ���� �� ����
vector<pii> islands[7];

// graph�� ���� ����Ʈ�� ������ ���� ���¸� ��Ÿ����, connected�� ���� ��ķ� �������� ���� ���¸� ��Ÿ��
vector<int> graph[7];
bool connected[7][7];

// numbering�� �� ��ȣ �ű� �� ��
int numbering, ans = 100000;

// dfs�� �� ��ȣ�� �ű�� ����
void dfs(int y, int x, int numbering) {
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir], nx = x + dx[dir];
		if (ny < 0 || ny >= n || nx < 0 || nx >= m || !map[ny][nx]) {
			continue;
		}
		if (visited[ny][nx] && map[ny][nx]) continue;

		visited[ny][nx] = true;
		map[ny][nx] = numbering;
		islands[numbering].emplace_back(ny, nx);
		dfs(ny, nx, numbering);
	}
}

// ������ ����Ǿ����� �Ǻ�
void checkDfs(int cur, int& cnt) {
	for (int next : graph[cur]) {
		if (!check[next]) {
			check[next] = true;
			cnt++;
			checkDfs(next, cnt);
		}
	}
}

void solve(int idx, int bridge, int map[][10]) {
	// adj�� 1�� ������ checkDfs�� Ž�������� �� ����
	int adj = 1;
	memset(check, 0, sizeof(check));
	check[1] = true;
	checkDfs(1, adj);
	// 1�� �����κ��� ���� Ž�� �����ϸ� �� ����
	if (adj == numbering) {
		ans = min(ans, bridge);
		return;
	}

	// ��� ���� ���� Ž��
	for (int i = idx + 1; i <= numbering; i++) {
		// �� ���� ���� ���ؼ� �ϳ� �� �̾Ƽ� �� ���� Ž��
		for (auto& cand : islands[i]) {
			int y = cand.first, x = cand.second;
			for (int dir = 0; dir < 4; dir++) {
				// ���� ĭ�� �ٴ��� ĭ�� �ٸ��� ���� �� ������ Ž�� ����
				int ny = y + dy[dir], nx = x + dx[dir];
				int nny = ny + dy[dir], nnx = nx + dx[dir];
				if (ny < 0 || ny >= n || nx < 0 || nx >= m || map[ny][nx] == i) continue;
				if (nny < 0 || nny >= n || nnx < 0 || nnx >= m || map[nny][nnx] == i) continue;
				// ���� ĭ Ȥ�� �ٴ��� ĭ�� ���� �־ Ž�� ����
				if ((0 < map[ny][nx] && map[ny][nx] < 9) || 0 < map[nny][nnx] && map[nny][nnx] < 9) continue;

				// count�� ���� ������ ���� �ٸ� ����
				int count = 0;

				// fail�� �ٸ��� ���� �� �ִ��� ������
				bool fail = false;

				// map ������ ����
				int temp[10][10];
				memcpy(temp, map, sizeof(temp));

				// opposite�� �ٸ��� ���� �� ���� �� �ٸ��� ������ ��� ��
				int opposite;
				while (true) {
					// ny, nx ���� �ٸ� ����
					temp[ny][nx] = 9;
					count++;
					int temp_y = ny + dy[dir], temp_x = nx + dx[dir];

					// �ٴ� ����ų�, ���� ���� ������ ����
					if (temp_y < 0 || temp_y >= n || temp_x < 0 || temp_x >= m || map[temp_y][temp_x] == i) {
						fail = true;
						break;
					}
					// ���� ���� �ƴϰ� �ٸ� ���� �ٴٶ����� ����
					if (map[temp_y][temp_x] != i && 0 < map[temp_y][temp_x] && map[temp_y][temp_x] < 9) {
						opposite = map[temp_y][temp_x];
						break;
					}
					ny = temp_y;
					nx = temp_x;
				}

				// �ٸ� ���� �� ���� ��
				if (!fail) {
					// ���� �ȵǾ� ������ ����
					if (!connected[i][opposite]) {
						connected[i][opposite] = true;
						connected[opposite][i] = true;
						graph[i].push_back(opposite);
						graph[opposite].push_back(i);
						solve(i, bridge + count, temp);
						graph[i].pop_back();
						graph[opposite].pop_back();
						connected[i][opposite] = false;
						connected[opposite][i] = false;
					}
				}
			}
		}
	}
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
	// ������ ���� ��ȣ �ű�
	numbering = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] && !visited[i][j]) {
				map[i][j] = numbering;
				visited[i][j] = true;
				islands[numbering].emplace_back(i, j);
				dfs(i, j, numbering);
				numbering++;
			}
		}
	}
	numbering--;
	solve(0, 0, map);
	if (ans == 100000) ans = -1;
	cout << ans;
}