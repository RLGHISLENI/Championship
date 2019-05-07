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

// Definição de classes utilizadas
class equipe;

// Estrutura da classe
class confronto {
  public:
    confronto(void);
    ~confronto(void);
    equipe getTimeCasa();
    void setTimeCasa(equipe value);
    equipe getTimeVisitante();
    void setTimeVisitante(equipe value);
    int getJogoRealizado();
    void setJogoRealizado(int value);
    string getRegistro();
    void setRegistro(string value);
    void limpar();

  private:
    equipe time_casa;
    equipe time_visitante;
    int jogoRealizado; // 0 - Não realziado   1 - Realizado
};

// Construtor da classe
confronto::confronto() {
  this->limpar();
}

// Destrutor da classe
confronto::~confronto() {
   
 }
 
// Gets e Sets das propriedades da classe
equipe confronto::getTimeCasa() {
  return this->time_casa;
}
void confronto::setTimeCasa(equipe value){
  this->time_casa = value;
}
equipe confronto::getTimeVisitante() {
  return this->time_visitante;
}
void confronto::setTimeVisitante(equipe value){
  this->time_visitante = value;
}
int confronto::getJogoRealizado(){
  return this->jogoRealizado;
}
void confronto::setJogoRealizado(int value){
  this->jogoRealizado = value;
}

// Obtem os dados do objeto separados por um delimitador para armazenar em arquivo 
string confronto::getRegistro(){  
  return this->time_casa.getNome() + ";" + std::to_string(this->time_casa.getGolspro()) + ";" + std::to_string(this->time_casa.getGolscontra()) + ";" + std::to_string(this->time_casa.getVitorias()) + ";" + std::to_string(this->time_casa.getDerrotas()) + ";" + std::to_string(this->time_casa.getEmpates()) + ";" + std::to_string(this->time_casa.getPontos()) + "|" +
         this->time_visitante.getNome() + ";" + std::to_string(this->time_visitante.getGolspro()) + ";" + std::to_string(this->time_visitante.getGolscontra()) + ";" + std::to_string(this->time_visitante.getVitorias()) + ";" + std::to_string(this->time_visitante.getDerrotas()) + ";" + std::to_string(this->time_visitante.getEmpates()) + ";" + std::to_string(this->time_visitante.getPontos())  + "|" +
         std::to_string(this->jogoRealizado) + "\n";
} 

// Carrega as propriedades do objeto com a informação recebida do arquivo gravado
void confronto::setRegistro(string value){  
  // Realiza split com delimitador principal(|) e carrega vetor com as informações passadas
  vector<string> regConfronto;
  util::StringSplit(value, "|", regConfronto);  

  // Carrega ou inicializa informações 
  if(regConfronto.size() > 0) {    

    // Carrega ou inicializa informações do time da casa
    this->time_casa.setRegistro(regConfronto[0]);
    
    // Carrega ou inicializa informações do time visitante
    this->time_visitante.setRegistro(regConfronto[1]);

    // Carrega ou inicializa flag 
    this->time_casa,jogoRealizado = std::stoi(regConfronto[2]);
  } else {
    this->limpar();
  }   
} 

// Funções da classe
void confronto::limpar(){
  // Inicializa
  this->time_casa.limpar();
  this->time_visitante.limpar();
  this->jogoRealizado = 0;
}    