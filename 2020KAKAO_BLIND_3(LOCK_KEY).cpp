#include <iostream>
#include <vector>

using namespace std;

int m, n, holeCount;

bool check(int i, int j, vector<vector<int>> & map, vector<vector<int>> & rotatedKey, vector<vector<int>> & lock) {
	// match�Ǿ�� �ϴ� ����
	int shouldMatched = holeCount;

	// rowStart, rowEnd, colStart, colEnd�� rotatedKey�� map�� ���ϴ� �κ�
	int rowStart = (i < m) ? m : i;
	int rowEnd = (i + n - 1 >= 2 * m) ? 2 * m - 1 : i + n - 1;
	int colStart = (j < m) ? m : j;
	int colEnd = (j + n - 1 >= 2 * m) ? 2 * m - 1 : j + n - 1;

	// ���ϴ� �κ��� Ž��
	for (int k = rowStart; k <= rowEnd; k++) {
		for (int l = colStart; l <= colEnd; l++) {
			// map�� ������ �ְ�, key�� ä���������� ä���� �ϴ� ���� �ϳ� �پ��.
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
	// rotatedKey�� key�� �ð�������� 90�� ȸ��
	for (int i = 0; i < rotatedKey.size(); i++) {
		for (int j = 0; j < rotatedKey.size(); j++) {
			rotatedKey[i][j] = key[rotatedKey.size() - 1 - j][i];
		}
	}

	// key���ٰ� rotatedKey�� ����
	for (int i = 0; i < key.size(); i++) {
		for (int j = 0; j < key.size(); j++) {
			key[i][j] = rotatedKey[i][j];
		}
	}
}
bool solution(vector<vector<int>> & key, vector<vector<int>> & lock) {
	// map�� lock�� �߾ӿ� ��ġ��Ű�� 3��� �÷��� �ε��� ������ ���ϰ��ϱ� ����.
	vector<vector<int>> map;
	vector<vector<int>> rotatedKey;

	rotatedKey.resize(key.size());
	for (int i = 0; i < rotatedKey.size(); i++) {
		rotatedKey[i].resize(rotatedKey.size());
	}

	m = lock.size();
	n = rotatedKey.size();

	// lock�� 3��� �÷��� �߾ӿ� ��ġ ��Ų��.
	map.resize(lock.size() * 3);
	for (int i = 0; i < map.size(); i++) {
		map[i].resize(map.size(), 0);
	}
	for (int i = 0; i < lock.size(); i++) {
		for (int j = 0; j < lock.size(); j++) {
			map[i + lock.size()][j + lock.size()] = lock[i][j];
		}
	}

	// key�� rotatedKey�� ����
	for (int i = 0; i < key.size(); i++) {
		for (int j = 0; j < key.size(); j++) {
			rotatedKey[i][j] = key[i][j];
		}
	}

	// ȸ����Ű�� ���� Ž��
	for (int dir = 0; dir < 4; dir++) {
		for (int i = m - n + 1; i < 2 * m; i++) {
			for (int j = m - n + 1; j < 2 * m; j++) {
				// ���谡 map ���ۿ� ���´� �� üũ
				if (check(i, j, map, rotatedKey, lock)) {
					return true;
				}
			}
		}
		rotate(rotatedKey, key);
	}
	// ���� Ž���� ��� match�� ������ false
	return false;
}

int main() {
	vector<vector<int>> key = { {0, 0, 0}, {1, 0, 0}, {0, 1, 1} };
	vector<vector<int>> lock = { {1, 1, 1}, {1, 1, 0}, {1, 0, 1} };
	holeCount = 2;
	cout << solution(key, lock) << endl;
}