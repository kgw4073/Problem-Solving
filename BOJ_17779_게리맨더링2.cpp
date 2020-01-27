#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using pii = pair<int, int>;
// 1330

int n;
int map[21][21];
int gu[21][21];

int offset[2];
int top = 0;
int maxOffset[2];

pii north, west, east, south;
int answer = 2e9;
int popCounts = 0;

int calculate() {
	int populations[6] = { 0, };
	populations[5] = popCounts;
	int counter = 1;
	memset(gu, 0, sizeof(gu));
	// 1번
	for (int i = north.first, flag = 1; i < west.first; i++, flag++) {
		for (int j = 1; j <= north.second - flag; j++) {
			populations[counter] += map[i][j];
			gu[i][j] = counter;
		}
	}
	for (int i = 1; i < north.first; i++) {
		for (int j = 1; j <= north.second; j++) {
			populations[counter] += map[i][j];
			gu[i][j] = counter;
		}
	}
	populations[5] -= populations[counter];
	counter++;
	//2번
	for (int i = north.first, flag = 1; i <= east.first; i++, flag++) {
		for (int j = north.second + flag; j <= n; j++) {
			populations[counter] += map[i][j];
			gu[i][j] = counter;

		}
	}
	for (int i = 1; i < north.first; i++) {
		for (int j = north.second + 1; j <= n; j++) {
			populations[counter] += map[i][j];
			gu[i][j] = counter;

		}
	}
	populations[5] -= populations[counter];
	counter++;
	//3번
	for (int i = west.first, flag = 0; i <= south.first; i++, flag++) {
		for (int j = 1; j < west.second + flag; j++) {
			populations[counter] += map[i][j];
			gu[i][j] = counter;

		}
	}
	for (int i = south.first + 1; i <= n; i++) {
		for (int j = 1; j < south.second; j++) {
			populations[counter] += map[i][j];
			gu[i][j] = counter;

		}
	}
	populations[5] -= populations[counter];
	counter++;
	//4번
	for (int i = east.first + 1, flag = 0; i <= south.first; i++, flag++) {
		for (int j = n; j >= east.second - flag; j--) {
			populations[counter] += map[i][j];
			gu[i][j] = counter;

		}
	}
	for (int i = south.first + 1; i <= n; i++) {
		for (int j = south.second; j <= n; j++) {
			populations[counter] += map[i][j];
			gu[i][j] = counter;

		}
	}
	populations[5] -= populations[counter];
	int mn = 2e9, mx = 0;
	for (int i = 1; i <= 5; i++) {
		mx = max(mx, populations[i]);
		mn = min(mn, populations[i]);
	}
	return mx - mn;
}
void solve(int y, int x, int depth) {
	if (depth == 2) {
		north = { y, x };
		west = { y + offset[0], x - offset[0] };
		east = { y + offset[1], x + offset[1] };
		south = { y + offset[0] + offset[1], x - offset[0] + offset[1] };
		if (west.first > n || west.second < 1 || east.first > n || east.second > n || south.first > n) {
			return;
		}
		answer = min(answer, calculate());
		return;
	}
	for (int i = 1; i < maxOffset[depth]; i++) {
		offset[top++] = i;
		solve(y, x, depth + 1);
		offset[--top] = 0;
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			popCounts += map[i][j];
		}
	}

	for (int i = 1; i <= n - 2; i++) {
		for (int j = 2; j <= n - 1; j++) {
			maxOffset[0] = j, maxOffset[1] = n - j + 1;
			solve(i, j, 0);
		}
	}
	cout << answer;
}