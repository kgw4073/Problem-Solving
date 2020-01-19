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

	// row, col�� Ž���ؾ� �ϴ� ��� ������
	int col = m - 8;
	int row = n - 8;
	
	for (int i = 0; i <= row; i++) {
		for (int j = 0; j <= col; j++) {
			// color ��� ��.
			for (int color = 0; color < 2; color++) {

				// �ٽ� ĥ�ؾ� �ϴ� ĭ�� ����
				int reColoringSum = 0;
				// should : �� �ڸ��� ĥ���� �־�߸� �ϴ� ����
				int should = color;
				// zigzag�� ü������ Ž���ؾ� ��.
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