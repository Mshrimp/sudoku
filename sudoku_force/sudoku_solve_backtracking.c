#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "color.h"
#include "sudoku_common.h"
#include "sudoku_solve.h"

int backtracking(void)
{
	int row_ind = 0;
	int col_ind = 0;
	int num = 0;
	int count = 0;
	int ind = 0;

	for (row_ind = 0; row_ind < SUDOKU_ROW; row_ind++) {
		for (col_ind = 0; col_ind < SUDOKU_COL; col_ind++) {
			if (sudoku[row_ind][col_ind][0] != 0) {
				continue;
			}
			for (num = 1; num < 10; num++) {
				if (sudoku[row_ind][col_ind][num+1] == 0) {
					continue;
				}
				if (sudoku_data_check(row_ind, col_ind, num)) {
					continue;
				}
				sudoku[row_ind][col_ind][0] = num;
				count = sudoku[row_ind][col_ind][1];
				sudoku[row_ind][col_ind][1] = 1;
				if (backtracking()) {
					return 1;
				}
				sudoku[row_ind][col_ind][0] = 0;
				sudoku[row_ind][col_ind][1] = count;
			}
			return 0;
		}
	}

	return 1;
}

int sudoku_solve_backtracking(int *times)
{
	int count_init = 0;
	int count = 0;
	int i = 0;
	int ret = -1;

	backtracking();

	(*times)++;
	printf("Check sudoku backtracking data times: %d\n", *times);
	sudoku_show();

	count = sudoku_data_count();
	printf("Sudoku backtracking total data count: %d\n", count);

    return 0;
}
