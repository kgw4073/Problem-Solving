#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
// 해당 테스트 케이스의 코어 개수
int N;

// 프로세서 매핑 상태
int map[12][12];

// 맵에서 코어로부터 나온 line이 연결되어 있는지 아닌지 나타냄
int lined[12][12];

// 코어 인덱스 저장 벡터
vector<pair<int, int>> vec;

// 코어의 총 개수
int coreNum;
// minimum line, max core 개수
int mnLine = 0, mxCore = 0;

int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, 1, 0, -1 };

/*
idx : vec에서 탐색하고 있는 코어 인덱스,
line : 현재 그어져 있는 line 개수
core : 현재 연결된 core 개수
depth : 탐색 트리 깊이
*/
void solution(int idx, int line, int core, int depth) {
	// 현재 저장된 max core가 지금 연결된 core의 개수와 앞으로 남은 모든 코어를 연결했을 때의 총 합보다 큰 경우
	// 탐색할 필요 없음
	if (mxCore > core + (coreNum - depth)) return;

	// 탐색 트리의 끝까지 도달했다면, 즉, 모든 코어를 탐색했다면
	if (depth == coreNum) {
		// 조건에 따라 갱신
		if (mxCore < core) {
			mxCore = core;
			mnLine = line;
		}
		else if (mxCore == core) {
			if (mnLine > line) {
				mnLine = line;
			}
		}
		return;
	}

	// tempLined는 현재 연결된 line의 상태를 복사하기 위함 (dfs 리턴시 상태 복구를 위함)
	int tempLined[12][12] = { 0, };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tempLined[i][j] = lined[i][j];
		}
	}

	// 네 방향 탐색
	for (int dir = 0; dir < 4; dir++) {
		// flag는 끝까지 연결 가능한가를 나타냄
		bool flag = true;
		
		int y = vec[idx].first;
		int x = vec[idx].second;

		int lineCounter = 0;
		// 가장자리까지 연결해 나감.
		while (1) {
			y += dy[dir];
			x += dx[dir];
			
			// 끝까지 도달했다면 break
			if (x < 0 || x >= N || y < 0 || y >= N) {
				break;
			}
			// 중간에 연결 못 하는 상황이면 flag를 false로 세팅하고 break
			if (map[y][x] || lined[y][x]) {
				flag = false;
				break;
			}
			// 연결된 상태를 업데이트
			lined[y][x] = 1;
			lineCounter++;
		}
		// 가장자리까지 연결 가능하면 트리의 자식으로 들어가 탐색(dfs)
		if (flag) {
			solution(idx + 1, line + lineCounter, core + 1, depth + 1);
		}
		
		// 연결되어 있었다면 tempLined를 이용하여 연결 상태 복구(dfs에서 리턴됐을 때)
		if (lineCounter) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					lined[i][j] = tempLined[i][j];
				}
			}
		}
	}
	// 필수적임. 이번 거 연결 안하고 다음 core로 탐색했을 때도 고려해야 함.
	solution(idx + 1, line, core, depth + 1);
	return;
}

int main() {
	int T;
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> T;

	for (int i = 1; i <= T; i++) {
		cin >> N;
		memset(map, 0, sizeof(map));
		memset(lined, 0, sizeof(lined));
		mxCore = 0;
		mnLine = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j]) {
					vec.push_back({ i, j });
				}
			}
		}
		coreNum = vec.size();
		solution(0, 0, 0, 0);
		cout << "#" << i << " " << mnLine << '\n';
		vec.clear();
	}
}