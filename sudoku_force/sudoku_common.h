#ifndef __SUDOKU_COMMON_H__
#define __SUDOKU_COMMON_H__

#define SUDOKU_ROW		(9)
#define SUDOKU_COL		(9)
#define SUDOKU_BOX		(9)

extern char sudoku[SUDOKU_ROW][SUDOKU_COL][11];

int get_data_from_file(char *file);
int sudoku_show(void);

int get_box_by_row_col(int row, int col);
int get_box_start_row_col(int box, int *row, int *col);

int sudoku_row_check(int row, char num);
int sudoku_col_check(int col, char num);
int sudoku_box_check(int row, int col, char num);
int sudoku_data_check(int row, int col, char num);
int sudoku_data_init(void);
int sudoku_data_count(void);

int is_num_in_row(int row, int num);
int is_num_in_col(int col, int num);
int is_num_in_box(int box, int num);

int get_row_num_count(int row);
int get_col_num_count(int col);
int get_box_num_count(int box);

int get_row_empty_count(int row);
int get_col_empty_count(int col);
int get_box_empty_count(int box);

int fill_in_box_row_by_num(char box[][3], int row, int num);
int fill_in_box_col_by_num(char box[][3], int col, int num);
int fill_in_box_by_num(char box[][3], int num);

int fill_num_in_sudoku_row_col(int row, int col, int num);

int get_box_3_3_num_count(char box[][3]);
int get_box_3_3_empty_count(char box[][3]);
int box_3_3_show(char box[][3]);

int box_3_3_3_show_in_row(char box_arrs[][3][3]);
int box_3_3_3_show_in_col(char box_arrs[][3][3]);

int is_box_empty_num_in_common_row(int box, int *common_row);
int is_box_empty_num_in_common_col(int box, int *common_col);

#endif

