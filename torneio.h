/**************************************************************
 ********* Trabalho Prático Grau B                    *********
 ********* Algoritmos e Programação C++               *********
 ********* Simulação e Bolão do Campeonato Brasileiro *********
 ********* Aluno: Roberto Luis Ghisleni               ********* 
 **************************************************************/

// Definição das referências utilizadas 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

// Define o namespace
using namespace std;

// Definição de classes utilizadas
class equipe;
class confronto;
class bolao;

// Estrutura da classe
class torneio
{
  public:
    torneio(void);
    ~torneio(void);    
    string getNome();
    void setNome(string value);
    equipe *getTabela();
    void setTabela(int index, equipe value);
    confronto *getJogos();
    void setJogos(int index, confronto value);
    bolao *getPalpite();
    void setPalpite(int index, bolao value);    
    void cadastrar_equipes();
    void informar_confrontos();
    void informar_bolao();
    void consultar_equipes();
    void consultar_confrontos();
    void consultar_classificacao();
    void consultar_vencedor_bolao();      
    void carregarTabela();
    void carregarJogos();
    void carregarBolao();
    void gravarTorneios();  
    void gravarTabela();
    void gravarJogos();
    void gravarBolao();

  private:
    string nome;
    int qtd_times;
    int qtd_partidas;
    int qtd_bolao;    
    int time;
    int partida;
    int apostador; 
    equipe tabela[20];
    confronto jogos[20];
    bolao palpite[20];
};

// Construtor da classe
torneio::torneio() {

}

// Destrutor da classe
 torneio::~torneio() {

}

// Gets e Sets das propriedades da classe
string torneio::getNome() {
  return this->nome;
}
void torneio::setNome(string value){
  this->nome = value;
}

// Procedimento para realização do cadastro de times, conforme a quantidade de times que devem compor o campeonato
void torneio::cadastrar_equipes()
{  
  // Limpa a tela
  system("CLS");

  // Quando equipes já informadas, visualizar cadastro
  if(this->qtd_times > 0 ){
    cout << "-----------------------------------------------------\n";
    cout << "--------- Cadastro de Equipes ja realizado ---------- \n";
    cout << "-----------------------------------------------------\n\n";
    
    // Aguarda o usuário informar alguma tecla
    system("PAUSE"); 

    // Chama visualização de times cadastrados
    consultar_equipes();

  } else {
  
    // Cabeçalho 
    cout << "-----------------------------------------------------\n";
    cout << "---------------- Cadastro de Equipes ---------------- \n";
    cout << "-----------------------------------------------------\n\n";
   
    // Identifica quantos times devem participar do campeonato
    cout << " Informe a quantidade de equipes do campeonato (zero para cancelar): ";
    cin >> this->qtd_times;
    cout << "\n";

    // Se informar zero, cancela o cadastro
    if (this->qtd_times > 0){
      
      // Redimenciona o array para a qtde de times participantes
      *tabela = *new equipe[this->qtd_times];
    
      // Define a qtde de partidas que o campeonato terá ( considerando jogos de ida e volta )
      this->qtd_partidas = (this->qtd_times-1) * this->qtd_times;

      // Redimenciona o array para a qtde de partidas a serem disputadas
      *this->jogos = *new confronto[this->qtd_partidas];
  
      // Armazena o nome de todos os times do campeonato no array
      for (this->time=0; this->time < this->qtd_times; this->time++)  {
        cout << " Informe o nome da equipe " << (this->time + 1) << ": ";
    
        // Lê e armazena o nome do time no array
        string nomeTime;
        cin >> nomeTime;
    
        // Inicializa as variáveis de cada time no array    
        this->tabela[time].setNome(nomeTime);
        this->tabela[time].iniciarPontuacao();
      }  
      cout << "-----------------------------------------------------\n\n";

      // Grava informações da tabela em arquivo
      gravarTabela();
    } else {
      cout << " Cadastro de equipes cancelado \n\n";
    }

    // Aguarda o usuário informar alguma tecla
    system("PAUSE"); 
  }
}

// Procedimento para visualizar a classificação
void torneio::consultar_classificacao()
{ 
  // Var. controle do laço
  equipe reg_aux;
  int qtd = qtd_times;
  int x,i,trocou;

  // Limpa a tela
  system("CLS");
  
  // Cabeçalho 
  cout << "-----------------------------------------------------\n";
  cout << "------- Tabela de Classificacao do Campeonato ------- \n";
  cout << "-----------------------------------------------------\n\n";

  // Cria uma cópia do array tabela para ordenação
  equipe tab_ordenada[20];  
  for(x = 0; x < qtd_times; x++){
    tab_ordenada[x] = tabela[x];
  }

  // Método de ordenação
  do{
    qtd--;
    trocou = 0;

    // Percorre a tabela e ordena conforme as regras de desempate
    for(i = 0; i < qtd; i++){
      if(tab_ordenada[i].getPontos() < tab_ordenada[i+1].getPontos()){

        // aplica método bolha
        reg_aux = tab_ordenada [i+1];
        tab_ordenada[i+1] = tab_ordenada[i];
        tab_ordenada[i] = reg_aux;
        trocou=1;                
      }else {
        // Em caso, de empate
        if(tab_ordenada[i].getPontos() == tab_ordenada[i+1].getPontos()){
      
          // Por saldo de gols 
          if(tab_ordenada[i].getSaldo() < tab_ordenada[i+1].getSaldo()){
            reg_aux = tab_ordenada [i+1];
            tab_ordenada[i+1] = tab_ordenada[i];
            tab_ordenada[i] = reg_aux;
            trocou = 1;                        
          } else {
          
            // Em caso de empate
            if(tab_ordenada[i].getSaldo() == tab_ordenada[i+1].getSaldo()){
            
              // Por vitória
              if(tab_ordenada[i].getVitorias() < tab_ordenada[i+1].getVitorias()){
                reg_aux = tab_ordenada [i+1];
                tab_ordenada[i+1] = tab_ordenada[i];
                tab_ordenada[i] = reg_aux;
                trocou = 1;                
              } else {              
                // Em caso de empate
                if(tab_ordenada[i].getVitorias() == tab_ordenada[i+1].getVitorias()){
                
                  // Por gols marcados
                  if(tab_ordenada[i].getGolspro() < tab_ordenada[i+1].getGolspro()){
                    reg_aux = tab_ordenada [i+1];
                    tab_ordenada[i+1] = tab_ordenada[i];
                    tab_ordenada[i] = reg_aux;
                    trocou = 1;                
                  }
                }
              }
            }
          }
        }
      }
    }
  }while(trocou);

  // Verifica se o cadastro de equipes já foi realizado
  if (qtd_times > 0) {
    
    // Percorre a tabela demosntrando a classificação
    for (time=0; time < qtd_times; time++)  {    
      cout << " " << time+1 << " - " << tab_ordenada[time].getNome() << "  PG: " << tab_ordenada[time].getPontos() << " V: " << tab_ordenada[time].getVitorias() << " D: " << tab_ordenada[time].getDerrotas() << " E: " << tab_ordenada[time].getEmpates() << " GM: " << tab_ordenada[time].getGolspro() << " GS: " << tab_ordenada[time].getGolscontra() << " S: " << tab_ordenada[time].getSaldo() << endl;
    }
  } else {
    cout << "********** Nenhuma equipe foi cadastrada ************\n\n";
  }

  cout << "-----------------------------------------------------\n\n";
  
  // Grava informações da tabela em arquivo
  gravarTabela();

  // Aguarda o usuário informar alguma tecla
  system("PAUSE");
}

// Procedimento para visualizar o jogos realizados
void torneio::consultar_confrontos()
{ 
  // Limpa a tela
  system("CLS");
  
  // Cabeçalho 
  cout << "-----------------------------------------------------\n";
  cout << "----- Tabela de jogos realizados no Campeonato ------ \n";
  cout << "-----------------------------------------------------\n\n";

  // Percorre a tabela demosntrando os jogos e seus resultados
  int Jogou = 0;  // Flag para saber se jogos foram realizados
  for (partida=0; partida < qtd_partidas; partida++)  {    
    if (jogos[partida].getJogoRealizado() > 0) {
      cout << " " << jogos[partida].getTimeCasa().getNome() << " " << jogos[partida].getTimeCasa().getGolspro() << " X " << jogos[partida].getTimeVisitante().getGolspro() << " " << jogos[partida].getTimeVisitante().getNome() << endl;
      Jogou = 1;
    }
  }

  // Se nenhum jogo realizado, informa
  if(Jogou == 0){
    cout << "************ Jogos nao foram realizados *************\n\n";
  }  
  cout << "-----------------------------------------------------\n\n";

  // Aguarda o usuário informar alguma tecla
  system("PAUSE");
}

// Procedimento para informar o resultado de cada confronto e atualizar a tabela de classificação
void torneio::informar_confrontos()
{  
  int time1;
  int time2;
  partida = 0;

  // Limpa a tela
  system("CLS");
  
  // Cabeçalho 
  cout << "-----------------------------------------------------\n";
  cout << "------------ Realizacao dos Conforntos -------------- \n";
  cout << "-----------------------------------------------------\n\n";

   // Verifica se o cadastro de equipes já foi realizado
  if (qtd_times > 0) {

    // Só permite informar os resultados se jogos não realizados
    if (jogos[0].getJogoRealizado() == 0) {

      // Percorre a tabela identificando os confrontos
      for (time1=0; time1 < qtd_times; time1++)  {    
        for (time2=0; time2 < qtd_times; time2++)  {

          // O mesmo time não pode se enfrentar
          if(tabela[time1].getNome() == tabela[time2].getNome()){
            // Pula para o próximo confronto
            continue;
          }

          // inicializa var
          int gol1=0;
          int gol2=0;
          equipe timeCasa;
          equipe timeVisitante;

          // Define os times 
          timeCasa.setNome(tabela[time1].getNome());
          timeVisitante.setNome(tabela[time2].getNome());
            
          // Demonstra o confronto
          cout << timeCasa.getNome() << " X " << timeVisitante.getNome() << endl;
   
          // Obtem os gols do time da casa
          cin >> gol1;
      
          // Armazena os gols pro do time da casa e contras do time visitante na tabela do campeonato
          tabela[time1].setGolspro(gol1);
          tabela[time2].setGolscontra(gol1);

          // Armazena os gols do confronto
          timeCasa.setGolspro(gol1);
          timeVisitante.setGolscontra(gol1);

          // Obtem os gols do time visitante
          cin >> gol2;

          // Armazena os gols pro do time visitante e contras do time da casa
          tabela[time2].setGolspro(gol2);
          tabela[time1].setGolscontra(gol2);

          // Armazena os gols do confronto
          timeVisitante.setGolspro(gol2);
          timeCasa.setGolscontra(gol2);
      
          // Armazena o jogo na tabela de confrontos
          jogos[partida].setTimeCasa(timeCasa);
          jogos[partida].setTimeVisitante(timeVisitante);
          jogos[partida].setJogoRealizado(1);  // Jogo Realizado

          // Incrementa o número de partidas
          partida++;
      
          // Empate entre os dois times
          if (gol1 == gol2)
          {
            // Soma um empate a mais para os dois times
            tabela[time1].setEmpates(1);
            tabela[time2].setEmpates(1);
      
          } else {

            // Vitória do time da casa
            if(gol1 > gol2)
            {
              // Soma uma vitoria a mais para o time da casa
              tabela[time1].setVitorias(1);

              // Soma uma derrota para o time visitante
              tabela[time2].setDerrotas(1);
        
            } else {
              // Vitória do time visitante
          
              // Soma uma vitoria a mais para o time visitante
              tabela[time2].setVitorias(1);

              // Soma uma derrota para o time da casa
              tabela[time1].setDerrotas(1);
            }
          }
        }
      }

      // Grava informações dos jogos em arquivo
      gravarJogos();
    } else {
      cout << "************ Jogos ja foram realizados **************\n\n";
    }
  } else {
    cout << "********** Nenhuma equipe foi cadastrada ************\n\n";
  }
  cout << "-----------------------------------------------------\n\n";

  // Aguarda o usuário informar alguma tecla
  system("PAUSE");
}

// Procedimento para visualizar os times informados para o campeonato
void torneio::consultar_equipes()
{ 
  // Limpa a tela
  system("CLS");
  
  // Cabeçalho 
  cout << "-----------------------------------------------------\n";
  cout << "-------- Equipes Participantes do Campeonato -------- \n";
  cout << "-----------------------------------------------------\n\n";

  // Verifica se o cadastro de equipes já foi realizado
  if (qtd_times > 0) {

    // Percorre a tabela demosntrando a classificação
    for (time=0; time < qtd_times; time++)  {    
      cout << " " << time+1 << " - " << tabela[time].getNome() << endl;
    }
  } else {
    cout << "********** Nenhuma equipe foi cadastrada ************\n\n";
  }
  cout << "-----------------------------------------------------\n\n";

  // Aguarda o usuário informar alguma tecla
  system("PAUSE");
}

// Procedimento para cadastrar os apostadores e suas apostas
void torneio::informar_bolao(){  

  // Limpa a tela
  system("CLS");

  // Quando não possui equipes cadastradas, cai fora
  if(this->qtd_times == 0){
    cout << "-----------------------------------------------------\n";
    cout << "----------- Nao exitem equipes cadastradas ---------- \n";
    cout << "-----------------------------------------------------\n\n";
    
    // Aguarda o usuário informar alguma tecla
    system("PAUSE");      
  } else {

    // Quando bolão já informado, cai fora
    if(this->qtd_bolao > 0){
      cout << "-----------------------------------------------------\n";
      cout << "----------- Cadastro de bolao ja realizado ---------- \n";
      cout << "-----------------------------------------------------\n\n";
    
      // Aguarda o usuário informar alguma tecla
      system("PAUSE");    
  
    } else {
      // Cabeçalho 
      cout << "-----------------------------------------------------\n";
      cout << "------ Palpites de jogos do Campeonato (Bolao) ------ \n";
      cout << "-----------------------------------------------------\n\n";
  
      // Identifica quantos apostadores devem participar do campeonato
      cout << " Informe a quantidade de apostadores do Bolao (zero para cancelar): ";
      cin >> qtd_bolao;
      cout << "\n";

      // Se informar zero, cancela o cadastro
      if (this->qtd_bolao > 0){

        // Redimenciona o array para a qtde de participantes do bolão
        *palpite = *new bolao[qtd_bolao];
  
        // Armazena no array as apostas de cada participante do bolão  
        for (apostador = 0; apostador < qtd_bolao; apostador++)  {    

          // Identifica o apostador do bolão
          string nomoApostador;
          cout << " Informe o nome do apostador: ";
          cin >> nomoApostador;
          cout << "\n";
          palpite[apostador].setNome(nomoApostador);
    
          // inicializa var
          int time1 = 0;
          int time2 = 0;
          int partida_aposta = 0;
    
          // Percorre a tabela identificando os confrontos por apostador
          for (time1=0; time1 < qtd_times; time1++)  {    
            for (time2=0; time2 < qtd_times; time2++)  {

              // O mesmo time não pode se enfrentar
              if(tabela[time1].getNome() == tabela[time2].getNome()){
                // Pula para o próximo confronto
                continue;
              }    
              // Var. para guardar o palpite do jogo
              confronto palpite_jogo;

              // Var. para armazenar as informações de cada equipe do confronto
              equipe time_Casa;
              equipe time_Visitante;

              // Define os times
              time_Casa.setNome(tabela[time1].getNome());
              time_Visitante.setNome(tabela[time2].getNome());
        
              // Demonstra o confronto
              cout << time_Casa.getNome() << " X " << time_Visitante.getNome() << endl;

              // Var. para ler o palpite do apostador
              int gols_casa;
              int gols_visitante;

              // Obtem o palpite de gols do time da casa
              cin >> gols_casa;
      
              // Obtem o palpite de gols do time visitante
              cin >> gols_visitante;

              // Alimenta as propriedades com os gols de cada equipe
              time_Casa.setGolspro(gols_casa);
              time_Casa.setGolscontra(gols_visitante);
              time_Visitante.setGolspro(gols_visitante);
              time_Visitante.setGolscontra(gols_casa);

              // Armazena o confronto no obj de aposta
              palpite_jogo.setTimeCasa(time_Casa);
              palpite_jogo.setTimeVisitante(time_Visitante);

              // Atualiza a tabela de palpites do apostador
              palpite[apostador].setAposta(partida_aposta, palpite_jogo);
                
              // Incrementa o número de partidas
              partida_aposta++;
            }
          }
          cout << "-----------------------------------------------------\n\n";
        }

        // Grava informações do bolão em arquivo
        gravarBolao();
      } else {
        cout << " Cadastro de bolao cancelado \n\n";
      }  
      // Aguarda o usuário informar alguma tecla
      system("PAUSE");
    }
  }
}

// Procedimento para apurar o vencedor do bolão
void torneio::consultar_vencedor_bolao(){
   // Limpa a tela
  system("CLS");
  
  // Cabeçalho 
  cout << "-----------------------------------------------------\n";
  cout << "---------------- Vencedor do Bolao ------------------ \n";
  cout << "-----------------------------------------------------\n\n";
  cout << "----------------Confrontos Realizados ---------------\n\n";
  
  // Percorre a tabela demosntrando os jogos e seus resultados
  int Jogou = 0;  // Flag para saber se jogos foram realizados
  for (partida=0; partida < qtd_partidas; partida++)  {    
    if (jogos[partida].getJogoRealizado() > 0) {
      cout << " " << jogos[partida].getTimeCasa().getNome() << " " << jogos[partida].getTimeCasa().getGolspro()  << " X " << jogos[partida].getTimeVisitante().getGolspro() << " " << jogos[partida].getTimeVisitante().getNome() << endl;
      Jogou = 1;
    }
  }

  // Se nenhum jogo realizado, informa
  if(Jogou == 0){
    cout << "************ Jogos nao foram realizados *************\n\n";
  }
  cout << "\n----------------- Apostas Realizadas ----------------\n\n";
  
  // Verifica se o bolão já foi cadastrado
  if (qtd_bolao > 0) {
    
    // Mostra a lista de apostadores e apostas
    for (apostador=0; apostador < qtd_bolao; apostador++)  {    
      cout << " Nome do Apostador: " << palpite[apostador].getNome() << endl;
      cout << " ------------------\n";
    
      // Limpa a variável para apurar os pontos atuais
      palpite[apostador].setPontos(0); 
      for (partida=0; partida < qtd_partidas; partida++)  {    

        // Palpite do apostador      
        cout << " " << palpite[apostador].getAposta()[partida].getTimeCasa().getNome() << " " << palpite[apostador].getAposta()[partida].getTimeCasa().getGolspro() << " X " << palpite[apostador].getAposta()[partida].getTimeVisitante().getGolspro() << " " << palpite[apostador].getAposta()[partida].getTimeVisitante().getNome() << endl;

        // Só computa pontuação para jogos realizados
        if (jogos[partida].getJogoRealizado() > 0) {

          // Acertou placar  = 5 pontos
          if (palpite[apostador].getAposta()[partida].getTimeCasa().getGolspro() == jogos[partida].getTimeCasa().getGolspro() && 
              palpite[apostador].getAposta()[partida].getTimeVisitante().getGolspro() == jogos[partida].getTimeVisitante().getGolspro()){
            palpite[apostador].setPontos(palpite[apostador].getPontos() + 5);

          } else {
            // Acertou o vencedor ou empate = 3 pontos
            // Vitória da casa

            if (palpite[apostador].getAposta()[partida].getTimeCasa().getGolspro() > palpite[apostador].getAposta()[partida].getTimeVisitante().getGolspro() && 
                jogos[partida].getTimeCasa().getGolspro() > jogos[partida].getTimeVisitante().getGolspro()){
              palpite[apostador].setPontos(palpite[apostador].getPontos() + 3);

            } else {

              // empate
              if (palpite[apostador].getAposta()[partida].getTimeCasa().getGolspro() == palpite[apostador].getAposta()[partida].getTimeVisitante().getGolspro() && 
                  jogos[partida].getTimeCasa().getGolspro() == jogos[partida].getTimeVisitante().getGolspro()){
                palpite[apostador].setPontos(palpite[apostador].getPontos() + 3);

              } else {
                // Vitória visitante
                if (palpite[apostador].getAposta()[partida].getTimeCasa().getGolspro() < palpite[apostador].getAposta()[partida].getTimeVisitante().getGolspro() && 
                    jogos[partida].getTimeCasa().getGolspro() < jogos[partida].getTimeVisitante().getGolspro()){
                  palpite[apostador].setPontos(palpite[apostador].getPontos() + 3);
                }
              }
            }
          }
        }
      }
      cout << "-----------------------------------------------------\n\n";
    }

    // Var. controle do laço
    bolao reg_aux; 
    int qtd = qtd_bolao;
    int i,trocou;
  
    // Método de ordenação
    do{
      qtd--;
      trocou = 0;

      // Percorre a tabela e ordena por número de pontos
      for(i = 0; i < qtd; i++){
        if(palpite[i].getPontos()  < palpite[i+1].getPontos()){

          // aplica método bolha
          reg_aux = palpite[i+1];
          palpite[i+1] = palpite[i];
          palpite[i] = reg_aux;
          trocou=1;                
        }
      }
    }while(trocou);

    cout << "\n-----------------------------------------------------\n";
    cout << "------------- Classificacao do Bolao ----------------\n";
    cout << "-----------------------------------------------------\n\n";

    // Apresenta o resultado do vencedor
    for (apostador=0; apostador < qtd_bolao; apostador++)  {    
      cout << " " << apostador+1 << " - " << palpite[apostador].getNome() << " = " << palpite[apostador].getPontos() << " pontos" << endl;   
    }
    cout << "-----------------------------------------------------\n\n";
  
    // Grava informações do bolão em arquivo
    gravarBolao();

  } else {
    cout << "*********** Nenhum aposta foi cadastrada ************\n\n\n\n";
  }

  // Aguarda o usuário informar alguma tecla
  system("PAUSE");
}

// Funções para armazenar os dados em arquivo texto
void torneio::gravarTorneios(){
  ofstream arqTorneios;
  arqTorneios.open("torneios.txt",ios_base::app);
  arqTorneios << this->nome << "\n";
  arqTorneios.close();  
}   
void torneio::gravarTabela(){
  ofstream arqTabela;
  arqTabela.open("tabela_" + this->nome + ".txt",ios_base::trunc);
  for (this->time=0; this->time < this->qtd_times; this->time++)  {
    arqTabela << this->tabela[this->time].getRegistro();
  } 
  arqTabela.close();  
}   
void torneio::gravarJogos(){
  ofstream arqJogos;
  arqJogos.open("jogos_" + this->nome + ".txt",ios_base::trunc);
  for (this->partida=0; this->partida < this->qtd_partidas; this->partida++)  {
    arqJogos << this->jogos[this->partida].getRegistro();
  } 
  arqJogos.close();  
}   
void torneio::gravarBolao(){
  ofstream arqBolao;
  // Abre e grava arquivo contendo os participantes do bolão
  arqBolao.open("bolao_" + this->nome + ".txt",ios_base::trunc);
  for (this->apostador=0; this->apostador < this->qtd_bolao; this->apostador++)  {
    arqBolao << this->palpite[this->apostador].getRegistro() << "\n";
    ofstream arqPalpites;   
    // Abre e grava arquivo com as apostas de cada participante do bolão
    arqPalpites.open("palpites_" + this->palpite[this->apostador].getNome() + "_" + this->nome + ".txt",ios_base::trunc);
    for (this->partida=0; this->partida < this->qtd_partidas; this->partida++)  {
      arqPalpites << this->palpite[this->apostador].getAposta()[partida].getRegistro();
    } 
    arqPalpites.close();  
  } 
  arqBolao.close();  
}   

// Funções para resgatar dados dos arquivos
void torneio::carregarTabela(){
  char registro[300];  
  ifstream arqTabela;
  arqTabela.open("tabela_" + this->nome + ".txt",ios_base::app);
  if(!arqTabela.is_open()){
    cout<<"Não foi possível abrir arquivo! Programa será terminado!\n";
    arqTabela.clear(); 
    system("PAUSE"); 
    exit(0);
  }
  this->time = 0;
  while (arqTabela.getline(registro, 300)) {        
    this->tabela[this->time].setRegistro(registro);
    this->time++;
  }
  this->qtd_times = this->time;
  arqTabela.close();
}
void torneio::carregarJogos(){
  char registro[300];  
  ifstream arqJogos;
  arqJogos.open("jogos_" + this->nome + ".txt",ios_base::app);
  if(!arqJogos.is_open()){
    cout<<"Não foi possível abrir arquivo! Programa será terminado!\n";
    arqJogos.clear(); 
    system("PAUSE"); 
    exit(0);
  }
  this->partida = 0;
  while (arqJogos.getline(registro, 300)) {        
    this->jogos[this->partida].setRegistro(registro);
    this->partida++;
  }
  if(this->partida==0) {
    this->qtd_partidas = (this->qtd_times-1) * this->qtd_times;
  } else {
    this->qtd_partidas = this->partida;
  }
  arqJogos.close();
}
void torneio::carregarBolao(){
  char registro[300];  
  ifstream arqBolao;
  arqBolao.open("bolao_" + this->nome + ".txt",ios_base::app);
  if(!arqBolao.is_open()){
    cout<<"Não foi possível abrir arquivo! Programa será terminado!\n";
    arqBolao.clear(); 
    system("PAUSE"); 
    exit(0);
  }
  this->apostador = 0;
  while (arqBolao.getline(registro, 300)) {        
    this->palpite[this->apostador].setRegistro(registro);

    char regAposta[300];  
    ifstream arqAposta;
    arqAposta.open("palpites_" + this->palpite[this->apostador].getNome() + "_" + this->nome + ".txt");
    if(!arqAposta.is_open()){
      cout<<"Não foi possível abrir arquivo! Programa será terminado!\n";
      arqAposta.clear(); 
      system("PAUSE"); 
      exit(0);
    }
    this->partida = 0;
    while (arqAposta.getline(regAposta, 300)) {        
      this->palpite[this->apostador].getAposta()[partida].setRegistro(regAposta);
      this->partida++;
    }
    arqAposta.close();
    this->apostador++;
  }
  this->qtd_bolao = this->apostador;
  arqBolao.close();
}