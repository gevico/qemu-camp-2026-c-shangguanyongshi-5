#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int main(void)
{
	int visited[MAX_ROW][MAX_COL] = {0};
	int parent_row[MAX_ROW][MAX_COL];
	int parent_col[MAX_ROW][MAX_COL];
	int queue_row[MAX_ROW * MAX_COL];
	int queue_col[MAX_ROW * MAX_COL];
	int front = 0;
	int rear = 0;
	int found = 0;
	int i, j;
	int dr[4] = {1, 0, -1, 0};
	int dc[4] = {0, 1, 0, -1};

	for (i = 0; i < MAX_ROW; i++) {
		for (j = 0; j < MAX_COL; j++) {
			parent_row[i][j] = -1;
			parent_col[i][j] = -1;
		}
	}

	queue_row[rear] = 0;
	queue_col[rear] = 0;
	rear++;
	visited[0][0] = 1;

	while (front < rear) {
		int r = queue_row[front];
		int c = queue_col[front];
		int d;
		front++;

		if (r == MAX_ROW - 1 && c == MAX_COL - 1) {
			found = 1;
			break;
		}

		for (d = 0; d < 4; d++) {
			int nr = r + dr[d];
			int nc = c + dc[d];
			if (nr >= 0 && nr < MAX_ROW &&
			    nc >= 0 && nc < MAX_COL &&
			    maze[nr][nc] == 0 && !visited[nr][nc]) {
				visited[nr][nc] = 1;
				parent_row[nr][nc] = r;
				parent_col[nr][nc] = c;
				queue_row[rear] = nr;
				queue_col[rear] = nc;
				rear++;
			}
		}
	}

	if (!found) {
		printf("No path!\n");
		return 0;
	}

	{
		int r = MAX_ROW - 1;
		int c = MAX_COL - 1;
		while (r != -1 && c != -1) {
			int pr = parent_row[r][c];
			int pc = parent_col[r][c];
			printf("(%d, %d)\n", r, c);
			r = pr;
			c = pc;
		}
	}

	return 0;
}