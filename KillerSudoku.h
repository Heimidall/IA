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
    int valor_final;
    vector<int> dominio;
    Celda(){
      valor_final = 0;
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
  bool es_valido(KS& sudoku, int col, int row, int valor);
  void FiltroDominicial(KS& sudoku);
  void printSol(KS& sudoku);
  void filtrador(KS& sudoku, int col,int row);
  void solver(KS& sudoku);
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
  void KS:: printSol(KS& sudoku){
      for (size_t i = 0; i < tamano; i++) {
        for (size_t j = 0; j < tamano; j++) {
          cout << sudoku.matrix[i][j].valor_inicial << " ";
        }
        cout << '\n';
      }
      std::cout << '\n';

  }

  void KS:: printSectores(KS& sudoku){
    for ( it = sudoku.valor_sectores.begin() ; it != sudoku.valor_sectores.end(); ++it)
      cout << ' ' << *it;
    cout << '\n';
  }
  bool KS:: lleno(KS& sudoku){
    for (int i = 0; i < tamano; i++) {
      for (int j = 0; j < tamano; j++) {
        if(sudoku.matrix[i][j].valor_inicial == 0 ){ //|| (sudoku.matrix[i][j].dominio.size() >1
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
          sudoku.matrix[i][j].dominio.resize(1);
          sudoku.matrix[i][j].dominio[0] = sudoku.matrix[i][j].valor_inicial;
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
    if(sudoku.matrix[col][row].valor_inicial ==0 ){
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
      //cajas
      for (int i = (col - (col%3)); i < (col - (col%3))+sqrt(tamano); i++) {
        for (int j = (row - (row%3)); j < (row - (row%3))+sqrt(tamano); j++) {
          if(sudoku.matrix[i][j].valor_inicial != 0){
            if(find(sudoku.matrix[col][row].dominio.begin(),sudoku.matrix[col][row].dominio.end(),sudoku.matrix[i][j].valor_inicial) !=sudoku.matrix[col][row].dominio.end()){
              x = find(sudoku.matrix[col][row].dominio.begin(),sudoku.matrix[col][row].dominio.end(),sudoku.matrix[i][j].valor_inicial);
              sudoku.matrix[col][row].dominio.erase(x);
            }
          }
        }
      }

    }
    if(sudoku.matrix[col][row].dominio.size()==1){
      sudoku.matrix[col][row].valor_inicial = sudoku.matrix[col][row].dominio[0];
    }
    return;
  }
  bool KS::es_valido(KS& sudoku, int col, int row, int valor){

    for (int i = 0; i < tamano; i++){
      if(sudoku.matrix[i][row].valor_inicial == valor)
        return false;
    }

    //para las filas
    for (int i = 0; i < tamano; i++) {
      if(sudoku.matrix[col][i].valor_inicial == valor)
        return false;
    }
    //cajas
    for (int i = (col - (col%3)); i < (col - (col%3))+sqrt(tamano); i++) {
      for (int j = (row - (row%3)); j < (row - (row%3))+sqrt(tamano); j++) {
        if(sudoku.matrix[i][j].valor_inicial == valor)
          return false;
        }
      }
      /*
      //killer sudoku
      std::cout << "antes de entrar al if: " << sudoku.valor_sectores[sudoku.matrix[col][row].sector_value] - valor << '\n';
      if((sudoku.valor_sectores[sudoku.matrix[col][row].sector_value] - valor)<0){
        std::cout << "entre al if" << '\n';
        return false;
      }
      else if((sudoku.valor_sectores[sudoku.matrix[col][row].sector_value] - valor)==0){ //aqui solo entraría el ultimo numero

        for (int i = 0; i < tamano; i++) {
          if(sudoku.valor_sectores[i] != 0){
            sudoku.valor_sectores[sudoku.matrix[col][row].sector_value] += valor;
            std::cout << "Valor sectores en, es valido: "<< sudoku.valor_sectores[sudoku.matrix[col][row].sector_value] << '\n';
            return false;
          }
        }
      }
      */
    return true;
    }
  void KS::solver(KS& sudoku){
    //vector<int>::iterator x;
    int x =0;
    int y=0;
    int temp = 0;
    bool flag = true;
    if(sudoku.lleno(sudoku)){
      //std::cout << "LLEEEENOOOOOOOOOOOOOO" << '\n';
      sudoku.printSol(sudoku);
      return;
    }
    else{
      for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
          if(sudoku.matrix[i][j].valor_inicial == 0){
            x = i;
            y = j;
            //std::cout << "i,j: " << i<<"," << j<<'\n';
            flag = false;
            break;
          }
        }
        if(!flag){
          break;
        }
      }
      if(!flag){
        for (int i = 0; i <sudoku.matrix[x][y].dominio.size(); i++) {
          temp = sudoku.matrix[x][y].dominio[i];
          //std::cout << "(" << x << ',' <<y << ")" << " temp:"<<temp <<" :"<<" size:" << sudoku.matrix[x][y].dominio.size()<<'\n';
          if(sudoku.es_valido(sudoku,x,y, temp)){
            //std::cout << "moviemiento valido: " << temp << '\n';
            //std::cout <<sudoku.valor_sectores[sudoku.matrix[x][y].sector_value]<< '-'<< temp<< ' ' << sudoku.valor_sectores[sudoku.matrix[x][y].sector_value] - temp << '\n';
            //sudoku.valor_sectores[sudoku.matrix[x][y].sector_value] -= temp;
            sudoku.matrix[x][y].valor_inicial = sudoku.matrix[x][y].dominio[i];
            //sudoku.matrix[x][y].dominio.erase(sudoku.matrix[x][y].dominio.begin()+i);
            sudoku.solver(sudoku);
          }

        //sudoku.matrix[x][y].dominio.push_back(temp);
        //std::cout << "ME DEEEEVOOOOOOOLLLLLLL VIIIIIIIIIIIIIIII " << " TEMP: " <<temp << '\n';
        if(!sudoku.lleno(sudoku)){
          //std::cout << "Return: " << x <<" , " << y<< '|' << temp <<'\n';
          //sudoku.valor_sectores[sudoku.matrix[x][y].sector_value] += temp;
          //std::cout << "Valor sector: "<<sudoku.valor_sectores[sudoku.matrix[x][y].sector_value] <<'\n';
          sudoku.matrix[x][y].valor_inicial = 0;

        }
        else{
          return;
        }
      }
    }
  }
}
