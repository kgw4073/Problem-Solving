#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int map[500][500];
int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	int score, maxScore = 0;
	// Brute forcing

	// 0�� 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m - 4; j++) {
			score = 0;
			for (int k = 0; k < 4; k++) {
				score += map[i][j + k];
			}
			maxScore = max(maxScore, score);
		}
	}
	for (int i = 0; i <= n - 4; i++) {
		for (int j = 0; j < m; j++) {
			score = 0;
			for (int k = 0; k < 4; k++) {
				score += map[i + k][j];
			}
			maxScore = max(maxScore, score);
		}
	}

	// 1�� �����
	for (int i = 0; i <= n - 2; i++) {
		for (int j = 0; j <= m - 2; j++) {
			score = 0;
			score += (map[i][j] + map[i][j + 1] + map[i + 1][j] + map[i + 1][j + 1]);
			maxScore = max(maxScore, score);
		}
	}

	// 2�� ��Ȳ��
	for (int i = 0; i <= n - 3; i++) {
		for (int j = 0; j <= m - 2; j++) {
			score = 0;
			score += (map[i][j] + map[i + 1][j] + map[i + 2][j]);
			score = max(score + map[i + 2][j + 1], score + map[i][j + 1]);
			maxScore = max(maxScore, score);
		}
	}

	for (int i = 0; i <= n - 3; i++) {
		for (int j = 0; j <= m - 2; j++) {
			score = 0;
			score += (map[i][j + 1] + map[i + 1][j + 1] + map[i + 2][j + 1]);
			score = max(score + map[i][j], score + map[i + 2][j]);
			maxScore = max(maxScore, score);
		}
	}

	for (int i = 0; i <= n - 2; i++) {
		for (int j = 0; j <= m - 3; j++) {
			score = 0;
			score += (map[i][j] + map[i][j + 1] + map[i][j + 2]);
			score = max(score + map[i + 1][j], score + map[i + 1][j + 2]);
			maxScore = max(maxScore, score);
		}
	}
	for (int i = 0; i <= n - 2; i++) {
		for (int j = 0; j <= m - 3; j++) {
			score = 0;
			score += (map[i + 1][j] + map[i + 1][j + 1] + map[i + 1][j + 2]);
			score = max(score + map[i][j], score + map[i][j + 2]);
			maxScore = max(maxScore, score);
		}
	}


	// 3�� �ʷϻ�
	for (int i = 0; i <= n - 3; i++) {
		for (int j = 0; j <= m - 2; j++) {
			score = 0;
			score += (map[i + 1][j] + map[i + 1][j + 1]);
			score = max(score + map[i][j] + map[i + 2][j + 1], score + map[i][j + 1] + map[i + 2][j]);
			maxScore = max(maxScore, score);
		}
	}
	for (int i = 0; i <= n - 2; i++) {
		for (int j = 0; j <= m - 3; j++) {
			score = 0;
			score += (map[i][j + 1] + map[i + 1][j + 1]);
			score = max(score + map[i][j] + map[i + 1][j + 2], score + map[i + 1][j] + map[i][j + 2]);
			maxScore = max(maxScore, score);
		}
	}

	// 4�� �����
	// ��
	for (int i = 0; i <= n - 2; i++) {
		for (int j = 0; j <= m - 3; j++) {
			score = 0;
			score += (map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i + 1][j + 1]);
			maxScore = max(maxScore, score);
		}
	}
	// ��
	for (int i = 0; i <= n - 3; i++) {
		for (int j = 0; j <= m - 2; j++) {
			score = 0;
			score += (map[i + 1][j] + map[i][j + 1] + map[i + 1][j + 1] + map[i + 2][j + 1]);
			maxScore = max(maxScore, score);
		}
	}
	// ��
	for (int i = 0; i <= n - 2; i++) {
		for (int j = 0; j <= m - 3; j++) {
			score = 0;
			score += (map[i][j + 1] + map[i + 1][j] + map[i + 1][j + 1] + map[i + 1][j + 2]);
			maxScore = max(maxScore, score);
		}
	}
	// ��
	for (int i = 0; i <= n - 3; i++) {
		for (int j = 0; j <= m - 2; j++) {
			score = 0;
			score += (map[i][j] + map[i + 1][j] + map[i + 2][j] + map[i + 1][j + 1]);
			maxScore = max(maxScore, score);
		}
	}
	cout << maxScore;
}