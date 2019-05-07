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

// Defini��o de classes utilizadas
class confronto;

// Estrutura da classe
class bolao
{
  public:
    bolao(void);
    ~bolao(void);
    string getNome();
    void setNome(string value);
    confronto *getAposta();
    void setAposta(int index, confronto value);
    int getPontos();
    void setPontos(int value);
    string getRegistro();
    void setRegistro(string value);
    string getRegAposta();
    void setRegAposta(string value);
    void gravarPalpites(string nomeTorneio);
    void limpar();

  private:
    string nome;    
    confronto aposta[20];
    int pontos;
};

 // Construtor da classe
bolao::bolao() {
  this->limpar();
}

// Destrutor da classe
 bolao::~bolao() {

}

// Gets e Sets das propriedades da classe
string bolao::getNome() {
  return this->nome;
}
void bolao::setNome(string value){
  this->nome = value;
}
confronto *bolao::getAposta() {
  return this->aposta;
}
void bolao::setAposta(int index, confronto value){
 this->aposta[index] = value;
}
int bolao::getPontos() {
  return this->pontos;
}
void bolao::setPontos(int value){
  this->pontos = value;
}

// Obtem os dados do objeto separados por um delimitador para armazenar em arquivo 
string bolao::getRegistro(){  
  return this->nome + ";" + std::to_string(this->pontos);
} 

// Carrega as propriedades do objeto com a informa��o recebida do arquivo gravado
void bolao::setRegistro(string value){  
  // Realiza split e carrega vetor com as informa��es passadas
  vector<string> regBolao;
  util::StringSplit(value, ";", regBolao);  
  
  // Carrega ou inicializa informa��es 
  if(regBolao.size() > 0) {    
    this->nome = regBolao[0].c_str();
    this->pontos = std::stoi(regBolao[1]);
  } else {
    this->limpar();
  }
} 

// Fun��es da classe
void bolao::limpar(){
  // Iniciliza
  this->nome = "";
  *this->aposta = *new confronto[20];
  this->pontos = 0;
}    