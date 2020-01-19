#include <stdio.h>
#include <stdlib.h>

typedef struct shark {
	// r, c 는 상어의 위치
	// speed는 속력
	// directionrection는 방향
	// size는 상어의 크기
	int r, c, speed, direction, size;
} shark;


const int direct[] = { 0, -1, 1, 1, -1 };


int main()
{
	int R, C, M, cnt, fisher = 0, total = 0;
	scanf("%d %d %d", &R, &C, &M);

	int** mark;
	mark = (int**)malloc(R * sizeof(int*));
	for (int i = 0; i < R; i++) {
		mark[i] = (int*)malloc(C * sizeof(int));
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			mark[i][j] = -1;
		}
	}

	shark* a = (shark*)malloc(M * sizeof(shark));
	int* erase = (int*)malloc(M * sizeof(int));

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d %d %d", &a[i].r, &a[i].c, &a[i].speed, &a[i].direction, &a[i].size);
		(a[i].r)--;
		(a[i].c)--;
		erase[i] = 0;
		mark[a[i].r][a[i].c] = i;
	}


	while (1) {

		int j = 0;
		while (j < R) {
			if (mark[j][fisher] >= 0) {
				total += a[mark[j][fisher]].size;
				erase[mark[j][fisher]] = 1;
				mark[j][fisher] = -1;
				break;
			}
			j++;
		}
		if (fisher == C - 1) break;
		for (int i = 0; i < M; i++)
			mark[a[i].r][a[i].c] = -1;
		for (int i = 0; i < M; i++) {
			if (erase[i]) continue;

			if (a[i].direction == 3 || a[i].direction == 4) {
				if (((a[i].speed) / (2 * C - 2)) >= 1) {
					if (a[i].c == 0) a[i].direction = 3;
					else if (a[i].c == C - 1) a[i].direction = 4;
				}
				cnt = (a[i].speed) % (2 * C - 2);
				while (cnt > 0) {
					if (a[i].c == 0) a[i].direction = 3;
					else if (a[i].c == C - 1) a[i].direction = 4;
					a[i].c += direct[a[i].direction];
					cnt--;
				}

				if (mark[a[i].r][a[i].c] == -1) mark[a[i].r][a[i].c] = i;
				else if (mark[a[i].r][a[i].c] >= 0) {
					if (a[mark[a[i].r][a[i].c]].size > a[i].size) erase[i] = 1;
					else if (a[mark[a[i].r][a[i].c]].size < a[i].size) {
						erase[mark[a[i].r][a[i].c]] = 1;
						mark[a[i].r][a[i].c] = i;
					}
				}
			}

			else {
				if (((a[i].speed) / (2 * R - 2)) >= 1) {
					if (a[i].r == 0) a[i].direction = 1;
					else if (a[i].r == R - 1) a[i].direction = 2;
				}
				cnt = (a[i].speed) % (2 * R - 2);
				while (cnt > 0) {
					if (a[i].r == 0) a[i].direction = 2;
					else if (a[i].r == R - 1) a[i].direction = 1;
					a[i].r += direct[a[i].direction];
					cnt--;
				}

				if (mark[a[i].r][a[i].c] == -1) mark[a[i].r][a[i].c] = i;
				else if (mark[a[i].r][a[i].c] >= 0) {
					if (a[mark[a[i].r][a[i].c]].size > a[i].size) erase[i] = 1;
					else if (a[mark[a[i].r][a[i].c]].size < a[i].size) {
						erase[mark[a[i].r][a[i].c]] = 1;
						mark[a[i].r][a[i].c] = i;
					}
				}
			}
		}
		fisher++;
	}
	printf("%d", total);
	for (int i = 0; i < R; i++)
		free(mark[i]);
	free(mark);
	free(a);
	free(erase);
}