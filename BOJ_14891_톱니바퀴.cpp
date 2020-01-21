#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

bitset<8> w[5];

void bitrotate(int number, bool dir) {
	// 시계방향, 오른쪽 shift
	if (dir) {
		// shift시에 흐르는 값이 flow
		int flow = (w[number].test(0) ? 1 : 0);
		w[number] >>= 1;
		w[number] |= (flow << 7);
	}
	else {
		int flow = (w[number].test(7) ? 1 : 0);
		w[number] <<= 1;
		w[number] |= flow;
	}
}

void rotate(int number, bool dir) {
	// 톱니가 겹치는 세 부분에 대해 돌릴 수 있는지 없는지 판단
	bool rotatable[5] = { false, };
	for (int i = 1; i <= 3; i++) {
		if (w[i].test(5) ^ w[i + 1].test(1)) {
			rotatable[i] = true;
		}
	}
	bitrotate(number, dir);
	// 1번 혹은 4번일 때는 끝에서부터 돌리다가 중간에 돌릴 수 없으면 바로 탈출.
	if (number == 1) {
		for (int i = 1; ; i++) {
			if (!rotatable[i]) break;
			dir = !dir;
			bitrotate(i + 1, dir);
		}
	}
	else if (number == 4) {
		for (int i = 3; ; i--) {
			if (!rotatable[i]) break;
			dir = !dir;
			bitrotate(i, dir);
		}
	}

	// 2번 혹은 3번일 때는 바로 옆에 붙어있는 1번 혹은 4번을 먼저 돌릴 수 있는지 체크 후 돌려준다.
	// 그리고 나서는 1, 4번과 마찬가지로 남은 것들을 돌리다가 돌릴 수 없으면 탈출
	else if (number == 2) {
		if (rotatable[1]) {
			bitrotate(1, !dir);
		}
		for (int i = 2; ; i++) {
			if (!rotatable[i]) break;
			dir = !dir;
			bitrotate(i + 1, dir);
		}
	}
	else {
		if (rotatable[3]) {
			bitrotate(4, !dir);
		}
		for (int i = 2; ; i--) {
			if (!rotatable[i]) break;
			dir = !dir;
			bitrotate(i, dir);
		}
	}
}
int main() {
	for (int i = 1; i <= 4; i++) {
		for (int j = 0; j < 8; j++) {
			char c;
			cin >> c;
			int bit = (c == '1' ? 1 : 0);
			w[i] |= (bit << (7 - j));
		}
	}

	int k, sum = 0;

	cin >> k;
	while (k--) {
		int number, d;
		cin >> number >> d;
		bool dir = (d == 1 ? true : false);
		rotate(number, dir);
		// for debuging
		/*
			cout << endl;
			cout << "number : " <<number << dir << "direction" << endl;
			for (int i = 1; i <= 4; i++) {
				cout << w[i] << endl;
			}
		*/
	}

	for (int i = 1; i <= 4; i++) {
		if (w[i].test(7)) {
			sum += (int)pow(2, i - 1);
		}
	}
	cout << sum;
}