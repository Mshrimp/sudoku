#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "color.h"
#include "sudoku_common.h"
#include "sudoku_solve.h"

int main(int argc, char *argv[])
{
	int count = 0;
	int count_bak = 0;
	int times = 0;
	int i = 0;
	int ret = -1;

    if (argc < 2) {
        printf("Usage: %s file\n", argv[0]);
        return -1;
    }

    ret = get_data_from_file(argv[1]);
    if (ret < 0) {
        printf("%s, get_data_from_file: %s, failed!\n", __func__, argv[1]);
        return ret;
    }

	sudoku_data_init();

	printf("Init sudoku data:\n");
	sudoku_show();

	for (i = 0; ; i++) {
		sudoku_solve_1(&times);
		sudoku_solve_2(&times);
		sudoku_solve_3(&times);

		count = sudoku_data_count();

		if (count == count_bak) {
			sudoku_show();
			break;
		}
		count_bak = count;
	}

	sudoku_solve_backtracking(&times);

    return 0;
}

