/**************************************************************
 ********* Trabalho Pr�tico Grau B                    *********
 ********* Algoritmos e Programa��o C++               *********
 ********* Simula��o e Bol�o do Campeonato Brasileiro *********
 ********* Aluno: Roberto Luis Ghisleni               ********* 
 **************************************************************/

// Defini��o das refer�ncias utilizadas 
#include <string>
#include <vector>

// Define o namespace
using namespace std;

// Estrutura da classe
class util {
  public:
    static void StringSplit(string, string, vector<string>&);
};

// M�todo est�tico que realiza spllit em var. string e retorna vetor por refer�ncia
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
