#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
//16 28

vector<int> graph[2551];
int value[2551];
bool visited[2551];

int n, m, t;

void dfs(int cur, int target, int& cnt) {
	for (int next : graph[cur]) {
		if (!visited[next] && value[next] == target && value[next] != 0) {
			visited[next] = true;
			value[next] = 0;
			cnt++;
			dfs(next, target, cnt);
		}
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			int val; cin >> val;
			int rowMajor = m * i + j;
			if (i < n) {
				graph[rowMajor].push_back(rowMajor + m);
				graph[rowMajor + m].push_back(rowMajor);
			}
			if (j <= m - 2) {
				graph[rowMajor].push_back(rowMajor + 1);
				graph[rowMajor + 1].push_back(rowMajor);
			}
			
			else {
				graph[rowMajor].push_back(rowMajor - j);
				graph[rowMajor - j].push_back(rowMajor);
			}
			value[rowMajor] = val;
		}
	}
	int endian = n * m + m;
	for (int i = 0; i < t; i++) {
		int x, d, k;
		cin >> x >> d >> k;
		if (d == 1) {
			d = 0;
			k = m - k;
			k %= m;
		}

		int step = x * m;
		for (int i = step; i <= endian; i += step) {
			int pArr[51];
			for (int j = k; j < m; j++) {
				pArr[j] = value[i + j - k];
			}
			for (int j = 0; j < k; j++) {
				pArr[j] = value[i + m + j - k];
			}
			for (int j = 0; j < m; j++) {
				value[i + j] = pArr[j];
			}
		}
		memset(visited, 0, sizeof(visited));
		// flag는 하나라도 인접한 노드가 있는지 없는지 체크, 있으면 setting됨
		int s = 0, count = 0, flag = false;
		for (int i = m; i <= endian; i++) {
			if (visited[i] || value[i] == 0) continue;
			visited[i] = true;
			
			// 인접한 노드를 세는 변수
			int cnt = 0;

			dfs(i, value[i], cnt);

			// 하나라도 인접하면서 같은 노드 있으면 flag setting하고 시작점도 0으로 바꿔줌
			if (cnt >= 1) {
				flag = true; value[i] = 0;
			}
			else {
				count++;
				s += value[i];
			}
		}

		// 인접하면서 같은 수를 가진 노드가 하나도 없다면 조건에 따라 갱신
		if (!flag) {
			double avg = (double)s / count;
			for (int i = m; i <= endian; i++) {
				if (value[i] == 0) continue;
				else {
					if (avg < (double)value[i]) {
						value[i]--;
					}
					else if (avg > (double)value[i]) {
						value[i]++;
					}
				}
			}
		}
	}

	int sum = 0;
	for (int i = m; i <= endian; i++) {
		sum += value[i];
	}
	cout << sum;
}
