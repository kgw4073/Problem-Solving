#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
int n, m;

vector<int> graph[100001];
int indegree[100001], dfsn[100001], SCC[100001];
bool finished[100001];
int sz, cnt = 0;
vector<int> stk;
int low[100001];
int dfs(int cur) {
	dfsn[cur] = ++cnt;
	stk.push_back(cur);
	/*int low = dfsn[cur];*/
	low[cur] = dfsn[cur];
	for (int next : graph[cur]) {
		if (!dfsn[next]) {
			low[cur] = min(low[cur], dfs(next));
		}
		else if (!SCC[next]) {
			low[cur] = min(low[cur], dfsn[next]);
		}
	}
	if (low[cur] == dfsn[cur]) {
		sz++;
		while (true) {
			int element = stk.back(); stk.pop_back();
			SCC[element] = sz;
			if (element == cur) break;
		}
	}
	return low[cur];
}
int main() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> m;
		cnt = sz = 0;
		memset(SCC, 0, sizeof(SCC));
		memset(dfsn, 0, sizeof(dfsn));
		memset(indegree, 0, sizeof(dfsn));

		for (int i = 0; i < 100001; i++) {
			graph[i].clear();
		}
		for (int i = 0; i < m; i++) {
			/*int x, y;
			cin >> x >> y;
			graph[x].push_back(y);*/
			
		}
		graph[1].push_back(2);
		graph[1].push_back(4);
		graph[2].push_back(3);
		graph[3].push_back(1);
		graph[3].push_back(5);
		graph[5].push_back(4);
		graph[4].push_back(5);
		graph[5].push_back(6);
		graph[6].push_back(7);
		graph[7].push_back(8);
		graph[6].push_back(5);
		for (int i = 1; i <= n; i++) {
			if (!dfsn[i]) {
				dfs(i);
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int next : graph[i]) {
				if (SCC[i] == SCC[next]) {
					continue;
				}
				indegree[SCC[next]]++;
			}
		}
		int answer = 0;
		for (int i = 1; i <= sz; i++) {
			if (!indegree[i]) {
				answer++;
			}
		}
		cout << answer << '\n';
	}
}