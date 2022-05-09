#ifndef __SUDOKU_SOLVE_H__
#define __SUDOKU_SOLVE_H__

int sudoku_check_all_data(void);
int sudoku_solve_1(int *times);


int try_to_fill_num_in_box_by_row_col(void);
int sudoku_solve_2(int *times);

int sudoku_solve_3(int *times);

int sudoku_solve_backtracking(int *times);

#endif
