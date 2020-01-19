#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


int r, c, sharkCount;
vector<vector<list<int>>> index_map;

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, 1, -1 };
class Shark {
public:
	int _r, _c, _speed, _dir, _size;
	Shark() {
		_r = 0;
		_c = 0;
		_speed = 0;
		_dir = 0;
		_size = 0;
	}
	Shark(int r, int c, int speed, int dir, int size) {
		_r = r;
		_c = c;
		_speed = speed;
		_dir = dir;
		_size = size;
	}
};

void SharkMove(Shark &shark) {
	int speed = shark._speed;
	int &dir = shark._dir;
	int &y = shark._r;
	int &x = shark._c;
	if (dir == 0) {
		speed %= (2 * r - 2);
		int upper_distance = y - 1;
		int lower_distance = r - y;
		if (speed > upper_distance) {
			speed -= upper_distance;
			y = 1;
			dir = 1;
			if (speed > r - 1) {
				speed -= (r - 1);
				y = r;
				y -= speed;
				dir = 0;
			}
			else {
				y += speed;
			}
		}
		else {
			y -= speed;
			return;
		}
	}
	// 아래
	else if (dir == 1) {
		speed %= (2 * r - 2);
		int upper_distance = y - 1;
		int lower_distance = r - y;
		if (speed > lower_distance) {
			speed -= lower_distance;
			y = r;
			dir = 0;
			if (speed > r - 1) {
				speed -= (r - 1);
				y = 1;
				dir = 1;
				y += speed;
				return;
			}
			else {
				y -= speed;
				return;
			}
		}
		else {
			y += speed;
			return;
		}
	}
	// 오른쪽
	else if (dir == 2) {
		speed %= (2 * c - 2);
		int right_distance = c - x;
		int left_distance = x - 1;
		if (speed > right_distance) {
			speed -= right_distance;
			x = c;
			dir = 3;
			if (speed > c - 1) {
				speed -= (c - 1);
				x = 1;
				dir = 2;
				x += speed;
				return;
			}
			else {
				x -= speed;
				return;
			}
		}
		else {
			x += speed;
			return;
		}
	}
	// 왼쪽
	else {
		speed %= (2 * c - 2);
		int right_distance = c - x;
		int left_distance = x - 1;
		if (speed > left_distance) {
			speed -= left_distance;
			x = 1;
			dir = 2;
			if (speed > c - 1) {
				speed -= (c - 1);
				x = c;
				x -= speed;
				dir = 3;
				return;
			}
			else {
				x += speed;
				return;
			}
		}
		else {
			x -= speed;
			return;
		}
	}
	
}
int main() {
	cin >> r >> c >> sharkCount;
	vector<Shark> sharks;
	vector<pair<int, int>> vec;
	int closest = 1000;
	int closest_shark_index = -1;
	int min_distance = 0;
	sharks.resize(sharkCount + 1);
	index_map.resize(101);
	for (int i = 0; i < 101; i++) {
		index_map[i].resize(101);
	}
	for (int i = 1; i <= sharkCount; i++) {
		int r, c, speed, dir, size;
		cin >> r >> c >> speed >> dir >> size;
		Shark shark(r, c, speed, --dir, size);
		sharks[i] = shark;
		if (c == 1) {
			if (min_distance == 0) {
				min_distance = r;
				closest_shark_index = i;
			}
			else if (min_distance > r) {
				min_distance = r;
				closest_shark_index = i;
			}
		}
		index_map[r][c].push_back(i);
	}
	
	int answer = 0;
	for (int time = 1; time <= c; time++) {
		// 포획
		if (min_distance != 0) {
			answer += sharks[closest_shark_index]._size;
			index_map[sharks[closest_shark_index]._r][sharks[closest_shark_index]._c].pop_front();
			sharks[closest_shark_index]._r = 0;
			sharks[closest_shark_index]._c = 0;
		}
		min_distance = 0;

		// 상어 대이동
		for (int i = 1; i <= sharkCount; i++) {
			// 상어 존재
			if (sharks[i]._c | 0) {
				index_map[sharks[i]._r][sharks[i]._c].pop_front();
				SharkMove(sharks[i]);
				int y = sharks[i]._r;
				int x = sharks[i]._c;
				index_map[y][x].push_back(i);
			}
		}

		// 상어 잡아먹기
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				if (!index_map[i][j].size()) continue;

				int max_shark_index = index_map[i][j].front();
				int max_shark_size = 0;
				if (index_map[i][j].size() >= 2) {
					for (int index : index_map[i][j]) {
						if (max_shark_size < sharks[index]._size) {
							max_shark_index = index;
							max_shark_size = sharks[index]._size;
						}
					}
					for (int index : index_map[i][j]) {
						if (index != max_shark_index) {
							sharks[index]._r = 0;
							sharks[index]._c = 0;
						}
					}
					index_map[i][j].clear();
					index_map[i][j].push_back(max_shark_index);

				}
				if (j == time + 1) {
					if (min_distance == 0) {
						min_distance = sharks[max_shark_index]._r;
						closest_shark_index = max_shark_index;
					}
					else if (min_distance > sharks[max_shark_index]._r) {
						min_distance = sharks[max_shark_index]._r;
						closest_shark_index = max_shark_index;
					}
				}
			}
		}
	}
	cout << answer;
}