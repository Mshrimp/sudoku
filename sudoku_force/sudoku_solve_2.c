#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "color.h"
#include "sudoku_common.h"
#include "sudoku_solve.h"

int num_fill_in_box(int box, int num)
{
	int box_start_row = 0;
	int box_start_col = 0;
	int row_ind = 0;
	int col_ind = 0;
	int ind = 0;
	char box_arr[3][3] = { 0 };

	get_box_start_row_col(box, &box_start_row, &box_start_col);
	
	for (ind = 0; ind < 9; ind++) {
		box_arr[ind/3][ind%3] = sudoku[box_start_row+ind/3][box_start_col+ind%3][0];
	}
	//box_3_3_show(box_arr);

	for (ind = 0; ind < 3; ind++) {
		row_ind = box_start_row + ind;
		if (is_num_in_row(row_ind, num)) {
			fill_in_box_row_by_num(box_arr, ind, num);
		}
	}
	//box_3_3_show(box_arr);

	for (ind = 0; ind < 3; ind++) {
		col_ind = box_start_col + ind;
		if (is_num_in_col(col_ind, num)) {
			fill_in_box_col_by_num(box_arr, ind, num);
		}
	}
	//box_3_3_show(box_arr);

	if (1 == get_box_3_3_empty_count(box_arr)) {
		for (ind = 0; ind < 9; ind++) {
			if (box_arr[ind/3][ind%3] == 0) {
				break;
			}
		}
		if (ind == 9) {
			return 0;
		}
		row_ind = box_start_row + ind/3;
		col_ind = box_start_col + ind%3;

		fill_num_in_sudoku_row_col(row_ind, col_ind, num);
	}

	return 0;
}

int try_to_fill_num_in_box_by_row_col(void)
{
	int num_ind = 0;
	int box_ind = 0;
	
	for (num_ind = 0; num_ind < 9; num_ind++) {
		for (box_ind = 0; box_ind < SUDOKU_BOX; box_ind++) {
			if (is_num_in_box(box_ind, num_ind+1)) {
				continue;
			}
			num_fill_in_box(box_ind, num_ind+1);
		}
	}

	return 0;
}

int sudoku_solve_2(void)
{
	int count_init = 0;
	int count = 0;
	int count_bak = 0;
	int i = 0;
	int ret = -1;

	count_init = sudoku_data_count();

	for (i = 0; ; i++) {
		try_to_fill_num_in_box_by_row_col();

		printf("Check sudoku 2 data %d times:\n", i+1);
		sudoku_show();

		count = sudoku_data_count();
		if ((count == 81) || (count == count_init) || (count == count_bak)) {
			break;
		}
		count_bak = count;
		printf("Sudoku 2 total data count: %d\n", count);
	}

    return 0;
}
