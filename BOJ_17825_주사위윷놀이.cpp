#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int endPoint = 21;

// 32���� ������ �׷����� ����
vector<int> graph[33];

// score�� 32���� ���� ���� �����ִ� ����
int score[33];

// state�� �ش� �ε��� ��� ���� ���� �ִ��� ������
int state[33];

// 0 ~ 3�� ���� ���� ��� ��ġ�� �ִ���
int makerNode[4];

// �ֻ��� ���
int dice[10];

// 0 ~ 3�� ������ �������� �ȳ�������
bool finished[4] = { false, };

// ��
int answer = 0;

void solve(int depth, int state[], int total) {
	if (depth == 10) {
		answer = max(answer, total);
		return;
	}
	// 0 ~ 3�� �� Ž��
	for (int i = 0; i < 4; i++) {
		// ���� ���̸� Ž�� ����
		if (finished[i]) {
			continue;
		}

		int currentNode = makerNode[i];
		int nextNode;
		// ���� ��尡 5, 10, 15�̸� �Ķ� �� ���� ��
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
		// ���� ��尡 �����̾ �ϴ� Ž���ϰ� ���� ���� �Ѿ
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
		// ���� ��忡 �� ������ Ž�� ����
		if (state[nextNode]) {
			continue;
		}
		// ���� ��忡 �ƹ� ���� ���� ������ �ƴϾ Ž��
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

	// �� �ؿ� �ڵ�� ���� �׷��� ��ȣ �Űܼ� ����
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