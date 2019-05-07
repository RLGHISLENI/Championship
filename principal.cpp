/**************************************************************
 ********* Trabalho Prático Grau B                    *********
 ********* Algoritmos e Programação C++               *********
 ********* Simulação e Bolão do Campeonato Brasileiro *********
 ********* Aluno: Roberto Luis Ghisleni               ********* 
 **************************************************************/

// Definição das referências utilizadas 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

// Definição de classes utilizadas
#include "equipe.h"
#include "confronto.h"
#include "bolao.h"
#include "torneio.h"

// Define o namespace
using namespace std;

// Variáveis de controle
int qtd_torneio = 0;
int indexTorneio = 0;

// Array para armazenar varios campeonatos
torneio comopeticao[20];

// Procedimentos utilizados na aplicação
void menuPrincipal();
void menuCompeticao();
void novoCampeonato();
void carregarTorneios();

// Processo principal
int main()
{   
  // Mostra o menu de opções 
  menuPrincipal();  

  // Encerra a execução
  return 0;
}

// Procedimento para realizar a montagem do menu de opções do programa
void menuPrincipal()
{
  // Limpa tela
  system("cls");

   // Cabeçalho 
  cout << "-----------------------------------------------------\n";
  cout << "------------------- Menu de opcoes  ----------------- \n";
  cout << "-----------------------------------------------------\n\n";
   
  // Demosntra o menu e solicita a opção escolhida
  int op_escolhida;
  cout << " Escolha a opcao desejada\n";
  cout << " ------------------------\n\n";  
  cout << "   1 - Novo campeonato\n";

  // Carrega dinamicamente os campeonatos cadastrados
  carregarTorneios();  

  cout << "   0 - Sair\n\n";
  cout << " Opcao: ";

  // Lê a opção 
  cin >> op_escolhida;

  // Executa a ação escolhida pelo usuário
  switch (op_escolhida){
    case 0: // Finaliza
      exit(0);
      break;

    case 1: // Cria nova estrutura
      novoCampeonato();
      break;

    default:
      // Define o indice do campeonato no array
      indexTorneio = (op_escolhida-2);

      // Se informou uma opção inválida, cai fora
      if (comopeticao[indexTorneio].getNome() != "") {

        // Carrega todos os dados já informados para o campeonato selecionado
        comopeticao[indexTorneio].carregarTabela();
        comopeticao[indexTorneio].carregarJogos();
        comopeticao[indexTorneio].carregarBolao();

        // Mostra o menu de opções de cada campeonato
        menuCompeticao();

      } else {
        // Finaliza
        exit(0);      
      }
      break;
  }
}

// Procedimento para realizar a montagem do menu de opções de cada campeonato
void menuCompeticao()
{
  // Limpa tela
  system("cls");

   // Cabeçalho 
  cout << "-----------------------------------------------------\n";
  cout << "------------ Menu de opcoes do Campeonato ----------- \n";
  cout << "-----------------------------------------------------\n\n";
  cout << " Nome do Campeonato: " + comopeticao[indexTorneio].getNome() + "\n\n"; 
  
  // Demosntra o menu e solicita a opção escolhida
  int op_escolhida;
  cout << " Escolha a opcao desejada\n";
  cout << " ------------------------\n\n";
  cout << "   1 - Informar equipes\n";
  cout << "   2 - Visualizar equipes\n";
  cout << "   3 - Informar confrontos\n";
  cout << "   4 - Visualizar confrontos\n";
  cout << "   5 - Visualizar classificacao\n";
  cout << "   6 - Informar aposta bolao\n";
  cout << "   7 - Visualizar vencedor bolao\n";
  cout << "   0 - Voltar\n\n";
  cout << " Opcao: ";

  // Lê a opção 
  cin >> op_escolhida;

  // Executa a ação escolhida pelo usuário
  switch (op_escolhida){
    case 1:
      comopeticao[indexTorneio].cadastrar_equipes();      
      menuCompeticao();
      break;
    case 2:
      comopeticao[indexTorneio].consultar_equipes();
      menuCompeticao();
      break;
    case 3:
      comopeticao[indexTorneio].informar_confrontos();
      menuCompeticao();
      break;
    case 4:
      comopeticao[indexTorneio].consultar_confrontos();
      menuCompeticao();
      break;
    case 5:
      comopeticao[indexTorneio].consultar_classificacao();
      menuCompeticao();
      break;
    case 6:
      comopeticao[indexTorneio].informar_bolao();
      menuCompeticao();
      break;
    case 7:
      comopeticao[indexTorneio].consultar_vencedor_bolao();
      menuCompeticao();
      break;
    default:
      menuPrincipal();
      break;
  }
}

// Procedimento para inclusão de uma nova competição
void novoCampeonato(){
  // Limpa tela
  system("CLS");

  // Cabeçalho 
  cout << "-----------------------------------------------------\n";
  cout << "------------ Inclusao de Novo Campeonato ------------ \n";
  cout << "-----------------------------------------------------\n\n";
   
  // Demosntra o menu e solicita a opção escolhida
  string nomeNovoCampeopnato;
  cout << " Informe um nome para o novo campeonato ou sair: ";

  // Lê o nome do campeonato
  cin >> nomeNovoCampeopnato;
  
  // Testa condição de saída
  if(nomeNovoCampeopnato == "sair"){

    // Volta ao início
    system("CLS");
    menuPrincipal();

  } else {
    // Incrementa e defino o indice do array de campeonato
    qtd_torneio++; 
    indexTorneio = qtd_torneio;

    // Define o nome do campeonato
    comopeticao[indexTorneio].setNome(nomeNovoCampeopnato);

    // Grava as informações em arquivo
    comopeticao[indexTorneio].gravarTorneios();

    // Chama o menu de opções de cada campeonato
    menuCompeticao();
  }
}

// Procedimento para carregar os campeonatos já cadastrados e armazenados em arquivo
void carregarTorneios(){
  // Var. para guardar a linha do arquivo
  char nomeTorneio[300];

  // Abre o arquivo para leitura
  ifstream arquivo;
  arquivo.open("torneios.txt",ios_base::app);
  
  // Validação básica para saber se foi possível abrir o arquivo
  if(!arquivo.is_open()){
    cout<<"Não foi possível abrir arquivo! Programa será terminado!\n";
    arquivo.clear(); 
    system("PAUSE");     
    exit(0); // Encerra o programa
  }

  // Inicializa com 2, pois a opção 1 é para criação de novos campeonatos
  qtd_torneio = 2;

  // Percorre as linhas do arquivo
  while (arquivo.getline(nomeTorneio, 300)) {        

    // Monta a opção de menu do campeonato
    cout << "   " << qtd_torneio << " - " << nomeTorneio <<"\n";

    // Carrega o nome do campeonato para o array
    comopeticao[qtd_torneio-2].setNome(nomeTorneio);

    // Incrementa
    qtd_torneio++;
  }

  // Define o total de campeonatos existentes no array
  qtd_torneio = qtd_torneio - 3;
  
  // Fecha arquivo
  arquivo.close();
}