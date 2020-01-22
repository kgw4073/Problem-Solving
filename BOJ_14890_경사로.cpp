#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <cstring>
#include <bitset>
#include <string>
#include <vector>
#include <cmath>
#include <deque>
#include <stack>
#include <queue>
#include <list>
#include <set>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;

int N, L;
int map[100][100];
int answer = 0;

// Tranpose
void rotate() {
	int temp[100][100];
	memcpy(temp, map, sizeof(temp));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = temp[j][i];
		}
	}
}

// 행으로 탐색
void simulate() {
	int ramp[100] = { false, };
	for (int i = 0; i < N; i++) {
		memset(ramp, 0, sizeof(ramp));
		bool fail = false;

		for (int k = 0; k < N - 1; ) {
			// 오른쪽 아래로 경사
			if (map[i][k] - map[i][k + 1] == 1) {
				int p, prev = map[i][k + 1];
				for (p = 1; p <= L; p++) {
					if (prev == map[i][k + p]) {
						ramp[k + p] = true;
						continue;
					}
					fail = true; break;
				}
				if (fail) break;
				else k += L;
			}
			else if (map[i][k] - map[i][k + 1] == -1) {
				int start = k, cnt = 0;
				int prev = map[i][start];

				for (; cnt < L; cnt++, start--) {
					if (start < 0 || ramp[start] || prev != map[i][start]) {
						fail = true; break;
					}
					ramp[start] = true;
				}
				if (fail) break;
				else k++;
			}
			else if (map[i][k] == map[i][k + 1]) {
				k++;
				continue;
			}
			else {
				fail = true; break;
			}
		}

		if (!fail) {
			answer++;
		}
	}
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	simulate();
	rotate();
	simulate();
	cout << answer;
}