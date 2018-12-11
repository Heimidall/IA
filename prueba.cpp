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
  sudoku.FiltroDominicial(sudoku);
  //sudoku.printSectores(sudoku);
  std::cout << '\n';
/*
  for (size_t i = 0; i < tamano; i++) {
    for (size_t j = 0; j < tamano; j++) {
      //std::cout << "Posicion:" << '('<< i<< "," << j <<')';
      sudoku.matrix[i][j].printdom(sudoku.matrix[i][j]);
    }
  }*/
  std::cout << '\n';
  sudoku.printGrilla(sudoku);
  std::cout << '\n';
  sudoku.solver(sudoku);
  std::cout << '\n';

  //sudoku.printSol(sudoku);
  //sudoku.printSol(sudoku);
//cout << matrix[0][1].sector_value << "este deberia ser 2,5" << matrix[2][2].sector_value << "este deberia ser 9,9";
return 0;
}
