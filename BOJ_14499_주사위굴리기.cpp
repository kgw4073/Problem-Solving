#include <iostream>
#define SWAP(a, b) {int temp = a; a = b; b = temp;}

using namespace std;

int n, m, x, y, k;
int map[20][20];
int dice[4][3] = { 0, };
// 동 서 북 남
const int dy[] = { 0, 0, 0, -1, 1 };
const int dx[] = { 0, 1, -1, 0, 0 };

int main() {
	cin >> n >> m >> y >> x >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	while (k--) {
		int dir;
		cin >> dir;
		if (y + dy[dir] < 0 || y + dy[dir] >= n || x + dx[dir] < 0 || x + dx[dir] >= m) {
			continue;
		}
		switch (dir) {
		//동쪽으로 굴림
		case 1:
			SWAP(dice[1][1], dice[1][2]);
			SWAP(dice[1][0], dice[1][2]);
			SWAP(dice[3][1], dice[1][2]);
			break;
		// 서쪽으로 굴림
		case 2:
			SWAP(dice[1][0], dice[1][1]);
			SWAP(dice[1][0], dice[3][1]);
			SWAP(dice[3][1], dice[1][2]);
			break;
		// 북쪽으로 굴림
		case 3:
			SWAP(dice[0][1], dice[3][1]);
			SWAP(dice[1][1], dice[3][1]);
			SWAP(dice[2][1], dice[3][1]);
			break;
		// 남쪽으로 굴림
		case 4:
			SWAP(dice[0][1], dice[1][1]);
			SWAP(dice[1][1], dice[2][1]);
			SWAP(dice[2][1], dice[3][1]);
			break;
		}
		// dice 배열 (1, 1)이 지도와 맞닿는 면이고 (3, 1)이 윗면
		y += dy[dir];
		x += dx[dir];
		if (map[y][x] == 0) {
			map[y][x] = dice[1][1];
		}
		else {
			dice[1][1] = map[y][x];
			map[y][x] = 0;
		}
		cout << dice[3][1] << '\n';
	}
}