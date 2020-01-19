#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
// �ش� �׽�Ʈ ���̽��� �ھ� ����
int N;

// ���μ��� ���� ����
int map[12][12];

// �ʿ��� �ھ�κ��� ���� line�� ����Ǿ� �ִ��� �ƴ��� ��Ÿ��
int lined[12][12];

// �ھ� �ε��� ���� ����
vector<pair<int, int>> vec;

// �ھ��� �� ����
int coreNum;
// minimum line, max core ����
int mnLine = 0, mxCore = 0;

int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, 1, 0, -1 };

/*
idx : vec���� Ž���ϰ� �ִ� �ھ� �ε���,
line : ���� �׾��� �ִ� line ����
core : ���� ����� core ����
depth : Ž�� Ʈ�� ����
*/
void solution(int idx, int line, int core, int depth) {
	// ���� ����� max core�� ���� ����� core�� ������ ������ ���� ��� �ھ �������� ���� �� �պ��� ū ���
	// Ž���� �ʿ� ����
	if (mxCore > core + (coreNum - depth)) return;

	// Ž�� Ʈ���� ������ �����ߴٸ�, ��, ��� �ھ Ž���ߴٸ�
	if (depth == coreNum) {
		// ���ǿ� ���� ����
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

	// tempLined�� ���� ����� line�� ���¸� �����ϱ� ���� (dfs ���Ͻ� ���� ������ ����)
	int tempLined[12][12] = { 0, };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tempLined[i][j] = lined[i][j];
		}
	}

	// �� ���� Ž��
	for (int dir = 0; dir < 4; dir++) {
		// flag�� ������ ���� �����Ѱ��� ��Ÿ��
		bool flag = true;
		
		int y = vec[idx].first;
		int x = vec[idx].second;

		int lineCounter = 0;
		// �����ڸ����� ������ ����.
		while (1) {
			y += dy[dir];
			x += dx[dir];
			
			// ������ �����ߴٸ� break
			if (x < 0 || x >= N || y < 0 || y >= N) {
				break;
			}
			// �߰��� ���� �� �ϴ� ��Ȳ�̸� flag�� false�� �����ϰ� break
			if (map[y][x] || lined[y][x]) {
				flag = false;
				break;
			}
			// ����� ���¸� ������Ʈ
			lined[y][x] = 1;
			lineCounter++;
		}
		// �����ڸ����� ���� �����ϸ� Ʈ���� �ڽ����� �� Ž��(dfs)
		if (flag) {
			solution(idx + 1, line + lineCounter, core + 1, depth + 1);
		}
		
		// ����Ǿ� �־��ٸ� tempLined�� �̿��Ͽ� ���� ���� ����(dfs���� ���ϵ��� ��)
		if (lineCounter) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					lined[i][j] = tempLined[i][j];
				}
			}
		}
	}
	// �ʼ�����. �̹� �� ���� ���ϰ� ���� core�� Ž������ ���� ����ؾ� ��.
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