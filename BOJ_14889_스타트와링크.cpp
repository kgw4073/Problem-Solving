#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, members;
int ablity[20][20];
bool first_team_check[20];
int answer = 2e9;

vector<int> first_team, second_team;

// first_team과 second_team이 각각 n/2명으로 주어졌을 때 팀의 능력치를 계산하는 함수.
// n/2를 teamate라고 두었으니 경우의 수는 조합수 teamate C 2 가 됨

int team_ability_calculate(vector<int> &team) {
	int abilities = 0;
	for (int i = 0; i < team.size() - 1; i++) {
		for (int j = i + 1; j < team.size(); j++) {
			abilities += ablity[team[i]][team[j]];
			abilities += ablity[team[j]][team[i]];
		}
	}
	return abilities;
}

// dfs 순회를 이용하여 모든 경우의 수 트리 탐색
void dfs(int index, int depth) {
	// depth가 n/2에 도달하면 능력치 계산
	if (depth == members) {
		int second_team_ability = 0;
		// 첫 번째 팀이 아니면 second_team에다가 인덱스 저장
		for (int i = 0; i < n; i++) {
			if (!first_team_check[i]) {
				second_team.push_back(i);
			}
		}
		
		// 각 팀의 능력치 계산 후 차이 중 가장 작은 것을 answer에 저장
		int abilitiesOfFirst = team_ability_calculate(first_team);
		int abilitiesOfSecond = team_ability_calculate(second_team);
		answer = min(answer, abs(abilitiesOfSecond - abilitiesOfFirst));
		
		// second 반드시 clear해주어야 함.
		second_team.clear();
		return;
	}

	// 백트래킹으로 first_team 벡터와 first_team_check에 정보 저장
	for (int i = index + 1; i < n; i++) {
		if (!first_team_check[i]) {
			first_team_check[i] = true;
			first_team.push_back(i);
			dfs(i, depth + 1);
			first_team.pop_back();
			first_team_check[i] = false;
		}
	}
}
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> ablity[i][j];
		}
	}
	// 팀원 수는 n / 2
	members = n / 2;
	
	// 백트래킹과 완전탐색으로 점수 계산
	dfs(-1, 0);
	cout << answer;
}