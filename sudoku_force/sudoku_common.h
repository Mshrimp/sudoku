#ifndef __SUDOKU_COMMON_H__
#define __SUDOKU_COMMON_H__

#define SUDOKU_ROW		(9)
#define SUDOKU_COL		(9)
#define SUDOKU_BOX		(9)

extern char sudoku[SUDOKU_ROW][SUDOKU_COL][11];

int get_data_from_file(char *file);
int sudoku_show(void);
int sudoku_row_check(int row, char num);
int sudoku_col_check(int col, char num);
int sudoku_box_check(int row, int col, char num);
int sudoku_data_check(int row, int col, char num);
int sudoku_data_init(void);
int sudoku_data_count(int *cnt);

#endif

