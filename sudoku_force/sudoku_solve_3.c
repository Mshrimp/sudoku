#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "color.h"
#include "sudoku_common.h"
#include "sudoku_solve.h"

int get_box_two_or_three_empty_num(int box_ind, char *data_arr, int size)
{
	int box_start_row = 0;
	int box_start_col = 0;
	char arr[9] = { 0 };
	int num = 0;
	int data_ind = 0;
	int ind = 0;

	get_box_start_row_col(box_ind, &box_start_row, &box_start_col);

	for (ind = 0; ind < 9; ind++) {
		num = sudoku[box_start_row+ind/3][box_start_col+ind%3][0];
		if (num > 0) {
			arr[num-1] = num;
		}
	}

	for (ind = 0; ind < 9; ind++) {
		if (arr[ind] == 0) {
			data_arr[data_ind] = ind+1;
			data_ind++;
			if (data_ind >= size) {
				printf("%s, error\n", __func__);
				return -1;
			}
		}
	}

	return 0;
}

int box_two_or_three_num_fill_in_row(int box, int row_common, int num)
{
	char box_arrs[3][3][3] = { 0 };
	char empty_data[3] = { 0 };
	int empty_count = 0;
	int box_row_start = 0;
	int box_col_start = 0;
	int row_ind = 0;
	int col_ind = 0;
	int box_ind = 0;
	int box_check_ind = 0;
	int row_check_ind = 0;
	int ind = 0;

	box_row_start = box / 3 * 3;
	box_col_start = 0;

	//printf("%s, box: %d, row_common: %d, num: %d\n", __func__, box, row_common, num);

	for (row_ind = 0; row_ind < 3; row_ind++) {
		for (col_ind = 0; col_ind < SUDOKU_COL; col_ind++) {
			box_arrs[col_ind/3][row_ind][col_ind%3] = sudoku[box_row_start+row_ind][box_col_start+col_ind][0];
		}
	}
	//box_3_3_3_show_in_row(box_arrs);

	for (box_ind = 0; box_ind < 3; box_ind++) {
		box_check_ind = box/3*3+box_ind;
		if (!is_num_in_box(box_check_ind, num)) {
			continue;
		}
		fill_in_box_by_num(box_arrs[box_check_ind%3], '*');
	}
	//box_3_3_3_show_in_row(box_arrs);

	for (row_ind = 0; row_ind < 3; row_ind++) {
		box_check_ind = box/3*3+box_ind;
		row_check_ind = box_row_start + row_ind;
		if (!is_num_in_row(row_check_ind, num)) {
			continue;
		}
		for (box_ind = 0; box_ind < 3; box_ind++) {
			fill_in_box_row_by_num(box_arrs[box_ind], row_ind, '*');
		}
	}
	//box_3_3_3_show_in_row(box_arrs);

	for (box_ind = 0; box_ind < 3; box_ind++) {
		fill_in_box_row_by_num(box_arrs[box_ind], row_common%3, '*');
	}
	//box_3_3_3_show_in_row(box_arrs);

	for (col_ind = 0; col_ind < SUDOKU_COL; col_ind++) {
		if (!is_num_in_col(col_ind, num)) {
			continue;
		}
		fill_in_box_col_by_num(box_arrs[col_ind/3], col_ind%3, '*');
	}
	//box_3_3_3_show_in_row(box_arrs);

	for (box_check_ind = 0; box_check_ind < 3; box_check_ind++) {
		if (1 != get_box_3_3_empty_count(box_arrs[box_check_ind])) {
			continue;
		}

		for (ind = 0; ind < 9; ind++) {
			if (box_arrs[box_check_ind][ind/3][ind%3] == 0) {
				break;
			}
		}
		if (ind == 9) {
			return 0;
		}
		row_ind = box_row_start + ind/3;
		col_ind = box_col_start + box_check_ind * 3 + ind%3;

		fill_num_in_sudoku_row_col(row_ind, col_ind, num);
	}

	return 0;
}

int box_two_or_three_num_fill_in_col(int box, int col_common, int num)
{
	char box_arrs[3][3][3] = { 0 };
	char empty_data[3] = { 0 };
	int empty_count = 0;
	int box_row_start = 0;
	int box_col_start = 0;
	int row_ind = 0;
	int col_ind = 0;
	int box_ind = 0;
	int box_check_ind = 0;
	int col_check_ind = 0;
	int ind = 0;

	box_row_start = 0;
	box_col_start = box % 3 * 3;

	//printf("%s, box: %d, col_common: %d, num: %d\n", __func__, box, col_common, num);

	for (row_ind = 0; row_ind < SUDOKU_ROW; row_ind++) {
		for (col_ind = 0; col_ind < 3; col_ind++) {
			box_arrs[row_ind/3][row_ind%3][col_ind] = sudoku[box_row_start+row_ind][box_col_start+col_ind][0];
		}
	}
	//box_3_3_3_show_in_col(box_arrs);

	for (box_ind = 0; box_ind < 3; box_ind++) {
		box_check_ind = box%3 + box_ind*3;
		if (!is_num_in_box(box_check_ind, num)) {
			continue;
		}
		fill_in_box_by_num(box_arrs[box_check_ind/3], '*');
	}
	//box_3_3_3_show_in_col(box_arrs);

	for (col_ind = 0; col_ind < 3; col_ind++) {
		col_check_ind = box_col_start + col_ind;
		if (!is_num_in_col(col_check_ind, num)) {
			continue;
		}
		for (box_ind = 0; box_ind < 3; box_ind++) {
			fill_in_box_col_by_num(box_arrs[box_ind], col_ind, '*');
		}
	}
	//box_3_3_3_show_in_col(box_arrs);

	for (box_ind = 0; box_ind < 3; box_ind++) {
		fill_in_box_col_by_num(box_arrs[box_ind], col_common%3, '*');
	}
	//box_3_3_3_show_in_col(box_arrs);

	for (row_ind = 0; row_ind < SUDOKU_ROW; row_ind++) {
		if (!is_num_in_row(row_ind, num)) {
			continue;
		}
		fill_in_box_row_by_num(box_arrs[row_ind/3], row_ind%3, '*');
	}
	//box_3_3_3_show_in_col(box_arrs);

	for (box_check_ind = 0; box_check_ind < 3; box_check_ind++) {
		if (1 != get_box_3_3_empty_count(box_arrs[box_check_ind])) {
			continue;
		}

		for (ind = 0; ind < 9; ind++) {
			if (box_arrs[box_check_ind][ind/3][ind%3] == 0) {
				break;
			}
		}
		if (ind == 9) {
			return 0;
		}
		row_ind = box_row_start + box_check_ind * 3 + ind/3;
		col_ind = box_col_start + ind%3;

		fill_num_in_sudoku_row_col(row_ind, col_ind, num);
	}

	return 0;
}

int try_to_fill_two_or_three_num_in_box(void)
{
	int num_ind = 0;
	int box_ind = 0;
	int row_common = 0;
	int col_common = 0;
	int empty_count = 0;
	char empty_data[3] = { 0 };
	int ind = 0;
	
	for (box_ind = 0; box_ind < SUDOKU_BOX; box_ind++) {
		empty_count = get_box_empty_count(box_ind);
		if ((2 != empty_count) && (3 != empty_count)) {
			continue;
		}
		//printf("%s, ok, box_ind: %d, empty_count: %d\n", __func__, box_ind, empty_count);

		if (is_box_empty_num_in_common_row(box_ind, &row_common)) {
			memset(empty_data, 0, sizeof(empty_data));
			get_box_two_or_three_empty_num(box_ind, empty_data, sizeof(empty_data));
#if 0
			printf("%s, box_ind: %d, row_common: %d\n", __func__, box_ind, row_common);
			printf("%s, empty_data[ind]:", __func__);
			for (ind = 0; ind < empty_count; ind++) {
				printf(" %d", empty_data[ind]);
			}
			printf("\n");
#endif
			for (ind = 0; ind < empty_count; ind++) {
				box_two_or_three_num_fill_in_row(box_ind, row_common, empty_data[ind]);
			}
		}

		if (is_box_empty_num_in_common_col(box_ind, &col_common)) {
			memset(empty_data, 0, sizeof(empty_data));
			get_box_two_or_three_empty_num(box_ind, empty_data, sizeof(empty_data));
#if 0
			printf("%s, box_ind: %d, row_common: %d\n", __func__, box_ind, row_common);
			printf("%s, empty_data[ind]:", __func__);
			for (ind = 0; ind < empty_count; ind++) {
				printf(" %d", empty_data[ind]);
			}
			printf("\n");
#endif
			for (ind = 0; ind < empty_count; ind++) {
				box_two_or_three_num_fill_in_col(box_ind, col_common, empty_data[ind]);
			}
		}
	}

	return 0;
}

int sudoku_solve_3(int *times)
{
	int count_init = 0;
	int count = 0;
	int count_bak = 0;
	int i = 0;
	int ret = -1;

	count_init = sudoku_data_count();

	for (i = 0; ; i++) {
		try_to_fill_two_or_three_num_in_box();

		count = sudoku_data_count();
		if ((count == 81) || (count == count_init) || (count == count_bak)) {
			break;
		}
		count_bak = count;

		(*times)++;
		printf("Check sudoku 3 data times: %d\n", *times);

		sudoku_show();
		printf("Sudoku 3 total data count: %d\n", count);
	}

    return 0;
}
