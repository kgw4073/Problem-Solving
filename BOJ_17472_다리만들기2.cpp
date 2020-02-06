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

// visited는 단순히 섬에 번호를 매길 때 dfs를 하기 위함
bool visited[10][10];

// 섬들이 이어졌는지 dfs를 할 때 일종의 visit 배열임
bool check[7] = { false, };

// islands 번호에 해당하는 벡터에 좌표가 전부 들어가 있음
vector<pii> islands[7];

// graph는 인접 리스트로 섬들의 연결 상태를 나타내며, connected는 인접 행렬로 직접적인 연결 상태를 나타냄
vector<int> graph[7];
bool connected[7][7];

// numbering은 섬 번호 매길 때 씀
int numbering, ans = 100000;

// dfs는 섬 번호를 매기기 위함
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

// 섬들이 연결되었는지 판별
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
	// adj는 1번 섬부터 checkDfs로 탐색가능한 섬 개수
	int adj = 1;
	memset(check, 0, sizeof(check));
	check[1] = true;
	checkDfs(1, adj);
	// 1번 섬으로부터 전부 탐색 가능하면 답 갱신
	if (adj == numbering) {
		ans = min(ans, bridge);
		return;
	}

	// 모든 섬에 대해 탐색
	for (int i = idx + 1; i <= numbering; i++) {
		// 각 섬의 땅에 대해서 하나 씩 뽑아서 네 방향 탐색
		for (auto& cand : islands[i]) {
			int y = cand.first, x = cand.second;
			for (int dir = 0; dir < 4; dir++) {
				// 다음 칸과 다다음 칸에 다리를 놓을 수 없으면 탐색 안함
				int ny = y + dy[dir], nx = x + dx[dir];
				int nny = ny + dy[dir], nnx = nx + dx[dir];
				if (ny < 0 || ny >= n || nx < 0 || nx >= m || map[ny][nx] == i) continue;
				if (nny < 0 || nny >= n || nnx < 0 || nnx >= m || map[nny][nnx] == i) continue;
				// 다음 칸 혹은 다다음 칸에 섬이 있어도 탐색 안함
				if ((0 < map[ny][nx] && map[ny][nx] < 9) || 0 < map[nny][nnx] && map[nny][nnx] < 9) continue;

				// count는 현재 점에서 놓는 다리 개수
				int count = 0;

				// fail은 다리를 놓을 수 있는지 없는지
				bool fail = false;

				// map 보존을 위해
				int temp[10][10];
				memcpy(temp, map, sizeof(temp));

				// opposite는 다리를 놓을 수 있을 때 다리가 놓여진 상대 섬
				int opposite;
				while (true) {
					// ny, nx 부터 다리 놓음
					temp[ny][nx] = 9;
					count++;
					int temp_y = ny + dy[dir], temp_x = nx + dx[dir];

					// 바다 벗어나거나, 본인 섬에 닿으면 실패
					if (temp_y < 0 || temp_y >= n || temp_x < 0 || temp_x >= m || map[temp_y][temp_x] == i) {
						fail = true;
						break;
					}
					// 본인 섬이 아니고 다른 섬에 다다랐으면 성공
					if (map[temp_y][temp_x] != i && 0 < map[temp_y][temp_x] && map[temp_y][temp_x] < 9) {
						opposite = map[temp_y][temp_x];
						break;
					}
					ny = temp_y;
					nx = temp_x;
				}

				// 다리 놓을 수 있을 때
				if (!fail) {
					// 연결 안되어 있으면 연결
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
	// 인접한 섬들 번호 매김
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