#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 사무실의 세로와 가로 크기가 n, m
int n, m;
// 8*8이 최대이므로 사각지대의 최솟값을 우선 100으로 설정
int minBlindSpot = 100;

// map과 tempMap을 사용하여 dfs로부터 리턴될 때 map을 복사
int map[8][8];

// 방향 배열
//	 3
// 2 + 0
//   1
int dy[] = { 0, 1, 0, -1 };
int dx[] = { 1, 0, -1, 0 };

// cctv 좌표를 담을 벡터
vector<pair<int, int>> cctv;

// brute forcing으로 모든 cctv를 검색
/*
	idx는 현재 탐색하고 있는 cctv번호
	blindSpot은 현재 맵 상태에서의 사각지대 개수
*/
void simulate(int idx, int blindSpot) {
	// cctv 인덱스가 끝까지 도달했으면 트리의 leaf node에 도달한 것
	if (idx == cctv.size()) {
		if (minBlindSpot > blindSpot) {
			minBlindSpot = blindSpot;
		}
		return;
	}

	// cctv의 원래 좌표를 저장
	int original_y = cctv[idx].first;
	int original_x = cctv[idx].second;

	// cctv의 종류
	int cctvNo = map[original_y][original_x];

	/// y, x는 cctv가 감시하는 사무실 인덱스
	int y, x;

	int tempMap[8][8];
	// dfs로부터 리턴시 맵 복구를 위해 저장.
	memcpy(tempMap, map, sizeof(map));

	// 1번일 때는 한 방향만 탐색 가능하므로 네 방향 모두 탐색
	if (cctvNo == 1) {
		for (int dir = 0; dir < 4; dir++) {
			int watchedArea = 0;
			y = original_y;
			x = original_x;

			// 벽에 도달할 때까지
			while (true) {
				y += dy[dir];
				x += dx[dir];

				// 사무실을 벗어나거나 벽이 있으면 탈출
				if (y < 0 || y >= n || x < 0 || x >= m || map[y][x] == 6) {
					break;
				}
				// 감시 가능한 곳이면 watchedArea증가시키고 칸 상태를 7로 바꿈
				if (map[y][x] == 0) {
					watchedArea++;
					map[y][x] = 7;
				}
			}

			// 현재 사각지대에서 감시 가능한 곳을 빼고 탐색
			simulate(idx + 1, blindSpot - watchedArea);

			// 맵 상태가 하나라도 바뀌었으면 맵 복구
			if (watchedArea) {
				memcpy(map, tempMap, sizeof(map));
			}
		}
	}
	// cctv번호가 2번이면
	else if (cctvNo == 2) {
		// cctv는 두 번만 돌리면 모든 방향 탐색 가능
		for (int dir = 0; dir < 2; dir++) {
			int watchedArea = 0;

			// coveredDir은 한 번에 커버 가능한 방향
			// 한 번에 두 방향을 커버 가능하므로 count가 2가 되기 전까지 탐색
			// 한 번에 반대 방향까지 탐색 가능하므로 (coveredDir + 2) % 4
			for (int coveredDir = dir, count = 0; count < 2; count++, coveredDir = (coveredDir + 2) % 4) {
				y = original_y;
				x = original_x;

				while (true) {
					y += dy[coveredDir];
					x += dx[coveredDir];
					if (y < 0 || y >= n || x < 0 || x >= m || map[y][x] == 6) {
						break;
					}
					if (map[y][x] == 0) {
						watchedArea++;
						map[y][x] = 7;
					}
				}
			}

			simulate(idx + 1, blindSpot - watchedArea);

			if (watchedArea) {
				memcpy(map, tempMap, sizeof(map));
			}

		}
	}
	// cctv가 3번이면
	else if (cctvNo == 3) {
		// 네 번 돌릴 때 모두 다른 지역을 탐색하게 됨
		for (int dir = 0; dir < 4; dir++) {
			int watchedArea = 0;

			// 90도 방향으로 두 방향 커버 가능하므로
			// count < 2까지이고, coveredDir은 (coveredDir + 1) % 4
			for (int coveredDir = dir, count = 0; count < 2; count++, coveredDir = (coveredDir + 1) % 4) {
				y = original_y;
				x = original_x;

				while (true) {
					y += dy[coveredDir];
					x += dx[coveredDir];
					if (y < 0 || y >= n || x < 0 || x >= m || map[y][x] == 6) {
						break;
					}
					if (map[y][x] == 0) {
						watchedArea++;
						map[y][x] = 7;
					}
				}
			}

			simulate(idx + 1, blindSpot - watchedArea);

			if (watchedArea) {
				memcpy(map, tempMap, sizeof(map));
			}
		}
	}
	// cctvNo가 4번이면
	else if (cctvNo == 4) {
		// 네 번 돌릴 때마다 다른 지역을 탐색
		for (int dir = 0; dir < 4; dir++) {
			int watchedArea = 0;
			// 한 번에 세 방향을 탐색 가능하다.
			// count < 3까지이고, coveredDir = (coveredDir + 1) % 4
			for (int coveredDir = dir, count = 0; count < 3; count++, coveredDir = (coveredDir + 1) % 4) {
				y = original_y;
				x = original_x;

				while (true) {
					y += dy[coveredDir];
					x += dx[coveredDir];
					if (y < 0 || y >= n || x < 0 || x >= m || map[y][x] == 6) {
						break;
					}
					if (map[y][x] == 0) {
						watchedArea++;
						map[y][x] = 7;
					}
				}
			}

			simulate(idx + 1, blindSpot - watchedArea);

			if (watchedArea) {
				memcpy(map, tempMap, sizeof(map));
			}
		}
	}
	// cctv번호가 5번
	else {
		int watchedArea = 0;
		// 한 번에 모든 방향 탐색 가능
		for (int coveredDir = 0; coveredDir < 4; coveredDir++) {
			y = original_y;
			x = original_x;

			while (true) {
				y += dy[coveredDir];
				x += dx[coveredDir];
				if (y < 0 || y >= n || x < 0 || x >= m || map[y][x] == 6) {
					break;
				}
				if (map[y][x] == 0) {
					watchedArea++;
					map[y][x] = 7;
				}
			}
		}

		simulate(idx + 1, blindSpot - watchedArea);

		if (watchedArea) {
			memcpy(map, tempMap, sizeof(map));
		}
	}
	return;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;

	// spot은 맵 상태를 받음
	int spot;
	// blindSpot은 사각지대 개수
	int blindSpot = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> spot;
			// 0이면 사각지대
			if (spot == 0) {
				blindSpot++;
			}
			// 6이면 벽이므로 그냥 넘어감
			else if (spot == 6);
			// 1~5이면 cctv이므로 cctv 벡터에 삽입
			else {
				cctv.push_back({ i, j });
			}
			map[i][j] = spot;
		}
	}

	simulate(0, blindSpot);
	cout << minBlindSpot;
}