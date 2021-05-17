/*######################################################################*/
/*##                                                                  ##*/
/*##             Tg-Sim 1.5 - Teoria de Grupos e Simetria             ##*/
/*##                                                  Marco de 2015   ##*/
/*######################################################################*/
/*#######################################################################*/
/*##                                                                   ##*/
/*##         PTE 1.5 - Programa de Termos Espectroscopicos             ##*/
/*##                                                    Marco de 2015  ##*/
/*##                                                                   ##*/
/*## Data de alteracao: 05/03/2015                                     ##*/
/*#######################################################################*/
/*##              ***  Latest modifications ***                        ##*/
/*##   -> Traducao para o ingles - OK                                  ##*/
/*##   -> Correcao para configuracoes triplas - OK                     ##*/
/*##   -> Better code modulation                                       ##*/
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
/*## efeito de spin e o principio da construcao.                       ##*/
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

/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "Lib/abertura.h"
#include "Lib/globals.h"
#include "Lib/microestados.h" // cabecalho com as funcoes que geram os microestados e computam na matriz resultados
#include "Lib/interpret.h"    // cabecalho com as funcoes que interpretam a matriz resultados
#include "Lib/genmicrost.h"
#include "Lib/confsimple.h"
#include "Lib/confdouble.h"
#include "Lib/conftriple.h"


   /*#####################################################################*/
   /*#                int main(int argc, char *argv[])                   #*/
   /*#                                                                   #*/
   /*#  Function que pega como argumento na linha de comando 'argv'.     #*/
   /*# Esta variavel seta o modo de como o programa deve rodar, ou seja, #*/
   /*# identifica o tipo (simples ou mista) e a configuracao fornecida.  #*/
   /*#                                                                   #*/
   /*#####################################################################*/

int main(int argc, char *argv[]) {          // argc = quantos argumentos foram passados
                                            // argv = matriz com os argumentos
    double start;                         // variável de contagem de tempo de cpu
    double stop;                           // variável de contagem de tempo de cpu


    // iniciando contagem do tempo de cpu
    start = (double)clock()/CLOCKS_PER_SEC;
    
    int no_e_1 = 1,         // Número de elétrons, entrada do usuário
        no_e_2 = 1,         // Número de elétrons do segundo orbital, entrada do usuário
		no_e_3 = 1;			// Número de elétrons do terceiro orbital, entrada do usuário


    char CONF_1[4],         // string que guarda a configuração
         CONF_2[4],
		 CONF_3[4],
         ELET_1[4],         // string que guarda o número de elétrons
         ELET_2[4],
		 ELET_3[4],
         orbital_1 = 'a',   // Orbital 's', 'p', 'd', 'f' ou 'g', entrada do usuário
         orbital_2 = 'a',   // Orbital 's', 'p', 'd', 'f' ou 'g', entrada do usuário
		 orbital_3 = 'a',	// Orbital 's', 'p', 'd', 'f' ou 'g', entrada do usuário
         _print_mtx,            // variavel que assume valor '1' pra imprimir matrizes e '0' se nao
         _print_micro;          // variavel que assume valor '1' pra imprimir microestados e '0' se nao




    F_ABERTURA();

//    printf("\n\n _print_mtx=%c, %d ||| _print_micro=%c, %d\n\n", _print_mtx, _print_mtx, _print_micro, _print_micro);

    switch(argc) {

           // Selecao de orbital simples
           case 4:
                _print_mtx = *argv[argc - 2]; // passando o valor de entrada para _print_mtx
                _print_micro = *argv[argc - 1]; // passando o valor de entrada para _print_micro

                strcpy(CONF_1, argv[1]);      // passando o argumento para a string CONF_1
                strcpy(ELET_1, argv[1]);      // passando o argumento para a string ELET_1 - vai conter o número de elétrons do primeiro orbital
                ELET_1[0] = '0';              // setando o valor da casa do orbital igual a zero
                no_e_1 = atoi(ELET_1);        // Transfoma caracter em número inteiro
                orbital_1 = CONF_1[0];
                strcat(CONF_TOTAL, argv[1]);
            
                CONF_SIMPLE(_print_mtx, _print_micro, orbital_1, no_e_1);
                break;

           // Selecao de orbital duplo
           case 5:
                _print_mtx = *argv[argc - 2]; // passando o valor de entrada para _print_mtx
                _print_micro = *argv[argc - 1]; // passando o valor de entrada para _print_micro

                strcpy(CONF_1, argv[1]);      // passando o argumento para a string CONF_1
                strcpy(CONF_2, argv[2]);      // passando o argumento para a string CONF_2
                strcpy(ELET_1, argv[1]);      // passando o argumento para a string ELET_1 - vai conter o numero de eletrons do primeiro orbital
                strcpy(ELET_2, argv[2]);      // passando o argumento para a string ELET_2 - vai conter o numero de eletrons do segundo orbital
                ELET_1[0] = '0';              // setando o valor da casa do orbital igual a zero
                ELET_2[0] = '0';
                no_e_1 = atoi(ELET_1);
                no_e_2 = atoi(ELET_2);
                orbital_1 = CONF_1[0];
                orbital_2 = CONF_2[0];
                strcat(CONF_TOTAL, argv[1]);
                strcat(CONF_TOTAL, argv[2]);
                
                CONF_DOUBLE(_print_mtx, _print_micro, orbital_1, no_e_1, orbital_2, no_e_2);
                break;

            // Selecao de orbital triplo
	        case 6:
                _print_mtx = *argv[argc - 2]; // passando o valor de entrada para _print_mtx
                _print_micro = *argv[argc - 1]; // passando o valor de entrada para _print_micro

	            strcpy(CONF_1, argv[1]);      // passando o argumento para a string CONF_1
	            strcpy(CONF_2, argv[2]);      // passando o argumento para a string CONF_2
	            strcpy(CONF_3, argv[3]);      // passando o argumento para a string CONF_3
	            strcpy(ELET_1, argv[1]);      // passando o argumento para a string ELET_1 - vai conter o numero de eletrons do primeiro orbital
	            strcpy(ELET_2, argv[2]);      // passando o argumento para a string ELET_2 - vai conter o numero de eletrons do segundo orbital
	            strcpy(ELET_3, argv[3]);      // passando o argumento para a string ELET_3 - vai conter o numero de eletrons do terceiro orbital
	            ELET_1[0] = '0';              // setando o valor da casa do orbital igual a zero
	            ELET_2[0] = '0';
				ELET_3[0] = '0';
	            no_e_1 = atoi(ELET_1);
	            no_e_2 = atoi(ELET_2);
	            no_e_3 = atoi(ELET_3);
	            orbital_1 = CONF_1[0];
	            orbital_2 = CONF_2[0];
	            orbital_3 = CONF_3[0];
                strcat(CONF_TOTAL, argv[1]);
                strcat(CONF_TOTAL, argv[2]);
                strcat(CONF_TOTAL, argv[3]);
                
	            CONF_TRIPLE(_print_mtx, _print_micro, orbital_1, no_e_1, orbital_2, no_e_2, orbital_3, no_e_3);
	            break;

           // Entrada invalida ou incompleta
           default:
                printf("\nUSAGE INSTRUCTIONS:\n\n");
                printf("  Define the electronic configuration right after program name and\n");
                printf("  the print options after the electronic configuration:\n\n");
            
                printf("Command line:\n");
                printf("%s <conf> [<O1Ne1> <O2Ne2> <O3Ne3>] <PrtAnwserMtx> <PrtMicrostates>\n\n", argv[0]);
            
                printf("Options:\n");
                printf("    <conf>           --> The electronic configuration up to triple mixing\n");
                printf("       <OxNex>       --> Each orbital type and number of electrons\n");
                printf("    <PrtAnwserMtx>   --> Print each Ms/Ml matrix\n");
                printf("    <PrtMicrostates> --> Print each microstate vector\n\n");
                
                printf("Electronic Configurations:\n");
                printf("    [s1], [d7], [f10]... Single orbital <OrbtalNumberOfElectrons>\n");
                printf("    [s1 p1], [f7 f7]... Two orbitals <Orbtal1NumberOfElectrons1> <Orbtal2NumberOfElectrons2>\n");
                printf("    [p4 d1 s1]... Three orbitals <Orbtal1NumberOfElectrons1> <Orbtal2NumberOfElectrons2> <Orbtal3NumberOfElectrons3>\n\n");
                
                printf("    Valid orbitals: 's', 'p', 'd', 'f' and 'g' (l = 0, 1, 2, 3 and 4, respectvely)\n");
                printf("    Valid numer of electons in each orbital is an integer between 1 and 2*(2*l+1)\n\n");
                
                printf("Print Options:\n");
                
                printf("    <PrtAnwserMtx>\n");
                printf("       [0] - do not print the Anwser Matrix on every step\n");
                printf("       [1] - print the Anwser Matrix on every step (might become disk consuming... be careful)\n");
                       
                printf("    <PrtMicrostates>\n");
                printf("       [0] - do not print the configuration microstates\n");
                printf("       [1] - print the configuration microstates (might become disk consuming... be careful)\n\n");
                
                printf("Examples:\n");
                
                printf("Single configuration (np4) without printing:\n");
                printf("    %s p4 0 0 > conf_p4.txt\n\n", argv[0]);
                printf("Two orbitals configuration (d5s1) printing microstates:\n");
                printf("    %s d5 s1 0 1 > conf_d5s1.txt\n\n", argv[0]);
                printf("Three orbitals configuration (s1p2d6) full printing:\n");
                printf("    %s s1 p2 d6 1 1 > conf_s1p1d6.txt\n", argv[0]);

                break;

           }
    
           // finalizando contagem do tempo de cpu
           stop = (double)clock()/CLOCKS_PER_SEC;
    
           printf("\n\nJob completed!\n");
    
           printf("Elapserd time: %g s \n\n", stop-start );

    return 0;
} // fim da main

