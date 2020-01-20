#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
int map[20][20];

// 최댓값을 저장
int answer = 0;

// 오른쪽, 왼쪽, 아래쪽, 위쪽
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

// 탐색 완료된 맵을 인자로 받아와서 answer를 갱신함
void renew(int map[][20]) {
	int check_max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			answer = max(answer, map[i][j]);
		}
	}
}

// dir과 map을 받아와서 dir에 따라 칸들을 움직임
void move(int dir, int map[][20]) {
	// 오른쪽
	if (dir == 0) {
		// 각 행에 대해서
		for (int i = 0; i < n; i++) {
			// vec에는 각 행에 대해서 이동시킨 결과를 차례대로 저장
			vector<int> vec;
			// pushflag는 숫자가 합쳐져도 되는 지를 판단
			bool pushflag = false;
			// 오른쪽에 있는 숫자들 먼저 오른쪽으로 이동시킴
			for (int j = n - 1; j >= 0; j--) {
				// map에 뭔가 있을 때
				if (map[i][j]) {
					// vec이 비어있다면 처음 숫자가 나타난 것
					if (vec.empty()) {
						// vec에 넣고 난 후, 같은 숫자가 들어오면 합쳐질 수 있으므로 flag 세팅
						vec.push_back(map[i][j]);
						pushflag = true;
					}
					// 한 번이라도 숫자가 나왔었다면
					else {
						// vec에 마지막 원소와 현재 map에 있는 숫자가 같을 때
						if (vec.back() == map[i][j]) {
							// 아직 합쳐지지 않은 것이었다면 합침
							if (pushflag) {
								vec.pop_back();
								vec.push_back(2 * map[i][j]);
								pushflag = false;
							}
							// 이미 합쳐진 것이면 그냥 vec에 담고 flag 세팅
							else {
								vec.push_back(map[i][j]);
								pushflag = true;
							}
						}
						// 숫자 다르면 그냥 vec에 담고 flag 세팅
						else {
							vec.push_back(map[i][j]);
							pushflag = true;
						}
					}
				}
			}
			// map 한 줄 갱신. vec에 담겨있는 대로 오른쪽부터 차례대로 저장한다.
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

	// 왼쪽. 위의 주석에 담은 논리 구조와 완전히 동일
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
			// map 한 줄 바꿈
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
	// 아래쪽
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
			// map 한 줄 바꿈
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
	// 위쪽
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
			// map 한 줄 바꿈
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
	// 5번 움직였으면
	if (depth == 5) {
		// 최댓값 찾아주고 끝
		renew(map);
		return;
	}
	// 네 방향 모두 탐색
	for (int dir = 0; dir < 4; dir++) {
		// map을 바꾸면 안됨. 현재 map에서 한 방향으로 움직인 map을 넘겨야 하므로 temp 생성
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