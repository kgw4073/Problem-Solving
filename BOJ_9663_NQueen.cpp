#include <iostream>

// dfs에서 현재 탐색하고 있는 '열'에 도달하기 전까지 사용한 row 번호를 저장
int usedRow[16];
// n은 크기, counter는 놓을 수 있는 경우의 수
int n, counter;

using namespace std;

void dfs(int col) {
	/*
		열의 끝에 도달하면 col이 n-1인데 이 n-1번째 열에서 가능한 행이 하나 있어서
		그 행에 놓고 dfs를 한 번 더 들어가면 col 이 n이 된다.
		즉, 서로 공격할 수 없는 경우가 존재함
	*/
	if (col == n) {
		counter++;
		return;
	}
	// disabled는 지금 탐색하고 있는 col에서 놓을 수 있는 행 번호가 있는지를 저장
	bool disabled[16];
	memset(disabled, 0, sizeof(disabled));

	// 0번부터 바로 전 col까지 사용했던 row번호에 따라, 지금 col에서 사용할 수 있는 row가 정해짐
	for (int i = 0; i < col; i++) {
		// col이전의 i번째 열에서 사용한 행 번호가 j
		int j = usedRow[i];
		disabled[j] = true;

		// up과 down이 의미하는 바는 i열의 j행에 있는 퀸이, col열에서 놓지 못하게 하는 행 번호임
		int up = j + i - col;
		int down = j - i + col;

		// 체스 판 안에 있으면 지금 col에 대해서, 해당 행은 사용 불가임
		if (0 <= up && up < n) {
			disabled[up] = true;
		}
		if (0 <= down && down < n) {
			disabled[down] = true;
		}
	}

	// 현재 col에서 모든 행을 탐색하는데
	for (int i= 0; i < n; i++) {
		// 해당 행이 사용 가능한 곳(이전의 퀸이 공격하는 곳이 아닌 곳)이라면
		// 현재 col에 대해서 사용한 행 번호는 i이므로 usedRow[col] = i로 두고 다음 col로 들어감.
		if (!disabled[i]) {
			usedRow[col] = i;
			dfs(col + 1);
			// 다음 이어지는 열들을 모두 탐색하고 돌아왔을 때는 현재 행에서 퀸을 제거
			usedRow[col] = -1;
		}
	}
}
int main() {
	cin >> n;
	dfs(0);
	cout << counter;
}