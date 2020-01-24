#include <iostream>
#include <vector>

using namespace std;

using pii = pair<int, int>;

int n, map[101][101];

const int dy[] = { 0, -1, 0, 1 };
const int dx[] = { 1, 0, -1, 0 };

void draw(int y, int x, int dir, int target) {

	vector<pii> vec;
	int end_y = y + dy[dir], end_x = x + dx[dir];
	map[end_y][end_x] = 1;
	vec.emplace_back(y, x);
	vec.emplace_back(end_y, end_x);

	int depth = 0;
	// target 번호까지 depth를 증가시키며 끝 점에 이어붙임
	// 회전시키는 기준은 end_y, end_x이다.
	while (depth < target) {
		int vecsz = vec.size();

		// 기존에 있던 점들을 end_y, end_x를 기준으로 시계방향으로 회전시킴
		for (int i = vecsz - 2; i >= 0; i--) {
			int ydist = end_y - vec[i].first;
			int xdist = end_x - vec[i].second;
			vec.emplace_back(end_y - xdist , end_x + ydist);
			map[end_y - xdist][end_x + ydist] = 1;
		}
		end_y = vec.at(vec.size() - 1).first;
		end_x = vec.at(vec.size() - 1).second;
		depth++;
	}
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y, dir, g;
		cin >> x >> y >> dir >> g;
		map[y][x] = 1;
		draw(y, x, dir, g);
	}
	int answer = 0;
	for (int i = 0; i <= 99; i++) {
		for (int j = 0; j <= 99; j++) {
			if (map[i][j] && map[i][j + 1] && map[i + 1][j] && map[i + 1][j + 1]) {
				answer++;
			}
		}
	}
	cout << answer;
}