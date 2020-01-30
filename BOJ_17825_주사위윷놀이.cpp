#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int endPoint = 21;

// 32개의 노드들을 그래프로 연결
vector<int> graph[33];

// score는 32개의 노드들 위에 쓰여있는 점수
int score[33];

// state는 해당 인덱스 노드 위에 말이 있는지 없는지
int state[33];

// 0 ~ 3번 말이 현재 어느 위치에 있는지
int makerNode[4];

// 주사위 결과
int dice[10];

// 0 ~ 3번 말들이 끝났는지 안끝났는지
bool finished[4] = { false, };

// 답
int answer = 0;

void solve(int depth, int state[], int total) {
	if (depth == 10) {
		answer = max(answer, total);
		return;
	}
	// 0 ~ 3번 말 탐색
	for (int i = 0; i < 4; i++) {
		// 끝난 말이면 탐색 안해
		if (finished[i]) {
			continue;
		}

		int currentNode = makerNode[i];
		int nextNode;
		// 현재 노드가 5, 10, 15이면 파란 선 따라 감
		if (currentNode == 5 || currentNode == 10 || currentNode == 15) {
			int count = dice[depth] - 1;
			nextNode = graph[currentNode][1];
			while (count--) {
				nextNode = graph[nextNode][0];
			}
		}
		else {
			int count = dice[depth];
			nextNode = makerNode[i];
			while (count--) {
				nextNode = graph[nextNode][0];
			}
		}
		// 다음 노드가 끝점이어도 일단 탐색하고 다음 말로 넘어감
		if (nextNode == endPoint) {
			state[currentNode] = 0;
			state[nextNode] = 1;
			makerNode[i] = nextNode;
			finished[i] = true;
			solve(depth + 1, state, total + score[nextNode]);
			finished[i] = false;
			state[nextNode] = 0;
			state[currentNode] = 1;
			makerNode[i] = currentNode;
			continue;
		}
		// 다음 노드에 뭐 있으면 탐색 안함
		if (state[nextNode]) {
			continue;
		}
		// 다음 노드에 아무 말도 없고 끝점도 아니어도 탐색
		makerNode[i] = nextNode;
		state[currentNode] = 0;
		state[nextNode] = 1;
		solve(depth + 1, state, total + score[nextNode]);
		state[nextNode] = 0;
		state[currentNode] = 1;
		makerNode[i] = currentNode;
	}
}
int main() {

	// 이 밑에 코드는 직접 그래프 번호 매겨서 연결
	for (int i = 0; i <= 20; i++) {
		graph[i].emplace_back(i + 1);
		score[i] = i * 2;
	}
	graph[5].emplace_back(22);
	score[22] = 13;
	graph[22].emplace_back(23);
	score[23] = 16;
	graph[23].emplace_back(24);
	score[24] = 19;
	graph[24].emplace_back(25);
	score[25] = 25;

	graph[25].emplace_back(26);
	score[26] = 30;
	graph[26].emplace_back(27);
	score[27] = 35;
	graph[27].emplace_back(20);


	graph[10].emplace_back(28);
	score[28] = 22;
	graph[28].emplace_back(29);
	score[29] = 24;
	graph[29].emplace_back(25);

	graph[15].emplace_back(30);
	score[30] = 28;
	graph[30].emplace_back(31);
	score[31] = 27;
	graph[31].emplace_back(32);
	score[32] = 26;
	graph[32].emplace_back(25);
	graph[21].emplace_back(21);
	for (int i = 0; i < 10; i++) {
		cin >> dice[i];
	}
	solve(0, state, 0);
	cout << answer;
}