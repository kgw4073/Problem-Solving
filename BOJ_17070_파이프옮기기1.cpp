#include <iostream>
#include <cstring>
using namespace std;
int n;
int map[17][17], dp[17][17][3];

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
	memset(dp, 0, sizeof(dp));
	dp[1][2][0] = 1;
	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			if (y <= n && x + 1 <= n && !map[y][x + 1]) {
				dp[y][x + 1][0] += dp[y][x][0] + dp[y][x][1];
			}
			if (y + 1 <= n && x <= n && !map[y + 1][x]) {
				dp[y + 1][x][2] += dp[y][x][1] + dp[y][x][2];
			}
			if (y <= n - 1 && x <= n - 1 && !map[y][x + 1] && !map[y + 1][x] && !map[y + 1][x + 1]) {
				dp[y + 1][x + 1][1] += dp[y][x][0] + dp[y][x][1] + dp[y][x][2];
			}
		}
	}
	cout << dp[n][n][0] + dp[n][n][1] + dp[n][n][2];
}