#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

bitset<8> w[5];

void bitrotate(int number, bool dir) {
	// �ð����, ������ shift
	if (dir) {
		// shift�ÿ� �帣�� ���� flow
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
	// ��ϰ� ��ġ�� �� �κп� ���� ���� �� �ִ��� ������ �Ǵ�
	bool rotatable[5] = { false, };
	for (int i = 1; i <= 3; i++) {
		if (w[i].test(5) ^ w[i + 1].test(1)) {
			rotatable[i] = true;
		}
	}
	bitrotate(number, dir);
	// 1�� Ȥ�� 4���� ���� ���������� �����ٰ� �߰��� ���� �� ������ �ٷ� Ż��.
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

	// 2�� Ȥ�� 3���� ���� �ٷ� ���� �پ��ִ� 1�� Ȥ�� 4���� ���� ���� �� �ִ��� üũ �� �����ش�.
	// �׸��� ������ 1, 4���� ���������� ���� �͵��� �����ٰ� ���� �� ������ Ż��
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