#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <deque>
#define SWAP(a, b) { int temp = a; a = b; b = temp; }
using namespace std;
int n;
int score[50][9];
vector<int> ordering;
int answer = 0;
deque<int> field;
vector<int> index;

int calculate() {
	int out_count = 0;
	int current_score = 0;
	int cnt = 0;

	for (int inning = 0; inning < n; inning++) {
		field.clear();
		out_count = 0;
		while (1) {
			int current_state = score[inning][index[cnt]];

			if (current_state == 0) {
				out_count++;
				cnt++;
				if (cnt >= 9) {
					cnt = 0;
				}
				if (out_count == 3) break;
				
				continue;
			}

			if (!field.size()) {
				field.emplace_back(current_state);
				if (field.back() == 4) {
					current_score++;
					field.pop_back();
				}
			}
			else {
				field.push_front(0);
				auto endian = field.rend();
				for (auto itr = field.rbegin(); ; ) {
					if (!field.size()) break;
					if (itr == endian) break;

					(*itr) += current_state;
					
					if (*itr >= 4) {
						current_score++;
						field.pop_back();
						itr = field.rbegin();
					}
					else itr++;
				}
				
			}
			cnt++;
			if (cnt >= 9) {
				cnt = 0;
			}
		}
	}
	
	return current_score;
}
void solve(int depth) {
	if (depth == 8) {
		for (int i = 0; i < 9; i++) {
			index[ordering[i]] = i;
		}
		answer = max(answer, calculate());
		return;
	}
	for (int i = depth; i < 9; i++) {
		SWAP(ordering[depth], ordering[i]);
		solve(depth + 1);
		SWAP(ordering[depth], ordering[i]);
	}
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n;

	ordering.push_back(3);
	for (int i = 0; i < 9; i++) {
		if (i == 3) continue;
		ordering.push_back(i);
	}
	for (int inning = 0; inning < n; inning++) {
		for (int i = 0; i < 9; i++) {
			cin >> score[inning][i];
		}
	}
	index.resize(9);
	solve(1);
	
	cout << answer;
}