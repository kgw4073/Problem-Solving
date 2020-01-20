#include <iostream>
#include <algorithm>

using namespace std;
// sequence ��� �迭
int a[11];
// + - * / ������ ������ ����
int op[4];

int n;
int max_val = -2e9;
int min_val = 2e9;

// ���� Ž�� Ʈ��
void solve(int depth, int plus, int minus, int multiply, int divide, int num) {
	// +-*/ ��� 0���� �Ѿ�� ���� ������ max_val, min_val�� ����
	if (!plus && !minus && !multiply && !divide) {
		max_val = max(max_val, num);
		min_val = min(min_val, num);
		return;
	}
	// 1�� �̻� ������ ���� �� �����ڸ� ����� �� �ִ�.
	if (plus >= 1) {
		solve(depth + 1, plus - 1, minus, multiply, divide, num + a[depth]);
	}
	if (minus >= 1) {
		solve(depth + 1, plus, minus - 1, multiply, divide, num - a[depth]);
	}
	if (multiply >= 1) {
		solve(depth + 1, plus, minus, multiply - 1, divide, num * a[depth]);
	}
	if (divide >= 1) {
		solve(depth + 1, plus, minus, multiply, divide - 1, num / a[depth]);
	}
}
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cin >> op[0] >> op[1] >> op[2] >> op[3];
	// ù ��° ���� a[0]�� �־����ٰ� �����ϱ⿡ depth�� 1���� �����Ѵ�.
	solve(1, op[0], op[1], op[2], op[3], a[0]);
	cout << max_val << '\n' << min_val;
}