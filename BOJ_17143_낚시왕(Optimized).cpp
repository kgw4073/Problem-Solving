#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <list>

using namespace std;
//1300
int R, C, M;

const int dy[] = { -1, 1, 0, 0 };
const int dx[] = { 0, 0, 1, -1 };

int map[100][100];
struct Shark {
	int r, c, s, d, z;
	bool alive;
	Shark(int _r, int _c, int _s, int _d, int _z) : r(_r), c(_c), s(_s), d(_d), z(_z) {
		alive = true;
		if (d <= 1) {
			s %= (2 * R - 2);
		}
		else {
			s %= (2 * C - 2);
		}
	}
};
vector<Shark> vec;

void xchange(int& newpos, int& dir, int maxpos) {
	while (newpos < 0 || newpos > maxpos) {
		if (newpos < 0) {
			newpos = newpos * -1;
			dir = (dir == 2) ? 3 : 2;
		}
		else {
			newpos = 2 * maxpos - newpos;
			dir = (dir == 2) ? 3 : 2;
		}
	}
}

void ychange(int& newpos, int& dir, int maxpos) {
	while (newpos<0 || newpos>maxpos) {
		if (newpos < 0) {
			newpos = newpos * -1;
			dir = (dir == 0) ? 1 : 0;
		}
		else {
			newpos = 2 * maxpos - newpos;
			dir = (dir == 0) ? 1 : 0;
		}
	}
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> R >> C >> M;
	int answer = 0;
	memset(map, -1, sizeof(map));
	for (int i = 0; i < M; i++) {
		int y, x, s, d, z;
		cin >> y >> x >> s >> d >> z;
		y--; x--; d--;
		map[y][x] = i;
		vec.emplace_back(y, x, s, d, z);
	}
	// 낚시왕 이동
	for (int x = 0; x < C; x++) {
		// 상어 잡기
		for (int y = 0; y < R; y++) {
			if (map[y][x] != -1) {
				vec[map[y][x]].alive = false;
				answer += vec[map[y][x]].z;
				break;
			}
		}

		memset(map, -1, sizeof(map));
		// 상어 대이동
		for (int i = 0; i < M; i++) {
			if (vec[i].alive) {
				int ny = vec[i].r + dy[vec[i].d] * vec[i].s;
				int nx = vec[i].c + dx[vec[i].d] * vec[i].s;
				if (nx < 0 || nx >= C) {
					xchange(nx, vec[i].d, C - 1);
				}
				if (ny < 0 || ny >= R) {
					ychange(ny, vec[i].d, R - 1);
				}
				vec[i].r = ny;
				vec[i].c = nx;
				if (map[ny][nx] == -1) {
					map[ny][nx] = i;
				}
				else {
					if (vec[map[ny][nx]].z < vec[i].z) {
						vec[map[ny][nx]].alive = false;
						map[ny][nx] = i;
					}
					else {
						vec[i].alive = false;
					}
				}
			}
		}
	}
	cout << answer;

}