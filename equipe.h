/**************************************************************
 ********* Trabalho Prático Grau B                    *********
 ********* Algoritmos e Programação C++               *********
 ********* Simulação e Bolão do Campeonato Brasileiro *********
 ********* Aluno: Roberto Luis Ghisleni               ********* 
 **************************************************************/

// Definição das referências utilizadas 
#include <string>
#include <vector>
#include "util.h"  // Funções estáticas

// Define o namespace
using namespace std;

// Definição de classes utilizadas
class util;

// Estrutura da classe
class equipe {
  public:
    equipe(void);
    ~equipe(void);
    string getNome();
    void setNome(string value);
    int getGolspro();
    void setGolspro(int value);
    int getGolscontra();
    void setGolscontra(int value);
    int getVitorias();
    void setVitorias(int value);
    int getDerrotas();
    void setDerrotas(int value);
    int getEmpates();
    void setEmpates(int value);
    int getPontos();
    int getSaldo();
    string getRegistro();
    void setRegistro(string value);
    void limpar();
    void iniciarPontuacao();

  private:
    string nome;
    int golspro;
    int golscontra;
    int vitorias;
    int derrotas;
    int empates;
    int pontos;    
    //util funcao;
};

// Construtor da classe
equipe::equipe() { 
  this->limpar();
}

// Destrutor da classe
 equipe::~equipe() {

 }
 
// Gets e Sets das propriedades da classe
string equipe::getNome() {
  return this->nome;
}
void equipe::setNome(string value){
  this->nome = value;
}
int equipe::getGolspro() {
  return this->golspro;
}
void equipe::setGolspro(int value){
  this->golspro = this->golspro + value;
}
int equipe::getGolscontra(){
  return this->golscontra;
}
void equipe::setGolscontra(int value){
  this->golscontra = this->golscontra + value;
}
int equipe::getVitorias(){
  return this->vitorias;
}
void equipe::setVitorias(int value){
  this->vitorias = this->vitorias + value;
  this->pontos = this->pontos + (3 * value);
}
int equipe::getDerrotas(){
  return this->derrotas;
}
void equipe::setDerrotas(int value){
  this->derrotas = this->derrotas + value;
}
int equipe::getEmpates(){
  return this->empates;
}    
void equipe::setEmpates(int value){
  this->empates = this->empates + value;
  this->pontos = this->pontos + value;
}    
int equipe::getPontos(){
  return this->pontos;
}
int equipe::getSaldo(){
  return (this->golspro - this->golscontra);
}

// Obtem os dados do objeto separados por um delimitador para armazenar em arquivo 
string equipe::getRegistro(){    
  return this->nome + ";" + 
         std::to_string(this->golspro) + ";" + 
         std::to_string(this->golscontra) + ";" + 
         std::to_string(this->vitorias) + ";" + 
         std::to_string(this->derrotas) + ";" + 
         std::to_string(this->empates) + ";" + 
         std::to_string(this->pontos) + "\n";
} 

// Carrega as propriedades do objeto com a informação recebida do arquivo gravado
void equipe::setRegistro(string value){  
  // Realiza split e carrega vetor com as informações passadas
  vector<string> regTabela;
  util::StringSplit(value, ";", regTabela);  
  
  // Carrega ou inicializa informações 
  if(regTabela.size() > 0) {
    this->nome = regTabela[0].c_str();
    this->golspro = std::stoi(regTabela[1]);
    this->golscontra = std::stoi(regTabela[2]);
    this->vitorias = std::stoi(regTabela[3]);
    this->derrotas = std::stoi(regTabela[4]);
    this->empates = std::stoi(regTabela[5]);
    this->pontos = std::stoi(regTabela[6]);
  } else {
    this->limpar();
  } 
} 

// Funções da classe
void equipe::iniciarPontuacao(){
  // Inicializa var int
  this->golspro = 0;
  this->golscontra = 0;
  this->vitorias = 0;
  this->derrotas = 0;
  this->empates = 0;
  this->pontos = 0; 
}    
void equipe::limpar(){
  // Inicializa tudo
  this->nome = "";
  iniciarPontuacao();
}    