#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
struct Enemy {
	int y, x, alive;
	Enemy(int _y, int _x, int _alive) : y(_y), x(_x), alive(_alive) {

	}
};
//13 20
int n, m, d;
vector<int> vec;
vector<Enemy> enemies;
set<int> s;
int maxanswer = 0;
const int inf = 10000000;

int calculate() {
	int y = n;
	int xs[] = { vec[0], vec[1], vec[2] };
	vector<Enemy> temp(enemies);
	int ans = 0;
	while (1) {
		int shooted[] = { -1, -1, -1 };
		int distance[] = { inf, inf, inf };
		
		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < temp.size(); i++) {
				if (temp[i].alive) {
					int tempDist = abs(y - temp[i].y) + abs(xs[k] - temp[i].x);
					if (tempDist > d) continue;
					if (distance[k] > tempDist) {
						distance[k] = tempDist;
						shooted[k] = i;
					}
					if (distance[k] == tempDist) {
						if (temp[shooted[k]].x > temp[i].x) {
							shooted[k] = i;
						}
					}
				}
			}
		}
		for (int k = 0; k < 3; k++) {
			if (shooted[k] == -1) continue;
			temp[shooted[k]].alive = 0;
			s.emplace(shooted[k]);
		}
		ans += s.size();
		s.clear();
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i].alive) {
				if (++temp[i].y >= n) {
					temp[i].alive = 0;
				}
			}
		}
		bool continueFlag = false;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i].alive) {
				continueFlag = true;
				break;
			}
		}
		if (!continueFlag) return ans;
	}
	
}
void solve(int idx, int depth) {
	if (depth == 3) {
		//calculate
		maxanswer = max(maxanswer, calculate());
		return;
	}
	for (int i = idx + 1; i < m; i++) {
		vec.push_back(i);
		solve(i, depth + 1);
		vec.pop_back();
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n >> m >> d;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int b;
			cin >> b;
			if (b) {
				enemies.emplace_back(i, j, 1);
			}
		}
	}
	solve(-1, 0);
	cout << maxanswer;
}