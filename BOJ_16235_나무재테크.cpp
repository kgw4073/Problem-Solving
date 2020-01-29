#include <iostream>
#include <vector>

using namespace std;

using pii = pair<int, int>;

int n, m, k, y, x, z;
int state[10][10];
int fertilizer[10][10];

vector<pii> map[10][10];

const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1 };
const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1 };

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> fertilizer[i][j];
			state[i][j] = 5;
		}
	}
	// ���� �ڸ��� ���� z��, ���� 1��ŭ �������.
	for (int i = 0; i < m; i++) {
		cin >> y >> x >> z;
		map[--y][--x].emplace_back(z, 1);
	}
	while (k--) {
		// �� ����
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int soil = 0;
				// vector�� Ư�������� ���������� Ž��
				for (int k = map[i][j].size() - 1; k >= 0; k--) {
					int age = map[i][j][k].first;
					int cnt = map[i][j][k].second;
					int mul = age * cnt;
					// age ���� �������� ���� ����� ���� �� ���� ��
					if (state[i][j] >= mul) {
						state[i][j] -= mul;
						map[i][j][k].first++;
					}
					// �ٴ� �� ���� �� �Ϻθ� ���̰� ������ ����
					else {
						int alive = state[i][j] / age;
						int dead = cnt - alive;
						soil += dead * (age / 2);
						if (alive == 0) {
							map[i][j].erase(map[i][j].begin() + k);
							continue;
						}
						state[i][j] -= alive * age;
						map[i][j][k].first++;
						map[i][j][k].second = alive;
					}
				}
				// �ܿ￡ ����� ������ ������ ���� �̸��൵ �������
				state[i][j] += soil + fertilizer[i][j];
			}
		}
		// ���� ����
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				// ���� ���̿� �ִ� ������
				for (auto& same_age_trees : map[y][x]) {
					// 5�� ������ ������ ��
					if (!(same_age_trees.first % 5)) {
						int cnt = same_age_trees.second;
						for (int dir = 0; dir < 8; dir++) {
							int ny = y + dy[dir], nx = x + dx[dir];
							if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
							// �ƹ��͵� ���ų� �ִµ� �������� �ִ� ���� ���̰� 1�� �ƴ� ���� cnt��ŭ ���� 1�� ���� ����
							if (!map[ny][nx].size() || map[ny][nx].back().first != 1) {
								map[ny][nx].emplace_back(1, cnt);
							}
							// �ƴϸ� �������� �ִ� ���� 1�� ������ cnt��ŭ ������Ŵ
							else {
								map[ny][nx].back().second += cnt;
							}
						}
					}
				}
			}
		}
	}
	int answer = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (auto trees : map[i][j]) {
				answer += trees.second;
			}
		}
	}
	cout << answer;
}