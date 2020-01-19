#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n, m;
// 연구소 상태 맵
int map[8][8];
// virus는 virus가 있는 좌표를 담음
vector<pair<int, int>> virus;
// clean는 오염되지 않은 좌표를 담음
vector<pair<int, int>> clean;
// wall은 새로 새울 벽이다(기존에 세워진 벽 아님)
vector<pair<int, int>> wall;
// 방향 좌표
int dy[] = { 0, 1, 0, -1 };
int dx[] = { 1, 0, -1, 0 };
// safeArea는 아직 바이러스가 퍼지지 않은 상태에서 오염되지 않은 곳의 수
int safeArea = 0;
// 가장 큰 safeArea를 저장
int maxSafeArea = 0;

void bfs(int map[][8], int safeArea) {
	// virus가 있는 곳마다 전부 bfs를 시행
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
				// 해당 맵에 벽이 있거나 바이러스가 있거나 인덱스를 벗어나면 바이러스 안 퍼짐
				if (map[ny][nx] || ny < 0 || ny >= n || nx < 0 || nx >= m) {
					continue;
				}
				// 바이러스 퍼짐
				map[ny][nx] = 2;
				q.push({ ny, nx });
				safeArea--;
			}
		}
	}
	// 바이러스가 모두 퍼진 상태에서 maxSafeArea와 비교
	maxSafeArea = max(maxSafeArea, safeArea);
	return;
}

// 오염되지 않은 곳에 벽을 세움 
void dfs(int idx, int depth) {
	// 세 개를 세웠으면 이제 바이러스가 퍼져야 함.
	if (depth == 3) {
		// 다른 상황을 탐색해야 하므로 map을 바이러스가 퍼지게 냅두면 안됨
		// temp에다가 복사해서 넘기자!
		int temp[8][8];
		memcpy(temp, map, sizeof(temp));
		// safeArea - 3을 넘긴 이유는 벽을 세 개 세웠으니까
		bfs(temp, safeArea - 3);
		return;
	}

	// clean한 곳 중에 세 곳을 고르는 오름차순 백트래킹
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
			// 오염되지 않은 곳이므로 safeArea 증가, clean vector에 좌표 넣음
			if (map[i][j] == 0) {
				clean.emplace_back(i, j);
				safeArea++;
			}
			// 바이러스 있으면 virus vector에 넣음
			else if (map[i][j] == 2) {
				virus.emplace_back(i, j);
			}
		}
	}
	// dfs로 벽 세 개 세움
	dfs(-1, 0);
	cout << maxSafeArea;
}