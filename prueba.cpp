#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
using namespace std;
class Celda{
  public:
    size_t size = 9;
    char valor_inicial;
    int sector;
    int sector_value;
    vector<int> dominio;
    Celda(){
      for (size_t i = 0; i < size; i++) {
        dominio.push_back(i+1);
      }
    }
    void printdom(){
      for(int i = 0; i < 9; i++) {
        cout << dominio[i] << '\n';
      }
    }
  };

int main(void) {
vector<vector<Celda>> matrix(9, vector<Celda>(9));
vector<int> valor_sectores;
//matrix[0][1].sector_value = 25;
//matrix[2][2].sector_value = 99;
string s;
char valor;
char ptos;
string value;
int pos,x;
string c;
ifstream file("easier_filled.txt");
for (size_t i = 0; i < 9; i++) {
  if(!file.good()) return 1;
  for (size_t j = 0; j < 9; j++) {
    file >> matrix[i][j].valor_inicial;
    file >> value;
    pos = value.find('C');
    c = value.substr(pos+1);
    stringstream ent(c);
    ent >> matrix[i][j].sector;
    //file >> matrix[i][j].sector;
    cout << matrix[i][j].valor_inicial << "C" << matrix[i][j].sector << '\n';
  }
  cout << "Aca termina la matriz" << '\n';
}
cout  << "aca empieza los valores de los sectores" << '\n';
while(file.good()){
  file >> value;
  pos = value.find(':');
  c = value.substr(pos+1);
  stringstream ent(c);
  ent >> x;
  valor_sectores.push_back(x);
  }
  cout << matrix[0][0].sector << " " <<valor_sectores[(matrix[0][0].sector)-1] << '\n';
file.close();
//cout << matrix[0][1].sector_value << "este deberia ser 2,5" << matrix[2][2].sector_value << "este deberia ser 9,9";
return 0;
}
