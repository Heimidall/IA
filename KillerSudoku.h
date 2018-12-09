#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
using namespace std;
const int tamano = 9;
class Celda{
  public:
    vector<int>::iterator it;
    int valor_inicial;
    int sector;
    int sector_value;
    vector<int> dominio;
    Celda(){
      for (size_t i = 0; i < tamano; i++) {
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
    for (size_t i = 0; i < tamano; i++) {
      if(!file.good()) return;
      for (size_t j = 0; j < tamano; j++) {
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
    for (size_t i = 0; i < tamano; i++) {
      for (size_t j = 0; j < tamano; j++) {
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
  /*
  void FiltroDominicial(KS& sudoku){
    for (int i = 0; i<tamano; i++) {
      for (int j= 0; j<tamano; j++ ) {
        if(sudoku.matrix[i][j].valor_inicial != 0){
          //cout << "Valor inicial: " << col->valor_inicial << '\n';
          sudoku.matrix[i][j].dominio.resize(1);
          sudoku.matrix[i][j].dominio[0] = sudoku.matrix[i][j].valor_inicial;
          //std::cout << "Valor incial: "<< sudoku.matrix[i][j].valor_inicial << '\n';
          //filtro_rows(sudoku, i, sudoku.matrix[i][j].valor_inicial);
        }
      }
    }
  }
  void filtro_rows(KS& sudoku, int n, int pos){
    for (int i = 0; i < tamano; i++) {
      if(sudoku.matrix[n][i].dominio.size() > 1){
        cout << sudoku.matrix[n][i].dominio[pos-1] << "Para el i" << i << '\n';
        sudoku.matrix[n][i].dominio.erase(sudoku.matrix[n][i].dominio.begin()+(pos-1));
        return;
      }
    }
    return;
  }*/

};
