#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int n;
vector<int> ops;
vector<int> arr;
int numCounts, opCounts;


int answer = numeric_limits<int>::min();
inline int calculate(int cur, int flag, int next) {
	switch (flag) {
	case 1:
		return cur + next;
		break;

	case 2:
		return cur - next;
		break;

	case 3:
		return cur * next;
		break;
	}
}
void dfs(int eval, int idx) {
	if (idx >= opCounts) {
		answer = max(answer, eval);
		return;
	}
	int cur = calculate(eval, ops[idx], arr[idx + 1]);
	dfs(cur, idx + 1);
	if (idx < numCounts - 2) {
		int next = calculate(arr[idx + 1], ops[idx + 1], arr[idx + 2]);
		cur = calculate(eval, ops[idx], next);
		dfs(cur, idx + 2);
	}
}
int main() {
	cin >> n;
	string s;
	cin >> s;
	for (int i = 0; i < n; i++) {
		if ('0' <= s[i] && s[i] <= '9') {
			arr.push_back(s[i] - '0');
			numCounts++;
		}
		else {
			if (s[i] == '+') {
				ops.push_back(1);
			}
			else if (s[i] == '-') {
				ops.push_back(2);
			}
			else {
				ops.push_back(3);
			}
			opCounts++;
		}
	}
	dfs(arr[0], 0);
	cout << answer;
}

