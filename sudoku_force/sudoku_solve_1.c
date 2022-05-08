#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "color.h"
#include "sudoku_common.h"
#include "sudoku_solve.h"

int sudoku_check_all_data(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int num = 0;

	for (i = 0; i < SUDOKU_ROW; i++) {
		for (j = 0; j < SUDOKU_COL; j++) {
			if (sudoku[i][j][0] == 0) {
				for (num = 1; num <= 9; num++) {
					if ((sudoku[i][j][num+1] != 0) && (sudoku_data_check(i, j, num))) {
						sudoku[i][j][num+1] = 0;
						sudoku[i][j][1] -= 1;
					}
				}
			}

			if ((sudoku[i][j][0] == 0) && (sudoku[i][j][1] == 1)) {
				for (k = 2; k < 11; k++) {
					if (sudoku[i][j][k] != 0) {
						break;
					}
				}
				sudoku[i][j][0] = sudoku[i][j][k];
			}
#if 0
			printf("row: %d, col: %d, data: ", i, j);
			for (k = 0; k < 11; k++) {
				printf(" %d", sudoku[i][j][k]);
			}
			printf("\n");
#endif
		}
	}

	return 0;
}

int sudoku_solve_1(void)
{
	int count_init = 0;
	int count = 0;
	int count_bak = 0;
	int i = 0;
	int ret = -1;

	count_init = sudoku_data_count();

	for (i = 0; ; i++) {
		sudoku_check_all_data();

		printf("Check sudoku data %d times:\n", i+1);
		sudoku_show();

		count = sudoku_data_count();
		if ((count == 81) || (count == count_init) || (count == count_bak)) {
			break;
		}
		count_bak = count;
		printf("Sudoku total data count: %d\n", count);
	}

    return 0;
}
