#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include "KillerSudoku.h"
using namespace std;

int main(void) {
  KS sudoku;
  sudoku.printGrilla();
  sudoku.printSectores();
  /*sudoku.FiltroDominicial(sudoku);
  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      sudoku.matrix[i][j].printdom();
    }
  }*/
//cout << matrix[0][1].sector_value << "este deberia ser 2,5" << matrix[2][2].sector_value << "este deberia ser 9,9";
return 0;
}
