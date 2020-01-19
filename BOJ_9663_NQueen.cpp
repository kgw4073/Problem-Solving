#include <iostream>

// dfs���� ���� Ž���ϰ� �ִ� '��'�� �����ϱ� ������ ����� row ��ȣ�� ����
int usedRow[16];
// n�� ũ��, counter�� ���� �� �ִ� ����� ��
int n, counter;

using namespace std;

void dfs(int col) {
	/*
		���� ���� �����ϸ� col�� n-1�ε� �� n-1��° ������ ������ ���� �ϳ� �־
		�� �࿡ ���� dfs�� �� �� �� ���� col �� n�� �ȴ�.
		��, ���� ������ �� ���� ��찡 ������
	*/
	if (col == n) {
		counter++;
		return;
	}
	// disabled�� ���� Ž���ϰ� �ִ� col���� ���� �� �ִ� �� ��ȣ�� �ִ����� ����
	bool disabled[16];
	memset(disabled, 0, sizeof(disabled));

	// 0������ �ٷ� �� col���� ����ߴ� row��ȣ�� ����, ���� col���� ����� �� �ִ� row�� ������
	for (int i = 0; i < col; i++) {
		// col������ i��° ������ ����� �� ��ȣ�� j
		int j = usedRow[i];
		disabled[j] = true;

		// up�� down�� �ǹ��ϴ� �ٴ� i���� j�࿡ �ִ� ����, col������ ���� ���ϰ� �ϴ� �� ��ȣ��
		int up = j + i - col;
		int down = j - i + col;

		// ü�� �� �ȿ� ������ ���� col�� ���ؼ�, �ش� ���� ��� �Ұ���
		if (0 <= up && up < n) {
			disabled[up] = true;
		}
		if (0 <= down && down < n) {
			disabled[down] = true;
		}
	}

	// ���� col���� ��� ���� Ž���ϴµ�
	for (int i= 0; i < n; i++) {
		// �ش� ���� ��� ������ ��(������ ���� �����ϴ� ���� �ƴ� ��)�̶��
		// ���� col�� ���ؼ� ����� �� ��ȣ�� i�̹Ƿ� usedRow[col] = i�� �ΰ� ���� col�� ��.
		if (!disabled[i]) {
			usedRow[col] = i;
			dfs(col + 1);
			// ���� �̾����� ������ ��� Ž���ϰ� ���ƿ��� ���� ���� �࿡�� ���� ����
			usedRow[col] = -1;
		}
	}
}
int main() {
	cin >> n;
	dfs(0);
	cout << counter;
}