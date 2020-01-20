#include <iostream>
#include <algorithm>

using namespace std;
// sequence 담는 배열
int a[11];
// + - * / 순으로 연산자 개수
int op[4];

int n;
int max_val = -2e9;
int min_val = 2e9;

// 완전 탐색 트리
void solve(int depth, int plus, int minus, int multiply, int divide, int num) {
	// +-*/ 모두 0개면 넘어온 값을 가지고 max_val, min_val을 갱신
	if (!plus && !minus && !multiply && !divide) {
		max_val = max(max_val, num);
		min_val = min(min_val, num);
		return;
	}
	// 1개 이상 남았을 때만 각 연산자를 사용할 수 있다.
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
	// 첫 번째 원소 a[0]은 주어진다고 가정하기에 depth를 1부터 시작한다.
	solve(1, op[0], op[1], op[2], op[3], a[0]);
	cout << max_val << '\n' << min_val;
}