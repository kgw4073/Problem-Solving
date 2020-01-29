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
	// 각각 자리에 수명 z년, 개수 1만큼 집어넣음.
	for (int i = 0; i < m; i++) {
		cin >> y >> x >> z;
		map[--y][--x].emplace_back(z, 1);
	}
	while (k--) {
		// 봄 여름
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int soil = 0;
				// vector의 특성때문에 끝에서부터 탐색
				for (int k = map[i][j].size() - 1; k >= 0; k--) {
					int age = map[i][j][k].first;
					int cnt = map[i][j][k].second;
					int mul = age * cnt;
					// age 살인 나무들이 전부 양분을 먹을 수 있을 때
					if (state[i][j] >= mul) {
						state[i][j] -= mul;
						map[i][j][k].first++;
					}
					// 다는 못 먹을 때 일부만 먹이고 나머지 죽임
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
				// 겨울에 양분을 주지만 어차피 지금 미리줘도 상관없음
				state[i][j] += soil + fertilizer[i][j];
			}
		}
		// 가을 번식
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				// 같은 나이에 있는 나무들
				for (auto& same_age_trees : map[y][x]) {
					// 5로 나누어 떨어질 때
					if (!(same_age_trees.first % 5)) {
						int cnt = same_age_trees.second;
						for (int dir = 0; dir < 8; dir++) {
							int ny = y + dy[dir], nx = x + dx[dir];
							if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
							// 아무것도 없거나 있는데 마지막에 있는 나무 나이가 1이 아닐 때는 cnt만큼 나이 1인 나무 번식
							if (!map[ny][nx].size() || map[ny][nx].back().first != 1) {
								map[ny][nx].emplace_back(1, cnt);
							}
							// 아니면 마지막에 있는 나이 1인 나무들 cnt만큼 증가시킴
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