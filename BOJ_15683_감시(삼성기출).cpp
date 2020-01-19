#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// �繫���� ���ο� ���� ũ�Ⱑ n, m
int n, m;
// 8*8�� �ִ��̹Ƿ� �簢������ �ּڰ��� �켱 100���� ����
int minBlindSpot = 100;

// map�� tempMap�� ����Ͽ� dfs�κ��� ���ϵ� �� map�� ����
int map[8][8];

// ���� �迭
//	 3
// 2 + 0
//   1
int dy[] = { 0, 1, 0, -1 };
int dx[] = { 1, 0, -1, 0 };

// cctv ��ǥ�� ���� ����
vector<pair<int, int>> cctv;

// brute forcing���� ��� cctv�� �˻�
/*
	idx�� ���� Ž���ϰ� �ִ� cctv��ȣ
	blindSpot�� ���� �� ���¿����� �簢���� ����
*/
void simulate(int idx, int blindSpot) {
	// cctv �ε����� ������ ���������� Ʈ���� leaf node�� ������ ��
	if (idx == cctv.size()) {
		if (minBlindSpot > blindSpot) {
			minBlindSpot = blindSpot;
		}
		return;
	}

	// cctv�� ���� ��ǥ�� ����
	int original_y = cctv[idx].first;
	int original_x = cctv[idx].second;

	// cctv�� ����
	int cctvNo = map[original_y][original_x];

	/// y, x�� cctv�� �����ϴ� �繫�� �ε���
	int y, x;

	int tempMap[8][8];
	// dfs�κ��� ���Ͻ� �� ������ ���� ����.
	memcpy(tempMap, map, sizeof(map));

	// 1���� ���� �� ���⸸ Ž�� �����ϹǷ� �� ���� ��� Ž��
	if (cctvNo == 1) {
		for (int dir = 0; dir < 4; dir++) {
			int watchedArea = 0;
			y = original_y;
			x = original_x;

			// ���� ������ ������
			while (true) {
				y += dy[dir];
				x += dx[dir];

				// �繫���� ����ų� ���� ������ Ż��
				if (y < 0 || y >= n || x < 0 || x >= m || map[y][x] == 6) {
					break;
				}
				// ���� ������ ���̸� watchedArea������Ű�� ĭ ���¸� 7�� �ٲ�
				if (map[y][x] == 0) {
					watchedArea++;
					map[y][x] = 7;
				}
			}

			// ���� �簢���뿡�� ���� ������ ���� ���� Ž��
			simulate(idx + 1, blindSpot - watchedArea);

			// �� ���°� �ϳ��� �ٲ������ �� ����
			if (watchedArea) {
				memcpy(map, tempMap, sizeof(map));
			}
		}
	}
	// cctv��ȣ�� 2���̸�
	else if (cctvNo == 2) {
		// cctv�� �� ���� ������ ��� ���� Ž�� ����
		for (int dir = 0; dir < 2; dir++) {
			int watchedArea = 0;

			// coveredDir�� �� ���� Ŀ�� ������ ����
			// �� ���� �� ������ Ŀ�� �����ϹǷ� count�� 2�� �Ǳ� ������ Ž��
			// �� ���� �ݴ� ������� Ž�� �����ϹǷ� (coveredDir + 2) % 4
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
	// cctv�� 3���̸�
	else if (cctvNo == 3) {
		// �� �� ���� �� ��� �ٸ� ������ Ž���ϰ� ��
		for (int dir = 0; dir < 4; dir++) {
			int watchedArea = 0;

			// 90�� �������� �� ���� Ŀ�� �����ϹǷ�
			// count < 2�����̰�, coveredDir�� (coveredDir + 1) % 4
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
	// cctvNo�� 4���̸�
	else if (cctvNo == 4) {
		// �� �� ���� ������ �ٸ� ������ Ž��
		for (int dir = 0; dir < 4; dir++) {
			int watchedArea = 0;
			// �� ���� �� ������ Ž�� �����ϴ�.
			// count < 3�����̰�, coveredDir = (coveredDir + 1) % 4
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
	// cctv��ȣ�� 5��
	else {
		int watchedArea = 0;
		// �� ���� ��� ���� Ž�� ����
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

	// spot�� �� ���¸� ����
	int spot;
	// blindSpot�� �簢���� ����
	int blindSpot = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> spot;
			// 0�̸� �簢����
			if (spot == 0) {
				blindSpot++;
			}
			// 6�̸� ���̹Ƿ� �׳� �Ѿ
			else if (spot == 6);
			// 1~5�̸� cctv�̹Ƿ� cctv ���Ϳ� ����
			else {
				cctv.push_back({ i, j });
			}
			map[i][j] = spot;
		}
	}

	simulate(0, blindSpot);
	cout << minBlindSpot;
}