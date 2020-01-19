#include <iostream>
#include <algorithm>

using namespace std;

int board[50][50];
int minimum = 2e9;

int main() {
	int n, m;
	char c;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> c;
			if (c == 'B') {
				board[i][j] = 0;
			}
			else {
				board[i][j] = 1;
			}
		}
	}

	// row, col은 탐색해야 하는 모든 시작점
	int col = m - 8;
	int row = n - 8;
	
	for (int i = 0; i <= row; i++) {
		for (int j = 0; j <= col; j++) {
			// color 흑과 백.
			for (int color = 0; color < 2; color++) {

				// 다시 칠해야 하는 칸의 개수
				int reColoringSum = 0;
				// should : 그 자리에 칠해져 있어야만 하는 색깔
				int should = color;
				// zigzag로 체스판을 탐색해야 함.
				for (int a = 0, zigzag = 0; a < 8; a++, zigzag++) {
					int y = i + a;
					if (!(zigzag % 2)) {
						for (int b = 0; b < 8; b++) {
							if (should != board[y][j + b]) {
								reColoringSum++;
							}
							if (should == 0) {
								should = 1;
							}
							else {
								should = 0;
							}
						}
					}
					else {
						for (int b = 7; b >= 0; b--) {
							if (should != board[y][j + b]) {
								reColoringSum++;
							}
							if (should == 0) {
								should = 1;
							}
							else {
								should = 0;
							}
						}
					}
				}
				minimum = min(reColoringSum, minimum);
			}
		}
	}
	cout << minimum;
}