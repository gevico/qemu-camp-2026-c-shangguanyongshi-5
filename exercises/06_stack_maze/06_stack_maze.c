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
	int stack_row[MAX_ROW * MAX_COL];
	int stack_col[MAX_ROW * MAX_COL];
	int next_dir[MAX_ROW * MAX_COL];
	int dr[4] = {-1, 0, 1, 0}; /* 上、右、下、左 */
	int dc[4] = {0, 1, 0, -1};
	int top = -1;
	int found = 0;
	int i, j;

	for (i = 0; i < MAX_ROW; i++) {
		for (j = 0; j < MAX_COL; j++) {
			parent_row[i][j] = -1;
			parent_col[i][j] = -1;
		}
	}

	stack_row[++top] = 0;
	stack_col[top] = 0;
	next_dir[top] = 0;
	visited[0][0] = 1;

	while (top >= 0) {
		int r = stack_row[top];
		int c = stack_col[top];
		int moved = 0;

		if (r == MAX_ROW - 1 && c == MAX_COL - 1) {
			found = 1;
			break;
		}

		while (next_dir[top] < 4) {
			int dir = next_dir[top]++;
			int nr = r + dr[dir];
			int nc = c + dc[dir];

			if (nr >= 0 && nr < MAX_ROW &&
			    nc >= 0 && nc < MAX_COL &&
			    maze[nr][nc] == 0 && !visited[nr][nc]) {
				parent_row[nr][nc] = r;
				parent_col[nr][nc] = c;
				visited[nr][nc] = 1;
				stack_row[++top] = nr;
				stack_col[top] = nc;
				next_dir[top] = 0;
				moved = 1;
				break;
			}
		}

		if (!moved) {
			top--;
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
			int pr, pc;
			printf("(%d, %d)\n", r, c);
			pr = parent_row[r][c];
			pc = parent_col[r][c];
			r = pr;
			c = pc;
		}
	}

	return 0;
}