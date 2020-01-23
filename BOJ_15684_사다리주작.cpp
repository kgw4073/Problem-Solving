#include <iostream>
#include <algorithm>

using namespace std;

int n, m, h;
int map[32][11];
int rmap[32][11];

const int inf = 2e9;
int answer = inf;

void solve(int start, int y, int x, int add, int rmap[][11], int map[][11]) {
	// 모든 세로 선을 다 탐색하고 도달했다면 answer를 갱신
	if (start == n + 1) {
		answer = min(answer, add);
		return;
	}
	// 범위를 벗어났거나 원래 시작했던 세로 선에 도달하지 못했다면 실패
	if (x <= 0 || x > n || (y >= h + 1 && x != start)) return;
	// 가로 끝에 내려왔는데 시작한 세로 선이라면 다음 세로 선을 탐색
	if (y >= h + 1 && x == start) {
		solve(start + 1, 1, start + 1, add, rmap, map);
		return;
	}
	// 오른쪽 가로 선 있다면 타고 내려감
	if (map[y][x]) {
		solve(start, y + 1, x + 1, add, rmap, map);
	}
	// 왼쪽 가로 선 있다면 타고 내려감
	if (rmap[y][x]) {
		solve(start, y + 1, x - 1, add, rmap, map);
	}
	// 둘 다 없으면
	if (!map[y][x] && !rmap[y][x]) {
		// 현재 추가된 사다리가 2이하일 때만 하나 더 놓을 수 있음
		if (add <= 2) {
			if (!map[y][x + 1]) {
				map[y][x] = 1;
				rmap[y][x + 1] = 1;
				solve(start, y + 1, x + 1, add + 1, rmap, map);
				rmap[y][x + 1] = 0;
				map[y][x] = 0;
			}
			if (!rmap[y][x - 1]) {
				map[y][x - 1] = 1;
				rmap[y][x] = 1;
				solve(start, y + 1, x - 1, add + 1, rmap, map);
				map[y][x - 1] = 0;
				rmap[y][x] = 0;
			}
		}
		// 그냥 내려가 봄
		solve(start, y + 1, x, add, rmap, map);
	}
}
int main() {
	cin >> n >> m >> h;
	// 오른쪽으로 가는 선과 왼쪽으로 가는 선을 map과 rmap으로 저장
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		map[u][v] = 1;
		rmap[u][v + 1] = 1;
	}
	solve(1, 1, 1, 0, rmap, map);
	if (answer == inf) {
		cout << -1;
	}
	else {
		cout << answer;
	}
}