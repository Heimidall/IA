#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
const int tamano = 9;
class Celda{
  public:
    void printdom(Celda& celda);
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
};
void Celda:: printdom(Celda& celda){
  for (auto i : celda.dominio)
  cout << ' ' << i;
  cout << '\n';
}

class KS{
private:


public:
  void printGrilla(KS& sudoku);
  void printSectores(KS& sudoku);
  bool lleno(KS& sudoku);
  void FiltroDominicial(KS& sudoku);
  void filtro_rows(KS& sudoku, int n, int& pos);
  void filtro_cols(KS& sudoku, int n, int& pos);
  void iterador_cols(KS& sudoku);
  void iterador_rows(KS& sudoku);
  void filtrador(KS& sudoku, int col,int row);
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
    ifstream file("80blank.txt");
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

};
  void KS:: printGrilla(KS& sudoku){
    for (size_t i = 0; i < tamano; i++) {
      for (size_t j = 0; j < tamano; j++) {
        cout << sudoku.matrix[i][j].valor_inicial << " ";
      }
      cout << '\n';
    }
  }
  void KS:: printSectores(KS& sudoku){
    for ( it = sudoku.valor_sectores.begin() ; it != sudoku.valor_sectores.end(); ++it)
      cout << ' ' << *it;
    cout << '\n';
  }
  bool KS:: lleno(KS& sudoku){
    for (int i = 0; i < tamano; i++) {
      for (int j = 0; j < tamano; j++) {
        if(sudoku.matrix[i][j].valor_inicial == 0){
          return false;
        }
      }
    }
    return true;
  }

  void KS::FiltroDominicial(KS& sudoku){
    for (int i = 0; i<tamano; i++) {
      for (int j= 0; j<tamano; j++ ) {
        if(sudoku.matrix[i][j].valor_inicial != 0){
          //cout << "Valor inicial: " << col->valor_inicial << '\n';
          sudoku.matrix[i][j].dominio.resize(1);
          sudoku.matrix[i][j].dominio[0] = sudoku.matrix[i][j].valor_inicial;
          //std::cout << "Valor incial: "<< sudoku.matrix[i][j].valor_inicial << '\n';
        }
        //else para los valores igaules a cero
        else{
          filtrador(sudoku, i,j);
        }
      }
    }
    return;
  }
  void KS::filtrador(KS& sudoku, int col, int row){
    vector<int>::iterator x;
    //para columnas
    for (int i = 0; i < tamano; i++) {
      if(sudoku.matrix[i][row].valor_inicial != 0){
        if(find(sudoku.matrix[col][row].dominio.begin(),sudoku.matrix[col][row].dominio.end(),sudoku.matrix[i][row].valor_inicial) != sudoku.matrix[col][row].dominio.end()){
          x = find(sudoku.matrix[col][row].dominio.begin(),sudoku.matrix[col][row].dominio.end(),sudoku.matrix[i][row].valor_inicial);
          sudoku.matrix[col][row].dominio.erase(x);

        }
      }
    }
    //para las filas
    for (int i = 0; i < tamano; i++) {
      if(sudoku.matrix[col][i].valor_inicial != 0){
        if(find(sudoku.matrix[col][row].dominio.begin(),sudoku.matrix[col][row].dominio.end(),sudoku.matrix[col][i].valor_inicial) !=sudoku.matrix[col][row].dominio.end()){
          x = find(sudoku.matrix[col][row].dominio.begin(),sudoku.matrix[col][row].dominio.end(),sudoku.matrix[col][i].valor_inicial);
          sudoku.matrix[col][row].dominio.erase(x);

        }
      }
    }
    for (int i = (col - (col%3)); i < (col - (col%3))+sqrt(tamano); i++) {
      for (int j = (row - (col%3)); j < (row - (row%3))+sqrt(tamano); j++) {
        if(sudoku.matrix[i][j].valor_inicial != 0){
          if(find(sudoku.matrix[col][row].dominio.begin(),sudoku.matrix[col][row].dominio.end(),sudoku.matrix[i][j].valor_inicial) !=sudoku.matrix[col][row].dominio.end()){
            x = find(sudoku.matrix[col][row].dominio.begin(),sudoku.matrix[col][row].dominio.end(),sudoku.matrix[i][j].valor_inicial);
            sudoku.matrix[col][row].dominio.erase(x);

          }
        }
      }
    }
    return;
  }
