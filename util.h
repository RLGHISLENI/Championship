/**************************************************************
 ********* Trabalho Prático Grau B                    *********
 ********* Algoritmos e Programação C++               *********
 ********* Simulação e Bolão do Campeonato Brasileiro *********
 ********* Aluno: Roberto Luis Ghisleni               ********* 
 **************************************************************/

// Definição das referências utilizadas 
#include <string>
#include <vector>

// Define o namespace
using namespace std;

// Estrutura da classe
class util {
  public:
    static void StringSplit(string, string, vector<string>&);
};

// Método estático que realiza spllit em var. string e retorna vetor por referência
void util::StringSplit(string str, string delim, vector<string>& results){
  int cutAt;
  while((cutAt = str.find_first_of(delim)) != str.npos){
    if(cutAt > 0){
      results.push_back(str.substr(0,cutAt));
    }
    str = str.substr(cutAt+1);
  }
  if(str.length() > 0) {
    results.push_back(str);
  }
}
