#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
int map[20][20];

// �ִ��� ����
int answer = 0;

// ������, ����, �Ʒ���, ����
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

// Ž�� �Ϸ�� ���� ���ڷ� �޾ƿͼ� answer�� ������
void renew(int map[][20]) {
	int check_max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			answer = max(answer, map[i][j]);
		}
	}
}

// dir�� map�� �޾ƿͼ� dir�� ���� ĭ���� ������
void move(int dir, int map[][20]) {
	// ������
	if (dir == 0) {
		// �� �࿡ ���ؼ�
		for (int i = 0; i < n; i++) {
			// vec���� �� �࿡ ���ؼ� �̵���Ų ����� ���ʴ�� ����
			vector<int> vec;
			// pushflag�� ���ڰ� �������� �Ǵ� ���� �Ǵ�
			bool pushflag = false;
			// �����ʿ� �ִ� ���ڵ� ���� ���������� �̵���Ŵ
			for (int j = n - 1; j >= 0; j--) {
				// map�� ���� ���� ��
				if (map[i][j]) {
					// vec�� ����ִٸ� ó�� ���ڰ� ��Ÿ�� ��
					if (vec.empty()) {
						// vec�� �ְ� �� ��, ���� ���ڰ� ������ ������ �� �����Ƿ� flag ����
						vec.push_back(map[i][j]);
						pushflag = true;
					}
					// �� ���̶� ���ڰ� ���Ծ��ٸ�
					else {
						// vec�� ������ ���ҿ� ���� map�� �ִ� ���ڰ� ���� ��
						if (vec.back() == map[i][j]) {
							// ���� �������� ���� ���̾��ٸ� ��ħ
							if (pushflag) {
								vec.pop_back();
								vec.push_back(2 * map[i][j]);
								pushflag = false;
							}
							// �̹� ������ ���̸� �׳� vec�� ��� flag ����
							else {
								vec.push_back(map[i][j]);
								pushflag = true;
							}
						}
						// ���� �ٸ��� �׳� vec�� ��� flag ����
						else {
							vec.push_back(map[i][j]);
							pushflag = true;
						}
					}
				}
			}
			// map �� �� ����. vec�� ����ִ� ��� �����ʺ��� ���ʴ�� �����Ѵ�.
			for (int j = n - 1, vecIndex = 0; j >= 0; j--) {
				if (vecIndex != vec.size()) {
					map[i][j] = vec[vecIndex++];
				}
				else {
					map[i][j] = 0;
				}
			}

		}
	}

	// ����. ���� �ּ��� ���� �� ������ ������ ����
	else if (dir == 1) {
		for (int i = 0; i < n; i++) {
			vector<int> vec;
			bool pushflag = false;
			for (int j = 0; j < n; j++) {
				if (map[i][j]) {
					if (vec.empty()) {
						vec.push_back(map[i][j]);
						pushflag = true;
					}
					else {
						if (vec.back() == map[i][j]) {
							if (pushflag) {
								vec.pop_back();
								vec.push_back(2 * map[i][j]);
								pushflag = false;
							}
							else {
								vec.push_back(map[i][j]);
								pushflag = true;
							}
						}
						else {
							vec.push_back(map[i][j]);
							pushflag = true;
						}
					}
				}
			}
			// map �� �� �ٲ�
			for (int j = 0, vecIndex = 0; j < n; j++) {
				if (vecIndex != vec.size()) {
					map[i][j] = vec[vecIndex++];
				}
				else {
					map[i][j] = 0;
				}
			}

		}
	}
	// �Ʒ���
	else if (dir == 2) {
		for (int j = n - 1; j >= 0; j--) {
			vector<int> vec;
			bool pushflag = false;
			for (int i = n - 1; i >= 0; i--) {
				if (map[i][j]) {
					if (vec.empty()) {
						vec.push_back(map[i][j]);
						pushflag = true;
					}
					else {
						if (vec.back() == map[i][j]) {
							if (pushflag) {
								vec.pop_back();
								vec.push_back(2 * map[i][j]);
								pushflag = false;
							}
							else {
								vec.push_back(map[i][j]);
								pushflag = true;
							}
						}
						else {
							vec.push_back(map[i][j]);
							pushflag = true;
						}
					}
				}
			}
			// map �� �� �ٲ�
			for (int i = n - 1, vecIndex = 0; i >= 0; i--) {
				if (vecIndex != vec.size()) {
					map[i][j] = vec[vecIndex++];
				}
				else {
					map[i][j] = 0;
				}
			}

		}
	}
	// ����
	else {
		for (int j = 0; j < n; j++) {
			vector<int> vec;
			bool pushflag = false;
			for (int i = 0; i < n; i++) {
				if (map[i][j]) {
					if (vec.empty()) {
						vec.push_back(map[i][j]);
						pushflag = true;
					}
					else {
						if (vec.back() == map[i][j]) {
							if (pushflag) {
								vec.pop_back();
								vec.push_back(2 * map[i][j]);
								pushflag = false;
							}
							else {
								vec.push_back(map[i][j]);
								pushflag = true;
							}
						}
						else {
							vec.push_back(map[i][j]);
							pushflag = true;
						}
					}
				}
			}
			// map �� �� �ٲ�
			for (int i = 0, vecIndex = 0; i < n; i++) {
				if (vecIndex != vec.size()) {
					map[i][j] = vec[vecIndex++];
				}
				else {
					map[i][j] = 0;
				}
			}

		}
	}
}
void solve(int depth, int map[][20]) {
	// 5�� ����������
	if (depth == 5) {
		// �ִ� ã���ְ� ��
		renew(map);
		return;
	}
	// �� ���� ��� Ž��
	for (int dir = 0; dir < 4; dir++) {
		// map�� �ٲٸ� �ȵ�. ���� map���� �� �������� ������ map�� �Ѱܾ� �ϹǷ� temp ����
		int temp[20][20];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				temp[i][j] = map[i][j];
			}
		}
		move(dir, temp);
		solve(depth + 1, temp);
	}
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	solve(0, map);
	cout << answer;
}