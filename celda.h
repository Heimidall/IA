#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#pragma once
using namespace std;
class Celda{
  public:
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
      for(int i = 0; i < 9; i++) {
        cout << dominio[i] << '\n';
      }
    }
};
