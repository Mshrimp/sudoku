#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "color.h"
#include "sudoku_common.h"
#include "sudoku_solve.h"

int main(int argc, char *argv[])
{
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

	for (i = 0; i < 1; i++) {
		sudoku_solve_1();
	}


	printf("Total test count: %d\n", i);

    return 0;
}

