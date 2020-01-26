#include <iostream>

using namespace std;

int n, temp, exponent;
char map[3100][6200];
const char star[3][6] = {
{' ', ' ', '*', ' ', ' ', ' '},
{' ', '*', ' ', '*', ' ', ' '},
{'*', '*', '*', '*', '*', ' '}
};
void solve(int depth, int y, int x, int n) {
	if (depth == exponent) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				map[y + i][x + j] = star[i][j];
			}
		}
		return;
	}
	solve(depth + 1, y + n / 2, x, n / 2);
	solve(depth + 1, y, x + n / 2, n / 2);
	solve(depth + 1, y + n / 2, x + n, n / 2);

}
int main() {
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;
	int temp = n;
	temp /= 3;
	exponent = 1;
	while (temp / 2) {
		temp /= 2;
		exponent++;
	}
	solve(1, 0, 0, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2 * n; j++) {
			if (map[i][j]) cout << map[i][j];
			else cout << " ";
		}
		cout << '\n';
	}
}