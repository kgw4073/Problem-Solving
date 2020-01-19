#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int dp[101][101];
int item[101];
const int inf = 987654321;

int main() {
	int n, m, r, t;

	cin >> n >> m >> r;

	for (int i = 1; i <= n; i++) {
		cin >> t;
		item[i] = t;
		for (int j = 0; j < 101; j++) {
			dp[i][j] = inf;
		}
		dp[i][i] = 0;
	}

	for (int i = 0; i < r; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		dp[a][b] = min(dp[a][b], l);
		dp[b][a] = min(dp[b][a], l);
	}

	int maxItems = 0;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			int temp_max = 0;
			for (int j = 1; j <= n; j++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
				if (dp[i][j] <= m) {
					temp_max += item[j];
				}
			}
			maxItems = max(temp_max, maxItems);
		}
	}

	cout << maxItems;
}