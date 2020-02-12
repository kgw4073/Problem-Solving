#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define SWAP(a, b) {P temp = a; a = b; b = temp;}
using namespace std;
// 13 25
int n, m, k;
int arr[50][50];

struct P {
	int r, c, s;
};

vector<P> back;
int answer = 2000000000;
void rotate(int r, int c, int ss, int arr[][50]) {
	r--; c--;
	vector<int*> vec;
	vector<int> val;
	for (int s = ss; s >= 1; s--) {
		vec.clear();
		val.clear();
		val.push_back(arr[r - s + 1][c - s]);
		for (int i = c - s; i < c + s; i++) {
			vec.push_back(&arr[r - s][i]);
			val.push_back(arr[r - s][i]);
		}
		for (int i = r - s; i < r + s; i++) {
			vec.push_back(&arr[i][c + s]);
			val.push_back(arr[i][c + s]);

		}
		for (int i = c + s; i > c - s; i--) {
			vec.push_back(&arr[r + s][i]);
			val.push_back(arr[r + s][i]);

		}
		for (int i = r + s; i > r - s; i--) {
			vec.push_back(&arr[i][c - s]);
			val.push_back(arr[i][c - s]);
		}

		for (int i = 0, bound = 8 * s; i < bound; i++) {
			*vec[i] = val[i];
		}
	}
}
int calculate(int arr[][50]) {
	int ret = 2000000000;
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < m; j++) {
			sum += arr[i][j];
		}
		ret = min(ret, sum);
	}
	return ret;
}
void solve(int depth) {
	if (depth == k - 1) {
		int temp[50][50];
		memcpy(temp, arr, sizeof(temp));
		for (P& order : back) {
			rotate(order.r, order.c, order.s, temp);
		}
		answer = min(answer, calculate(temp));
		return;
	}
	for (int i = depth; i < k; i++) {
		SWAP(back[depth], back[i]);
		solve(depth + 1);
		SWAP(back[depth], back[i]);
	}
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		int r, c, s;
		cin >> r >> c >> s;
		back.push_back({ r, c, s });
	}
	solve(0);
	cout << answer;
}
