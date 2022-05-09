
all:
	-@mkdir build
	gcc -c sudoku_common.c -o sudoku_common.o
	gcc -c sudoku_solve_1.c -o sudoku_solve_1.o
	gcc -c sudoku_solve_2.c -o sudoku_solve_2.o
	gcc -c sudoku_solve_3.c -o sudoku_solve_3.o
	gcc -c sudoku_solve_backtracking.c -o sudoku_solve_backtracking.o
	gcc -c main.c -o main.o
	gcc -o sudoku sudoku_common.o sudoku_solve_1.o sudoku_solve_2.o sudoku_solve_3.o sudoku_solve_backtracking.o main.o
	-@ mv *.o build/

clean:
	-@rm build/*.o -rf
	-@rm build -rf
	-@rm sudoku -rf
