#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
//13 39
using namespace std;

int n;
vector<int> graph[11];
int map[11][11];
int pops[11];
bool visited[11] = { false, };
const int inf = 2000000000;
int answer = inf;
vector<int> connected;
vector<int> secondVisit;
vector<int> firstSelect;


bool forback[11] = { false, };
void countcheck(int& count, int start) {
	connected.push_back(start);
	count++;
	visited[start] = true;

	for (auto v : graph[start]) {
		if (!visited[v]) {
			countcheck(count, v);
		}
	}
}
void firstDfs(int& ordering, int start) {
	ordering += pops[start];
	visited[start] = true;
	for (auto v : graph[start]) {
		if (!visited[v]) {
			firstDfs(ordering, v);
		}
	}
}
void secondDfs(int& ordering, int start, int& secondParts) {
	secondParts++;
	secondVisit.push_back(start);
	ordering += pops[start];
	visited[start] = true;
	for (auto v : graph[start]) {
		if (!visited[v]) {
			secondDfs(ordering, v, secondParts);
		}
	}
}

bool isConnected(vector<int>& vec) {

	bool visit[11] = { false, };
	visit[vec[0]] = true;
	queue<int> q;
	q.push(vec[0]);
	int cnt = vec.size() - 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (auto next : graph[cur]) {
			if (!visit[next]) {
				for (auto p : vec) {
					if (p == next) {
						visit[p] = true;
						q.push(p);
						cnt--;
					}
				}
			}
		}
	}
	if (!cnt) return true;
	return false;
}
void solve(int depth, int idx, int target, int& first) {
	if (depth == target) {
		if (!isConnected(firstSelect)) {
			
			return;
		}
		int second = 0, secondParts = 0;
		for (int i = 0; ; i++) {
			if (!visited[i]) {
				secondDfs(second, i, secondParts);
				break;
			}
		}
		if (secondParts == n - depth) {
			answer = min(answer, abs(first - second));
		}
		// º¹±Í
		for (auto p : secondVisit) {
			visited[p] = false;
		}
		secondVisit.clear();
		return;
	}
	else {
		for (int i = idx + 1; i < connected.size(); i++) {
			if (!visited[connected[i]]) {
				visited[connected[i]] = true;
				
				firstSelect.push_back(connected[i]);
				first += pops[connected[i]];
				solve(depth + 1, i, target, first);
				first -= pops[connected[i]];
				firstSelect.pop_back();
				visited[connected[i]] = false;
			}
		}
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> pops[i];
	}
	for (int u = 0; u < n; u++) {
		int t;
		cin >> t;
		for (int j = 0; j < t; j++) {
			int v;
			cin >> v;
			v--;
			graph[u].emplace_back(v);
			map[u][v] = 1;
		}
	}
	for (int start = 0; start < n; start++) {
		memset(visited, 0, sizeof(visited));
		int count = 0;
		connected.clear();
		countcheck(count, start);
		for (int target = 1; target < n; target++) {
			int first = 0, second = 0;
			memset(visited, 0, sizeof(visited));
			int secondParts = 0;
			if (count < target) {
				firstDfs(first, start);
				for (int i = 0; ; i++) {
					if (!visited[i]) {
						secondDfs(second, start, secondParts);
						break;
					}
				}
				if (secondParts == n - count) {
					answer = min(answer, abs(first - second));
				}
				break;
			}
			else {

				solve(0, -1, target, first);
			}
		}
	}
	if (answer == inf) {
		answer = -1;
	}
	cout << answer;
}