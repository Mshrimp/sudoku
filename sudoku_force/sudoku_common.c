#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "color.h"
#include "sudoku_common.h"

// 11
// 0 - 现有实际值
// 1 - 可选数据个数
// 2~10 - 可选数据列表
char sudoku[SUDOKU_ROW][SUDOKU_COL][11] = { 0 };

int get_data_from_file(char *file)
{
    FILE *fp = NULL;
    char buf[16] = { 0 };
    int len = 0;
    int i = 0;
	int j = 0;

    fp = fopen(file, "r");
    if (!fp) {
        printf("%s, fopen failed, errno: %d, %s\n",
                __func__, errno, strerror(errno));
        return -1;
    }

    while (fgets(buf, sizeof(buf), fp)) {
        len = strlen(buf);
		if (buf[len-1] == '\n') {
			buf[len-1] = '\0';
		}
        len = strlen(buf);
        if (len > SUDOKU_COL) {
            printf("%s, i: %d, buf: %s, len: %d, over range!\n",
                    __func__, i, buf, len);
            break;
        }
        for (j = 0; j < len; j++) {
            sudoku[i][j][0] = buf[j] - '0';
        }

		memset(buf, 0, sizeof(buf));
        i++;
    }

    fclose(fp);

    return 0;
}

int sudoku_show(void)
{
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; i < SUDOKU_ROW; i++) {
		if (i % 3 == 0) {
			for (k = 0; k < 25; k++) {
				if ((i != 0) && (k != 0) && (k != 24) && (k % 8 == 0)) {
					printf("+");
				} else {
					printf("-");
				}
			}
			printf("\n");
		}
        for (j = 0; j < SUDOKU_COL; j++) {
			if (j % 3 == 0) {
				if (j != 0) {
					printf(" ");
				}
				printf("|");
			}
			if ((sudoku[i][j][0] != 0) && (sudoku[i][j][1] == 0)) {
            	printf(BLUE" %d"NONE, sudoku[i][j][0]);
			} else if (sudoku[i][j][1] == 1) {
				printf(GREEN" %d"NONE, sudoku[i][j][0]);
			} else {
				printf(GRAY" %d"NONE, sudoku[i][j][0]);
			}
        }
		printf(" |");
        printf("\n");
    }
	for (k = 0; k < 25; k++) {
		printf("-");
	}
	printf("\n");

    return 0;
}

int get_box_by_row_col(int row, int col)
{
	int box = 0;

	box = row / 3 * 3 + col / 3;

	return box;
}

int get_box_start_row_col(int box, int *row, int *col)
{
	*row = box / 3 * 3;
	*col = box % 3 * 3;

	return 0;
}

int sudoku_row_check(int row, char num)
{
	int i = 0;

	for (i = 0; i < SUDOKU_COL; i++) {
		if (sudoku[row][i][0] == num) {
			return 1;
		}
	} 

	return 0;
}

int sudoku_col_check(int col, char num)
{
	int i = 0;

	for (i = 0; i < SUDOKU_ROW; i++) {
		if (sudoku[i][col][0] == num) {
			return 1;
		}
	} 

	return 0;
}

int sudoku_box_check(int row, int col, char num)
{
	int box = 0;
	int box_row = 0;
	int box_col = 0;
	int i = 0;
	int j = 0;

	box = row/3*3 + col/3;
	box_row = box/3*3;
	box_col = box%3*3;

	for (i = 0; i < SUDOKU_ROW; i++) {
		if (sudoku[box_row+(i/3)][box_col+(i%3)][0] == num) {
			return 1;
		}
	} 

	return 0;
}

int sudoku_data_check(int row, int col, char num)
{
	int i = 0;
	int ret = -1;

	ret = sudoku_row_check(row, num);
	if (ret) {
		return 1;
	}
	
	ret = sudoku_col_check(col, num);
	if (ret) {
		return 1;
	}
	
	ret = sudoku_box_check(row, col, num);
	if (ret) {
		return 1;
	}
	
	return 0;
}

int sudoku_data_init(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int num = 0;

	for (i = 0; i < SUDOKU_ROW; i++) {
		for (j = 0; j < SUDOKU_COL; j++) {
			if (sudoku[i][j][0] == 0) {
				for (num = 1; num <= 9; num++) {
					sudoku[i][j][num+1] = num;
					sudoku[i][j][1] += 1;
				}
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

int sudoku_data_count(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int num = 0;
	int count = 0;

	for (i = 0; i < SUDOKU_ROW; i++) {
		for (j = 0; j < SUDOKU_COL; j++) {
			if (sudoku[i][j][0] != 0) {
				count++;
			}
		}
	}

	return count;
}

int is_num_in_row(int row, int num)
{
	int i = 0;

	for (i = 0; i < SUDOKU_COL; i++) {
		if (sudoku[row][i][0] == num) {
			return 1;
		}
	}

	return 0;
}

int is_num_in_col(int col, int num)
{
	int i = 0;

	for (i = 0; i < SUDOKU_ROW; i++) {
		if (sudoku[i][col][0] == num) {
			return 1;
		}
	}

	return 0;
}

int is_num_in_box(int box, int num)
{
	int box_start_row = 0;
	int box_start_col = 0;
	int i = 0;

	get_box_start_row_col(box, &box_start_row, &box_start_col);

	for (i = 0; i < 9; i++) {
		if (sudoku[box_start_row+i/3][box_start_col+i%3][0] == num) {
			return 1;
		}
	}

	return 0;
}

int get_row_num_count(int row)
{
	int count = 0;
	int i = 0;

	for (i = 0; i < SUDOKU_COL; i++) {
		if (sudoku[row][i][0] != 0) {
			count++;
		}
	}

	return count;
}

int get_row_empty_count(int row)
{
	int count = 0;
	int i = 0;

	for (i = 0; i < SUDOKU_COL; i++) {
		if (sudoku[row][i][0] == 0) {
			count++;
		}
	}

	return count;
}

int get_col_num_count(int col)
{
	int count = 0;
	int i = 0;

	for (i = 0; i < SUDOKU_ROW; i++) {
		if (sudoku[i][col][0] != 0) {
			count++;
		}
	}

	return count;
}

int get_col_empty_count(int col)
{
	int count = 0;
	int i = 0;

	for (i = 0; i < SUDOKU_ROW; i++) {
		if (sudoku[i][col][0] == 0) {
			count++;
		}
	}

	return count;
}

int get_box_num_count(int box)
{
	int box_start_row = 0;
	int box_start_col = 0;
	int count = 0;
	int i = 0;

	get_box_start_row_col(box, &box_start_row, &box_start_col);

	for (i = 0; i < 9; i++) {
		if (sudoku[box_start_row+i/3][box_start_col+i%3][0] != 0) {
			count++;
		}
	}

	return count;
}

int get_box_empty_count(int box)
{
	int box_start_row = 0;
	int box_start_col = 0;
	int count = 0;
	int i = 0;

	get_box_start_row_col(box, &box_start_row, &box_start_col);

	for (i = 0; i < 9; i++) {
		if (sudoku[box_start_row+i/3][box_start_col+i%3][0] == 0) {
			count++;
		}
	}

	return count;
}

int fill_in_box_row_by_num(char box[][3], int row, int num)
{
	int i = 0;

	for (i = 0; i < 3; i++) {
		box[row][i] = num;
	}

	return 0;
}

int fill_in_box_col_by_num(char box[][3], int col, int num)
{
	int i = 0;

	for (i = 0; i < 3; i++) {
		box[i][col] = num;
	}

	return 0;
}

int fill_in_box_by_num(char box[][3], int num)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			box[i][j] = num;
		}
	}

	return 0;
}

int fill_num_in_sudoku_row_col(int row, int col, int num)
{
	int ind = 0;

	sudoku[row][col][0] = num;
	sudoku[row][col][1] = 1;

	for (ind = 0; ind < 9; ind++) {
		if (sudoku[row][col][ind+2] != num) {
			sudoku[row][col][ind+2] = 0;
		}
	}

	return 0;
}

int get_box_3_3_num_count(char box[][3])
{
	int count = 0;
	int i = 0;

	for (i = 0; i < 9; i++) {
		if (box[i/3][i%3] != 0) {
			count++;
		}
	}

	return count;
}

int get_box_3_3_empty_count(char box[][3])
{
	int count = 0;
	int i = 0;

	for (i = 0; i < 9; i++) {
		if (box[i/3][i%3] == 0) {
			count++;
		}
	}

	return count;
}

int box_3_3_show(char box[][3])
{
	int i = 0;

	printf("box show:\n");
	printf("--------\n");
	for (i = 0; i < 9; i++) {
		if ((i != 0) && (i % 3 == 0)) {
			printf("\n");
		}
		printf(" %d", box[i/3][i%3]);
	}
	printf("\n");
	printf("--------\n");

	return 0;
}

