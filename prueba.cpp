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
  sudoku.printGrilla(sudoku);
  sudoku.printSectores(sudoku);
  sudoku.FiltroDominicial(sudoku);
  //sudoku.iterador_cols(sudoku);
  //sudoku.iterador_rows(sudoku);
  for (size_t i = 0; i < tamano; i++) {
    for (size_t j = 0; j < tamano; j++) {
      sudoku.matrix[i][j].printdom(sudoku.matrix[i][j]);
    }
  }
//cout << matrix[0][1].sector_value << "este deberia ser 2,5" << matrix[2][2].sector_value << "este deberia ser 9,9";
return 0;
}
