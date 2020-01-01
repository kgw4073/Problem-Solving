#include <iostream>
#include <vector>

using namespace std;

int m, n, holeCount;

bool check(int i, int j, vector<vector<int>> & map, vector<vector<int>> & rotatedKey, vector<vector<int>> & lock) {
	// match되어야 하는 구멍
	int shouldMatched = holeCount;

	// rowStart, rowEnd, colStart, colEnd는 rotatedKey와 map이 접하는 부분
	int rowStart = (i < m) ? m : i;
	int rowEnd = (i + n - 1 >= 2 * m) ? 2 * m - 1 : i + n - 1;
	int colStart = (j < m) ? m : j;
	int colEnd = (j + n - 1 >= 2 * m) ? 2 * m - 1 : j + n - 1;

	// 접하는 부분을 탐색
	for (int k = rowStart; k <= rowEnd; k++) {
		for (int l = colStart; l <= colEnd; l++) {
			// map에 구멍이 있고, key가 채워져있으면 채워야 하는 구멍 하나 줄어듦.
			if (!map[k][l] && rotatedKey[k - i][l - j]) {
				shouldMatched--;
				continue;
			}
			else if (map[k][l] && !rotatedKey[k - i][l - j]) {
				continue;
			}
			return false;
		}
	}
	if (!shouldMatched) {
		return true;
	}
	else return false;

}
void rotate(vector<vector<int>> & rotatedKey, vector<vector<int>> & key) {
	// rotatedKey는 key를 시계방향으로 90도 회전
	for (int i = 0; i < rotatedKey.size(); i++) {
		for (int j = 0; j < rotatedKey.size(); j++) {
			rotatedKey[i][j] = key[rotatedKey.size() - 1 - j][i];
		}
	}

	// key에다가 rotatedKey를 복사
	for (int i = 0; i < key.size(); i++) {
		for (int j = 0; j < key.size(); j++) {
			key[i][j] = rotatedKey[i][j];
		}
	}
}
bool solution(vector<vector<int>> & key, vector<vector<int>> & lock) {
	// map은 lock을 중앙에 위치시키며 3배로 늘려서 인덱스 조정을 편하게하기 위함.
	vector<vector<int>> map;
	vector<vector<int>> rotatedKey;

	rotatedKey.resize(key.size());
	for (int i = 0; i < rotatedKey.size(); i++) {
		rotatedKey[i].resize(rotatedKey.size());
	}

	m = lock.size();
	n = rotatedKey.size();

	// lock을 3배로 늘려서 중앙에 위치 시킨다.
	map.resize(lock.size() * 3);
	for (int i = 0; i < map.size(); i++) {
		map[i].resize(map.size(), 0);
	}
	for (int i = 0; i < lock.size(); i++) {
		for (int j = 0; j < lock.size(); j++) {
			map[i + lock.size()][j + lock.size()] = lock[i][j];
		}
	}

	// key를 rotatedKey로 복사
	for (int i = 0; i < key.size(); i++) {
		for (int j = 0; j < key.size(); j++) {
			rotatedKey[i][j] = key[i][j];
		}
	}

	// 회전시키며 전부 탐색
	for (int dir = 0; dir < 4; dir++) {
		for (int i = m - n + 1; i < 2 * m; i++) {
			for (int j = m - n + 1; j < 2 * m; j++) {
				// 열쇠가 map 구멍에 들어맞는 지 체크
				if (check(i, j, map, rotatedKey, lock)) {
					return true;
				}
			}
		}
		rotate(rotatedKey, key);
	}
	// 전부 탐색한 결과 match가 없으면 false
	return false;
}

int main() {
	vector<vector<int>> key = { {0, 0, 0}, {1, 0, 0}, {0, 1, 1} };
	vector<vector<int>> lock = { {1, 1, 1}, {1, 1, 0}, {1, 0, 1} };
	holeCount = 2;
	cout << solution(key, lock) << endl;
}