#include <iostream>
#include <cstdlib>
using namespace std;
const int N =9;
class Sudoku{
private:
  bool Encontrarpos(int grid[N][N], int &row, int &col);
  bool isSafe(int grid[N][N], int row, int col, int num);
  bool solveSudoku(int grid[N][N]);
  bool checkRow(int grid[N][N], int row, int col);
  bool checkCol(int grid[N][N], int row, int col);
  bool checkBox(int grid[N][N], int boxStartRow, int boxStartCol, int num);
  void Printer(int grid[N][N]);
public:
  Sudoku();

  
};
