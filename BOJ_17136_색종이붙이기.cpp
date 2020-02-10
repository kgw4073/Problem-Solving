#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

// 14 36
using namespace std;

int map[10][10];
int answer = 1000;
vector<pair<int, int>> vec;

__inline bool possible(int y, int x, int k) {
	if (y + k > 10 || x + k > 10) return false;

	for (int i = y; i < y + k; i++) {
		for (int j = x; j < x + k; j++) {
			if (map[i][j] != 7) {
				return false;
			}
		}
	}

	return true;
}


void solve(int idx, int count[]) {

	if (idx == vec.size()) {
		int s = 0;
		for (int i = 1; i <= 5; i++) {
			s += count[i];
		}
		answer = min(answer, 25 - s);
		return;
	}
	int y = vec[idx].first, x = vec[idx].second;
	if (map[y][x] == 7) {
		for (int k = 5; k; k--) {
			if (count[k] < 1) continue;
			if (possible(y, x, k)) {
				int temp[10][10];
				memcpy(temp, map, sizeof(temp));
				for (int i = y; i < y + k; i++) {
					for (int j = x; j < x + k; j++) {
						map[i][j] = k;
					}
				}
				count[k]--;
				solve(idx + 1, count);
				count[k]++;
				memcpy(map, temp, sizeof(map));
			}
		}

	}
	else {
		solve(idx + 1, count);
	}
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> map[i][j];
			if (map[i][j]) {
				map[i][j] = 7;
				vec.emplace_back(i, j);
			}
		}
	}
	int count[] = { 0, 5, 5, 5, 5, 5 };
	solve(0, count);
	if (answer == 1000) {
		answer = -1;
	}
	cout << answer;
}
