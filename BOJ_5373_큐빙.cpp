#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int t;

int map[12][9];
string s;
void init() {
	for (int j = 3; j < 6; j++) {
		for (int i = 0; i < 3; i++) {
			map[i][j] = 3;
		}
		for (int i = 6; i < 9; i++) {
			map[i][j] = 4;
		}
		for (int i = 9; i < 12; i++) {
			map[i][j] = 2;
		}
	}
	for (int i = 3; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			map[i][j] = 5;
		}
		for (int j = 3; j < 6; j++) {
			map[i][j] = 1;
		}
		for (int j = 6; j < 9; j++) {
			map[i][j] = 6;
		}
	}
}

void pointer_shift(int* queue[]) {
	int value[12];
	for (int i = 3; i < 12; i++) {
		value[i] = *queue[i - 3];
	}
	value[0] = *queue[9], value[1] = *queue[10], value[2] = *queue[11];
	for (int i = 0; i < 12; i++) {
		*queue[i] = value[i];
	}
}
const int starty[] = { -1, 3, 9, 0, 6, 3, 3 };
const int startx[] = { -1, 3, 3, 3, 3, 0, 6 };
void rotate(int plane, int dir) {
	int temp[3][3];
	int* queue[12] = { 0, };
	if (dir == 1) {

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				temp[i][j] = map[2 - j + starty[plane]][i + startx[plane]];
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				map[i + starty[plane]][j + startx[plane]] = temp[i][j];
			}
		}
		switch (plane) {
		case 1:

			queue[0] = &map[2][3], queue[1] = &map[2][4], queue[2] = &map[2][5];
			queue[3] = &map[3][6], queue[4] = &map[4][6], queue[5] = &map[5][6];
			queue[6] = &map[6][5], queue[7] = &map[6][4], queue[8] = &map[6][3];
			queue[9] = &map[5][2], queue[10] = &map[4][2], queue[11] = &map[3][2];
			break;

		case 2:
			queue[0] = &map[8][3], queue[1] = &map[8][4], queue[2] = &map[8][5];
			queue[3] = &map[5][8], queue[4] = &map[4][8], queue[5] = &map[3][8];
			queue[6] = &map[0][5], queue[7] = &map[0][4], queue[8] = &map[0][3];
			queue[9] = &map[3][0], queue[10] = &map[4][0], queue[11] = &map[5][0];

			break;

		case 3:
			queue[0] = &map[3][8], queue[1] = &map[3][7], queue[2] = &map[3][6];
			queue[3] = &map[3][5], queue[4] = &map[3][4], queue[5] = &map[3][3];
			queue[6] = &map[3][2], queue[7] = &map[3][1], queue[8] = &map[3][0];
			queue[9] = &map[11][3], queue[10] = &map[11][4], queue[11] = &map[11][5];
			break;

		case 4:
			queue[0] = &map[5][0], queue[1] = &map[5][1], queue[2] = &map[5][2];
			queue[3] = &map[5][3], queue[4] = &map[5][4], queue[5] = &map[5][5];
			queue[6] = &map[5][6], queue[7] = &map[5][7], queue[8] = &map[5][8];
			queue[9] = &map[9][5], queue[10] = &map[9][4], queue[11] = &map[9][3];
			break;

		case 5:
			queue[0] = &map[0][3], queue[1] = &map[1][3], queue[2] = &map[2][3];
			queue[3] = &map[3][3], queue[4] = &map[4][3], queue[5] = &map[5][3];
			queue[6] = &map[6][3], queue[7] = &map[7][3], queue[8] = &map[8][3];
			queue[9] = &map[9][3], queue[10] = &map[10][3], queue[11] = &map[11][3];
			break;

		case 6:
			queue[0] = &map[11][5], queue[1] = &map[10][5], queue[2] = &map[9][5];
			queue[3] = &map[8][5], queue[4] = &map[7][5], queue[5] = &map[6][5];
			queue[6] = &map[5][5], queue[7] = &map[4][5], queue[8] = &map[3][5];
			queue[9] = &map[2][5], queue[10] = &map[1][5], queue[11] = &map[0][5];
			break;
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				temp[i][j] = map[j + starty[plane]][2 - i + startx[plane]];
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				map[i + starty[plane]][j + startx[plane]] = temp[i][j];
			}
		}
		switch (plane) {
		case 1:

			queue[11] = &map[2][3], queue[10] = &map[2][4], queue[9] = &map[2][5];
			queue[8] = &map[3][6], queue[7] = &map[4][6], queue[6] = &map[5][6];
			queue[5] = &map[6][5], queue[4] = &map[6][4], queue[3] = &map[6][3];
			queue[2] = &map[5][2], queue[1] = &map[4][2], queue[0] = &map[3][2];
			break;

		case 2:
			queue[11] = &map[8][3], queue[10] = &map[8][4], queue[9] = &map[8][5];
			queue[8] = &map[5][8], queue[7] = &map[4][8], queue[6] = &map[3][8];
			queue[5] = &map[0][5], queue[4] = &map[0][4], queue[3] = &map[0][3];
			queue[2] = &map[3][0], queue[1] = &map[4][0], queue[0] = &map[5][0];

			break;

		case 3:
			queue[11] = &map[3][8], queue[10] = &map[3][7], queue[9] = &map[3][6];
			queue[8] = &map[3][5], queue[7] = &map[3][4], queue[6] = &map[3][3];
			queue[5] = &map[3][2], queue[4] = &map[3][1], queue[3] = &map[3][0];
			queue[2] = &map[11][3], queue[1] = &map[11][4], queue[0] = &map[11][5];
			break;

		case 4:
			queue[11] = &map[5][0], queue[10] = &map[5][1], queue[9] = &map[5][2];
			queue[8] = &map[5][3], queue[7] = &map[5][4], queue[6] = &map[5][5];
			queue[5] = &map[5][6], queue[4] = &map[5][7], queue[3] = &map[5][8];
			queue[2] = &map[9][5], queue[1] = &map[9][4], queue[0] = &map[9][3];
			break;

		case 5:
			queue[11] = &map[0][3], queue[10] = &map[1][3], queue[9] = &map[2][3];
			queue[8] = &map[3][3], queue[7] = &map[4][3], queue[6] = &map[5][3];
			queue[5] = &map[6][3], queue[4] = &map[7][3], queue[3] = &map[8][3];
			queue[2] = &map[9][3], queue[1] = &map[10][3], queue[0] = &map[11][3];
			break;

		case 6:
			queue[11] = &map[11][5], queue[10] = &map[10][5], queue[9] = &map[9][5];
			queue[8] = &map[8][5], queue[7] = &map[7][5], queue[6] = &map[6][5];
			queue[5] = &map[5][5], queue[4] = &map[4][5], queue[3] = &map[3][5];
			queue[2] = &map[2][5], queue[1] = &map[1][5], queue[0] = &map[0][5];
			break;
		}
	}
	pointer_shift(queue);
}

int main() {
	cin >> t;
	while (t--) {
		init();
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int plane, dir;
			cin >> s;
			switch (s[0]) {
			case 'U':
				plane = 1;
				break;
			case 'D':
				plane = 2;
				break;
			case 'F':
				plane = 4;
				break;
			case 'B':
				plane = 3;
				break;
			case 'L':
				plane = 5;
				break;
			case 'R':
				plane = 6;
				break;
			}
			if (s[1] == '-') dir = -1;
			else dir = 1;

			rotate(plane, dir);
		}
		for (int i = 3; i < 6; i++) {
			for (int j = 3; j < 6; j++) {
				switch (map[i][j]) {
				case 1:
					cout << 'w';
					break;
				case 2:
					cout << 'y';
					break;
				case 3:
					cout << 'o';
					break;
				case 4:
					cout << 'r';
					break;
				case 5:
					cout << 'g';
					break;
				case 6:
					cout << 'b';
					break;
				}
			}
			cout << '\n';
		}
	}
}