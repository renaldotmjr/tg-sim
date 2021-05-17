/*######################################################################*/
/*##                                                                  ##*/
/*##             Tg-Sim 1.5 - Teoria de Grupos e Simetria             ##*/
/*##                                                  Marco de 2015   ##*/
/*######################################################################*/
/*#######################################################################*/
/*##                                                                   ##*/
/*##         RTE 1.5 - Reducao de Termos Espectroscopicos              ##*/
/*##                                                    Marco de 2015  ##*/
/*##                                                                   ##*/
/*## Data de alteracao: 16/04/2015                                     ##*/
/*#######################################################################*/
/*##              ***  Latest modifications ***                        ##*/
/*##   -> Traducao para o ingles - OK                                  ##*/
/*##   -> Correcao para configuracoes triplas - OK                     ##*/
/*##                                                                   ##*/
/*#######################################################################*/
/*##  Universidade Federal de Pernambuco - UFPE                        ##*/
/*##       Departamento de Química Fundamental - DQF                   ##*/
/*##                                                                   ##*/
/*##  Universidade Federal Rural de Pernambuco - UFRPE                 ##*/
/*##       Unidade Academica de Serra Talhada - UAST                   ##*/
/*##                                                                   ##*/
/*##                                                                   ##*/
/*## Este programa visa o preenchimento logico de orbitais, incluindo  ##*/
/*## efeito de spin e o princípio da construcao.                       ##*/
/*## Como parâmetros de entrada o usuário deve fornecer o orbital      ##*/
/*## (s, p, d, f ou g) e a quantidade de eletrons a serem distribuidos.##*/
/*##                                                                   ##*/
/*## Com estes valores o programa retorna os termos espectrocopicos da ##*/
/*## configuracao informada, seja ela composta por um único orbital ou ##*/
/*## por dois orbitais. Os termos espectroscópicos sao ordenados       ##*/
/*## energeticamente segundo a regra de Hund e tambem sao mostrados    ##*/
/*## seus desdobramentos devido ao acoplamento spin-orbital.           ##*/
/*##                                                                   ##*/
/*##                                                                   ##*/
/*#######################################################################*/
/*##                                  E. C. Aguiar e R. T. Moura Jr.   ##*/
/*#######################################################################*/



   /*#####################################################################*/
   /*#           Inicio de diretivas de pre-processamento                #*/
   /*#####################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Lib/abertura.h"
#include "Lib/globals.h"
#include "Lib/tg_sim.h"
#include "Lib/tg_sim_html.h"
#include "Lib/readtable.h"


/*#############################################################################*/
/*#                   int main(int argc, char *argv[])                        #*/
/*#                                                                           #*/
/*# Function que recebe como argumentos o TE, Grupo Pontual e a Configuracao  #*/
/*#  que gerou o TE. Caso tais argumentos nao sejam informados na linha de    #*/
/*#   comando, o programa pede ao usuário para que entre com os parâmetros.   #*/
/*#############################################################################*/

int main(int argc, char *argv[]) {

    int _J = 0,   // Multiplicidade do termo espectroscópico; (2S + 1)
        _L = 0;   // Somatorio maximo dos ml de uma configuração

    float _MTX_REP_RED[15],   // Array que contém a representação redutível do sistema
    	  _MTX_NCLASSE[15],	  // Matriz com o número de elementos de cada classe do grupo
    	  _MTX_COEF_RI[15],   //
          _H = 0;			  // Ordem do Grupo


    int i = 0, ii = 0;        // Contadores 'for'
    int paridade = 0,         // Define a paridade do Termo Espectroscópico, assume valor 1 para 'par' e -1 para 'impar'
        _Classe,
        no_e;                 // Número de eletrons da configuracao fornecida pelo usuario

    char _TERMO[3],                   // string que guarda o termo espectroscópico fornecido pelo usuário
         _MULTIPLICIDADE[4],          // string que guarda a multiplicidade fornecida pelo usuário
         _termo = 'a',                // Caracter que representa o L do termo
         _GP[3],                      // Grupo Pontual fornecido pelo usuario
         ch,                          // Caractere de escolha
         _CONF[3],                    // String que guarda a configuracao fornecida pelo usuário
         _ELET[3],                    // String que guarda o número de elétrons da configuração 
         orbital;                     // Caractere que define o orbital da configuração fornecida pelo usuário 

    
    
    
    // Initializing prints
    F_ABERTURA();
    

    // Se o usuario quiser dar argumentos...
    if ( argc == 4){
     
         strcpy(_TERMO, argv[1]);             // passando o argumento para a string _TERMO
         strcpy(_MULTIPLICIDADE, argv[1]);    // passando o argumento para a string _MULTIPLICIDADE - vai conter a multiplicidade do termo
         strcpy(_GP, argv[2]);                // passando o argumento para a string _GP
         strcpy(_CONF, argv[3]);              // passando o argumento para a string CONF_1
         strcpy(_ELET, argv[3]);              // passando o argumento para a string ELET_1 - vai conter o número de elétrons do primeiro orbital 

         _MULTIPLICIDADE[3] = '0';            // setando o valor do L do termo igual a zero
         _J = atoi(_MULTIPLICIDADE);          // Transfoma caracter em numero inteiro
         _termo = _TERMO[1];                  // Associa a váriavel _termo ao caracter que representa o L do termo espectroscópico

         _ELET[0] = '0';                      // setando o valor da casa do orbital igual a zero 
         no_e = atoi(_ELET);                  // Transfoma caracter em número inteiro 
         orbital = _CONF[0];
    }
     
    // se nao der argumentos...
    else {

         printf("\n\nType the Spectroscopic Term (Term Symbol), the Point Group and the electronic configuration!\n"); // 
         printf("e.g.: 1D Oh d2");
         printf("\n\n->");
         scanf("%s %s %s", _TERMO, _GP, _CONF);
     
         strcpy(_MULTIPLICIDADE, _TERMO);
         _MULTIPLICIDADE[3] = '0';            // setando o valor do L do termo igual a zero
         _J = atoi(_MULTIPLICIDADE);          // Transfoma caractere em numero inteiro
         _termo = _TERMO[1];                  // Associa a variavel _termo ao caracter que representa o L do termo espectroscopico

         strcpy(_ELET, _CONF);                // passando o argumento para a string ELET_1 - vai conter o número de elétrons do primeiro orbital 
         _ELET[0] = '0';                      // setando o valor da casa do orbital igual a zero 
         no_e = atoi(_ELET);                  // Transfoma caracter em número inteiro 
         orbital = _CONF[0];
    }


    // Testa se o caracter referente ao termo esta na segunda ou primeira casa da string
    if ( _termo == 'S'|| _termo == 'P'|| _termo == 'D'|| _termo == 'F'|| _termo == 'G'|| _termo == 'H'||
         _termo == 'I'|| _termo == 'K'|| _termo == 'L'|| _termo == 'M'|| _termo == 'N'|| _termo == 'O'||
         _termo == 'Q'|| _termo == 'R'|| _termo == 'T'|| _termo == 'U'|| _termo == 'V'|| _termo == 'W'||
         _termo == 'X'|| _termo == 'Y'|| _termo == 'Z'|| _termo == 'A'|| _termo == 'B'|| _termo == 'C'||
         _termo == 'E' ) {
    }

    else {
        _termo = _TERMO[2];
    }

    // Compara a entrada do usuário com um L conhecido e associa a entrada alfanumérica a um algarismo
    switch(_termo) {

            case 'S':  _L = 0;  break;
            case 'P':  _L = 1;  break;
            case 'D':  _L = 2;  break;
            case 'F':  _L = 3;  break;
            case 'G':  _L = 4;  break;
            case 'H':  _L = 5;  break;
            case 'I':  _L = 6;  break;
            case 'K':  _L = 7;  break;
            case 'L':  _L = 8;  break;
            case 'M':  _L = 9;  break;
            case 'N':  _L = 10; break;
            case 'O':  _L = 11; break;
            case 'Q':  _L = 12; break;
            case 'R':  _L = 13; break;
            case 'T':  _L = 14; break;
            case 'U':  _L = 15; break;
            case 'V':  _L = 16; break;
            case 'W':  _L = 17; break;
            case 'X':  _L = 18; break;
            case 'Y':  _L = 19; break;
            case 'Z':  _L = 20; break;
            case 'A':  _L = 21; break;
            case 'B':  _L = 22; break;
            case 'C':  _L = 23; break;
            case 'E':  _L = 24; break;
            
            default:      // Entrada invalida ou incompleta
            
                 printf("\n\tHow to use:\n");
            
                 printf("Type: %s <Spectroscopic Term> <Point Group> <electonic configuration>\n\n",argv[0]);
            
                 printf("Examples:\n");
                 printf("    %s 3D C2v f4", argv[0]);
                 printf("    %s 1G Td d2", argv[0]);
            
                 break;
    }

    printf("\nSpectroscopic Term: %s", _TERMO);
    printf("\nL = %d  ;  2S+1 = %d", _L, _J);
    printf("\nPoint Group: %s", _GP);
    printf("\nElectronic Conf.: %s", _CONF);
    
    // Definindo a paridade da configuracao
    paridade = F_PARITY(orbital, no_e);
    printf("\n    P-> Parity of electronic configuration = %d\n", paridade);

    
    /*##################################################*/
    /*#  Inicio do calculo da Representacao Redutivel  #*/
    /*##################################################*/
    
    
    // Zera as matrizes que contem as representacoes irredutivel e redutivel
    for(i=0; i<=15; i++) {
        _MTX_REP_RED[i] = 0.0;
        _MTX_COEF_RI[i] = 0.0;
    }
    

    printf("\nReading the Character Tables...");
    // Le as rotacoes referentes a cada operacao de simetria do Grupo escolhido
    F_READ_TABLE(_GP, "Teta");
    
    printf("  Done!\n");
    

    // Calcula os tracos de cada operacao de simetria aplicadas no termo
    // Encontrando, assim, a representacao redutivel
    for (i = 2; i <= _MTX_CHAR[0]; i++){

          if (_MTX_ELEM[i][0] == 'i') {
              _MTX_REP_RED[i] = (2*_L +1)*paridade;
          }
          else 
              _MTX_REP_RED[i] = F_BETHE(_L,_MTX_CHAR[i]);
        
        
          if (_MTX_ELEM[i][0] == 'S')
              _MTX_REP_RED[i] = _MTX_REP_RED[i]*paridade;
          else;
    }
    

    _MTX_REP_RED[0] = _MTX_CHAR[0];  // Adiciona a representacao redutivel o numero de classes do grupo

    _MTX_REP_RED[1] = (2*_L + 1);    // Adiciona a representacao redutivel o traco referente a operacao 'E'

    /*###################################################*/
    /*#    Fim do calculo da Representacao Redutivel    #*/
    /*###################################################*/

    printf("\n\nReducible Representation: \n");
    printf("    Number of characters: %.1f \n",_MTX_CHAR[0]);
    printf("    T(%s): ", _TERMO);

    for( i=1; i<= _MTX_CHAR[0]; i++) {
              printf("%8.1f", _MTX_REP_RED[i]);
    }
    printf("\n");


    /*#####################################################*/
    /*# Inicio da decomposicao da Representacao Redutivel #*/
    /*#####################################################*/

	F_READ_TABLE(_GP, "nelet");			// Gera uma matriz com o valor dos elementos de cada classe do grupo

    for(i=0; i<=15; i++){
             _MTX_NCLASSE[i] = _MTX_CHAR[i];
    }

    _Classe = _MTX_NCLASSE[0];

    _H = F_SOMAMTX(_Classe, _MTX_NCLASSE);	// Fornece a Ordem do Grupo

	// Gera uma matriz com os coeficientes multiplicativos referente a decomposicao da rep. redutivel nas irredutiveis do grupo
	for(i = 1; i <= _MTX_RI[0][0]; i++) {

			F_READ_TABLE(_GP, _MTX_RI[i]);

    		for(ii = 1; ii <= _MTX_NCLASSE[0]; ii++) {

					_MTX_COEF_RI[i] = _MTX_COEF_RI[i] + F_GTO(_H, _MTX_NCLASSE[ii], _MTX_REP_RED[ii], _MTX_CHAR[ii]);
            }
    }


    /*#####################################################*/
    /*#   Fim da decomposcao da Representacao Redutivel  #*/
    /*#####################################################*/

    printf("\n\nThe %s term in a %s symmetry field yields the follow energy levels:\n\n", _TERMO, _GP);
    printf("G = ");

    for(i = 1; i <=_MTX_NCLASSE[0]; i++) {

			if (i != _MTX_NCLASSE[0])
					printf("%.0f%s + ", _MTX_COEF_RI[i], _MTX_RI[i]);

			else
					printf("%.0f%s", _MTX_COEF_RI[i], _MTX_RI[i]);

    }

    F_FILE_HTML(_TERMO, _GP, _CONF, _J, _L, _MTX_ELEM, _MTX_REP_RED, _MTX_CHAR[0], _MTX_COEF_RI, _MTX_RI, paridade);

} // Fim de int main(int argc, char *argv[])
