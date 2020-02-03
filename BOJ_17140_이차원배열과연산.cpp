#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
using pii = pair<int, int>;

priority_queue<pii, vector<pii>, greater<> > pq;

bool operator<(const pii& a, const pii& b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	return a.first < b.first;
}
int r, c, k;
int map[100][100];
int time;
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> r >> c >> k;
	r--; c--;
	int row = 3, col = 3;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int num;
			cin >> num;
			map[i][j] = num;
		}
	}
	int count[101];
	set<int> s;
	for (time = 0; time <= 100; time++) {
		if (map[r][c] == k) break;
		int i, j;
		int tempRow = 0, tempCol = 0;

		if (row >= col) {
			// r연산
			for (i = 0; i < row; i++) {
				s.clear();
				memset(count, 0, sizeof(count));
				for (j = 0; j < 100; j++) {
					if (map[i][j] == 0) {
						continue;
					}
					s.insert(map[i][j]);
					count[map[i][j]]++;
				}

				for (auto num : s) {
					pq.emplace(count[num], num);
				}
				for (j = 0; j < 100; j += 2) {
					if (pq.empty()) break;
					int num = pq.top().second, count = pq.top().first;
					map[i][j] = num, map[i][j + 1] = count;
					pq.pop();
				}
				tempCol = max(tempCol, j);

				for (; j < 100; j++) {
					map[i][j] = 0;
				}
				while (!pq.empty()) pq.pop();
			}
			col = tempCol;
		}
		else {
			// c연산
			for (i = 0; i < col; i++) {
				s.clear();
				memset(count, 0, sizeof(count));

				for (j = 0; j < 100; j++) {
					if (map[j][i] == 0) {
						continue;
					}
					s.insert(map[j][i]);
					count[map[j][i]]++;
				}

				for (auto num : s) {
					pq.emplace(count[num], num);
				}
				for (j = 0; j < 100; j += 2) {
					if (pq.empty()) break;
					int num = pq.top().second, count = pq.top().first;
					map[j][i] = num, map[j + 1][i] = count;
					pq.pop();
				}
				tempRow = max(tempRow, j);
				for (; j < 100; j++) {
					map[j][i] = 0;
				}

				while (!pq.empty()) pq.pop();
			}
			row = tempRow;
		}
	}
	if (time > 100) time = -1;
	cout << time;
}