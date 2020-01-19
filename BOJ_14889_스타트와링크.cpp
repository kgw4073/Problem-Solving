#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, members;
int ablity[20][20];
bool first_team_check[20];
int answer = 2e9;

vector<int> first_team, second_team;

// first_team�� second_team�� ���� n/2������ �־����� �� ���� �ɷ�ġ�� ����ϴ� �Լ�.
// n/2�� teamate��� �ξ����� ����� ���� ���ռ� teamate C 2 �� ��

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

// dfs ��ȸ�� �̿��Ͽ� ��� ����� �� Ʈ�� Ž��
void dfs(int index, int depth) {
	// depth�� n/2�� �����ϸ� �ɷ�ġ ���
	if (depth == members) {
		int second_team_ability = 0;
		// ù ��° ���� �ƴϸ� second_team���ٰ� �ε��� ����
		for (int i = 0; i < n; i++) {
			if (!first_team_check[i]) {
				second_team.push_back(i);
			}
		}
		
		// �� ���� �ɷ�ġ ��� �� ���� �� ���� ���� ���� answer�� ����
		int abilitiesOfFirst = team_ability_calculate(first_team);
		int abilitiesOfSecond = team_ability_calculate(second_team);
		answer = min(answer, abs(abilitiesOfSecond - abilitiesOfFirst));
		
		// second �ݵ�� clear���־�� ��.
		second_team.clear();
		return;
	}

	// ��Ʈ��ŷ���� first_team ���Ϳ� first_team_check�� ���� ����
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
	// ���� ���� n / 2
	members = n / 2;
	
	// ��Ʈ��ŷ�� ����Ž������ ���� ���
	dfs(-1, 0);
	cout << answer;
}