#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
const int tamano = 9;
class Sector{
public:
  int valor_sectormax;
  int valor_sector;
  int miembros;
  Sector(int x){
    valor_sector = x;
    miembros = 0;
    valor_sectormax=x;
  }
};
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
  void FC(KS sudoku, int col, int row, int valor);
  void RestoreFC(KS sudoku, int col, int row, int valor);
  vector< vector<Celda> >::iterator row;
  vector<Celda>::iterator col;
  vector<vector<Celda>> matrix{9, vector<Celda>(9)};
  vector<Sector> valor_sectores;
  vector<int>::iterator it;
  KS(){
    char ptos;
    string value;
    int pos,x;
    string c;
    ifstream file("hard.txt");
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
      Sector sec(x);
      valor_sectores.push_back(sec);
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
    for ( auto it = sudoku.valor_sectores.begin() ; it != sudoku.valor_sectores.end(); ++it)
      cout << ' ' << it->valor_sector << "con:" << it->miembros << "miembros |";
    cout << '\n';
  }
  bool KS:: lleno(KS& sudoku){
    for (int i = 0; i < tamano; i++) {
      for (int j = 0; j < tamano; j++) {
        if(sudoku.matrix[i][j].valor_inicial == 0 || sudoku.valor_sectores[j].valor_sector != 0){// || sudoku.valor_sectores[j].valor_sector != 0
          return false;
        }
      }
    }
    return true;
  }

  void KS::FiltroDominicial(KS& sudoku){
    for (int i = 0; i<tamano; i++) {
      for (int j= 0; j<tamano; j++ ) {
        sudoku.valor_sectores[sudoku.matrix[i][j].sector-1].miembros +=1;
        if(sudoku.matrix[i][j].valor_inicial != 0){
          sudoku.matrix[i][j].dominio.resize(1);
          sudoku.matrix[i][j].dominio[0] = sudoku.matrix[i][j].valor_inicial;
          sudoku.valor_sectores[sudoku.matrix[i][j].sector-1].valor_sector -= sudoku.matrix[i][j].valor_inicial;
          sudoku.valor_sectores[sudoku.matrix[i][j].sector-1].miembros -=1;
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
      sudoku.valor_sectores[sudoku.matrix[col][row].sector-1].valor_sector -= sudoku.matrix[col][row].valor_inicial;
      sudoku.valor_sectores[sudoku.matrix[col][row].sector-1].miembros -=1;
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

      //killer sudoku
      //std::cout << "antes de entrar al if: (" << col << " , " << row << ") : " << sudoku.valor_sectores[sudoku.matrix[col][row].sector -1].valor_sector<< " - " << valor  << " = " <<sudoku.valor_sectores[sudoku.matrix[col][row].sector-1].valor_sector - valor << "Miembros: " <<sudoku.valor_sectores[sudoku.matrix[col][row].sector-1].miembros << '\n';
      if((sudoku.valor_sectores[sudoku.matrix[col][row].sector-1].valor_sector - valor)<0){
        //sudoku.valor_sectores[sudoku.matrix[col][row].sector-1] += valor;
        //std::cout << "entre al if" << '\n';
        return false;
      }

      if((sudoku.valor_sectores[sudoku.matrix[col][row].sector-1].valor_sector - valor) > 0 && sudoku.valor_sectores[sudoku.matrix[col][row].sector-1].miembros == 0){ //aqui solo entraría el ultimo numero
        //std::cout << "Entre al if de miembros, porque  (" <<col<<" , " << row<<") tiene 0 miembros" << '\n';
            //sudoku.valor_sectores[sudoku.matrix[col][row].sector_value] += valor;
            //std::cout << "Valor sectores en, es valido: "<< sudoku.valor_sectores[sudoku.matrix[col][row].sector_value] << '\n';
            return false;


      }

    return true;
    }
  void KS::solver(KS& sudoku){
    vector<int> respaldo;
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
        for (int i = sudoku.matrix[x][y].dominio.size(); i-- !=0;) {
          respaldo = sudoku.matrix[x][y].dominio;
          temp = sudoku.matrix[x][y].dominio[i];
          //std::cout << "(" << x << ',' <<y << ")" << " temp:"<<temp <<" :"<<" size:" << sudoku.matrix[x][y].dominio.size()<<'\n';
          //std::cout<< "Sector: " <<sudoku.valor_sectores[(sudoku.matrix[x][y].sector)-1]<< " " <<sudoku.valor_sectores[sudoku.matrix[x][y].sector_value]<< '-'<< sudoku.matrix[x][y].dominio[i]<< ' ' << sudoku.valor_sectores[sudoku.matrix[x][y].sector_value] - sudoku.matrix[x][y].dominio[i] << '\n';
          sudoku.valor_sectores[sudoku.matrix[x][y].sector -1].miembros -=1;
          sudoku.matrix[x][y].valor_inicial = sudoku.matrix[x][y].dominio[i];
          if(sudoku.es_valido(sudoku,x,y, sudoku.matrix[x][y].dominio[i])){
            if((x==0 && y ==0)|| (x==1 && y ==1) || (x==2 && y ==2)|| (x==3 && y ==3)|| (x==4 && y ==4)|| (x==5 && y ==5) || (x==6 && y ==6) || (x==7 && y ==7) || (x==8 && y ==8)){
              std::cout << "( " << x<<" , " << y <<") =" << temp <<'\n';
            }
            //std::cout << "moviemiento valido: " << temp << '\n';

            sudoku.valor_sectores[sudoku.matrix[x][y].sector -1].valor_sector -= temp;
            sudoku.FC(sudoku, x,y,sudoku.matrix[x][y].dominio[i]);
            //std::cout << "avanzo en la recursion con este valor del sector: " << sudoku.valor_sectores[sudoku.matrix[x][y].sector -1].valor_sector << '\n';
            //std::cout << "Miembros:" << sudoku.valor_sectores[sudoku.matrix[x][y].sector -1].miembros <<'\n';
            //sudoku.matrix[x][y].dominio.erase(sudoku.matrix[x][y].dominio.begin()+i);
            sudoku.solver(sudoku);
          }

        //sudoku.matrix[x][y].dominio.push_back(temp);
        //std::cout << "ME DEEEEVOOOOOOOLLLLLLL VIIIIIIIIIIIIIIII " << " TEMP: " <<temp << '\n';
        if(!sudoku.lleno(sudoku)){
          //std::cout << "me devuelvo en la recursion con este valor del sector: " << sudoku.valor_sectores[sudoku.matrix[x][y].sector -1].valor_sector <<'\n';

          //std::cout << "Return: " << x <<" , " << y<< '|' << temp <<'\n';
          sudoku.valor_sectores[sudoku.matrix[x][y].sector -1].miembros +=1;
          sudoku.valor_sectores[sudoku.matrix[x][y].sector-1].valor_sector += sudoku.matrix[x][y].valor_inicial;
          sudoku.RestoreFC(sudoku, x,y,sudoku.matrix[x][y].dominio[i]);
          //std::cout << "Valor sector: "<<sudoku.valor_sectores[sudoku.matrix[x][y].sector_value] <<'\n';
          //sudoku.matrix[x][y].dominio = respaldo;
          sudoku.matrix[x][y].valor_inicial = 0;

        }
        else{
          return;
        }
      }
    }
  }
}
void KS::RestoreFC(KS sudoku, int col, int row, int valor){
  for (int i = 0; i < tamano; i++) {
    if(find(sudoku.matrix[i][row].dominio.begin(),sudoku.matrix[i][row].dominio.end(),valor) == sudoku.matrix[i][row].dominio.end()){
      sudoku.matrix[i][row].dominio.push_back(valor);
      sort(sudoku.matrix[i][row].dominio.begin(),sudoku.matrix[i][row].dominio.end());
    }
  }
  for (int i = 0; i < tamano; i++) {
    if(find(sudoku.matrix[col][i].dominio.begin(),sudoku.matrix[col][i].dominio.end(),valor) == sudoku.matrix[col][i].dominio.end()){
      sudoku.matrix[col][i].dominio.push_back(valor);
      sort(sudoku.matrix[col][i].dominio.begin(),sudoku.matrix[col][i].dominio.end());
    }
  }
  for (int i = (col - (col%3)); i < (col - (col%3))+sqrt(tamano); i++) {
    for (int j = (row - (row%3)); j < (row - (row%3))+sqrt(tamano); j++) {
      if(find(sudoku.matrix[i][j].dominio.begin(),sudoku.matrix[i][j].dominio.end(),valor) == sudoku.matrix[i][j].dominio.end()){
        sudoku.matrix[i][j].dominio.push_back(valor);
        sort(sudoku.matrix[i][j].dominio.begin(),sudoku.matrix[i][j].dominio.end());
      }
    }
  }
}
void KS::FC(KS sudoku, int col, int row, int valor){
  vector<int>::iterator x;
    //para columnas
    for (int i = 0; i < tamano; i++) {
        if(find(sudoku.matrix[i][row].dominio.begin(),sudoku.matrix[i][row].dominio.end(),valor) != sudoku.matrix[i][row].dominio.end()){
          x = find(sudoku.matrix[i][row].dominio.begin(),sudoku.matrix[i][row].dominio.end(),valor);
          sudoku.matrix[i][row].dominio.erase(x);
        }
        if(sudoku.matrix[i][row].dominio.size()==0){
          return;
        }
      }
    //para las filas
    for (int i = 0; i < tamano; i++) {
      if(find(sudoku.matrix[col][i].dominio.begin(),sudoku.matrix[col][i].dominio.end(),valor) != sudoku.matrix[col][i].dominio.end()){
        x = find(sudoku.matrix[col][i].dominio.begin(),sudoku.matrix[col][i].dominio.end(),valor);
        sudoku.matrix[col][i].dominio.erase(x);
        }
        if(sudoku.matrix[col][i].dominio.size()==0){
          return;
        }
      }

    //cajas
    for (int i = (col - (col%3)); i < (col - (col%3))+sqrt(tamano); i++) {
      for (int j = (row - (row%3)); j < (row - (row%3))+sqrt(tamano); j++) {
        if(find(sudoku.matrix[i][j].dominio.begin(),sudoku.matrix[i][j].dominio.end(),valor) != sudoku.matrix[i][j].dominio.end()){
          x = find(sudoku.matrix[i][j].dominio.begin(),sudoku.matrix[i][j].dominio.end(),valor);
          sudoku.matrix[i][j].dominio.erase(x);
          }
          if(sudoku.matrix[i][j].dominio.size()==0){
            return;
          }
      }
    }
  }
