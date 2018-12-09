#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
using namespace std;
class Celda{
  public:
    vector<int>::iterator it;
    size_t size = 9;
    int valor_inicial;
    int sector;
    int sector_value;
    vector<int> dominio;
    Celda(){
      for (size_t i = 0; i < size; i++) {
        dominio.push_back(i+1);
      }
    }
    void printdom(){
      for (auto i : dominio)
        cout << ' ' << i;
      cout << '\n';
      }
};

class KS{
public:
  vector< vector<Celda> >::iterator row;
  vector<Celda>::iterator col;
  vector<vector<Celda>> matrix{9, vector<Celda>(9)};
  vector<int> valor_sectores;
  vector<int>::iterator it;
  KS(){
    char ptos;
    string value;
    int pos,x;
    string c;
    ifstream file("easier_filled.txt");
    for (size_t i = 0; i < 9; i++) {
      if(!file.good()) return;
      for (size_t j = 0; j < 9; j++) {
        file >> ptos;
        if(ptos == '.'){
          matrix[i][j].valor_inicial = 0;
        }
        else{
          x = ptos - '0';
          matrix[i][j].valor_inicial = x;
        }
        file >> value;
        pos = value.find('C');
        c = value.substr(pos+1);
        stringstream ent(c);
        ent >> matrix[i][j].sector;
        }
  }
    while(file.good()){
      file >> value;
      pos = value.find(':');
      c = value.substr(pos+1);
      stringstream ent(c);
      ent >> x;
      valor_sectores.push_back(x);
    }
    file.close();
  }

  void printGrilla(){
    for (size_t i = 0; i < 9; i++) {
      for (size_t j = 0; j < 9; j++) {
        cout << matrix[i][j].valor_inicial << " ";
      }
      cout << '\n';
    }
  }
  void printSectores(){
    for ( it = valor_sectores.begin() ; it != valor_sectores.end(); ++it)
      cout << ' ' << *it;
    cout << '\n';
  }
  void FiltroDominicial(KS& sudoku){
    for (row = sudoku.matrix.begin(); row != sudoku.matrix.end(); ++row) {
      for (col = row->begin(); col != row->end(); ++col) {
        if(col->valor_inicial != 0){
          cout << "Valor inicial: " << col->valor_inicial << '\n';
          col->dominio.resize(1);
          col->dominio[0] = col->valor_inicial;
        }
      }
    }
  }

};
