/*######################################################################*/
/*##                            microestados.h                        ##*/
/*##                                                                  ##*/
/*## Arquivo de cabeçalho contendo as funções F_MS, F_ML, F_FATORIAL, ##*/
/*##  F_NMET e F_NME, necessárias para a compilacao do codigo-fonte   ##*/
/*##                             PTE.C                                ##*/
/*##                                                                  ##*/
/*######################################################################*/
/*##           PTE-SG v1.4 - Programa de Termos Espectroscópicos      ##*/
/*##                                                                  ##*/
/*##  Data da versao: 2015                                            ##*/
/*##                                                                  ##*/
/*##                                                                  ##*/
/*##                                                                  ##*/
/*##                                      PTE - SG - Janeiro de 2015  ##*/
/*######################################################################*/
/*##                                  E. C. Aguiar e R. T. Moura Jr.  ##*/
/*######################################################################*/

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

/*#########################################################################*/
/*#                    int F_FATORIAL( int number )                       #*/
/*#                                                                       #*/
/*#  Function que calcula o fatorial do argumento 'number', retornando-o  #*/
/*# em 'vfat', sendo ambos inteiros. Caso 'number = 0' a função retorna 1 #*/
/*#########################################################################*/

double F_FATORIAL( int number ) {

    int i = 0;  // Contador 'for'
    double vfat = 1.0;   // Resultado caso number = 0 ou 1

    // Calculo do fatorial
    for ( i = number; i > 0 ; i-- ) {
        vfat = vfat*i;        // vfat = number*(number -1)*(number -1 -1)...
        }

    return(vfat);
}

/*#########################################################################*/
/*#               int F_MS( int ORB, int MTX_ms[ORB] )                    #*/
/*#                                                                       #*/
/*#Function que calcula o momento de spin (Ms) de um microestado fornecido#*/
/*#    como argumento da funcao ( MTX_ms[ORB] ). A function retorna 'Ms'  #*/
/*#########################################################################*/

int F_MS( int ORB, int MTX_ms[ORB] ) {

      int i;   // Contador 'for'
      int Ms = 0;  // Valor do momento de spin do microestado fornecido em MTX_ms

// Contribuição dos spins positivos
      for(i = 0; i < ORB/2; i++) {
             Ms = Ms + (MTX_ms[i]);
             }

// Contribuição dos spins Negativos
      for(i = ORB/2; i < ORB; i++) {
             Ms = Ms - (MTX_ms[i]);
             }

      return Ms;
}

/*#########################################################################*/
/*#       int F_ML( int ORB, int MTX_ms[ORB], int MTX_ml[ORB] )           #*/
/*#                                                                       #*/
/*#    Function que calcula o momento magnético (Ml) de um microestado    #*/
/*#    fornecido como argumento da função ( MTX_ms[ORB] e MTX_ml[ORB]).   #*/
/*#                       A function retorna 'Ml'                         #*/
/*#########################################################################*/

int F_ML( int ORB, int MTX_ms[ORB], int MTX_ml[ORB] ) {

      int i;       // Contador 'for'
      int Ml = 0;      // Valor do momento de ângular do microestado fornecido em MTX_ms

      for(i = 0; i < ORB; i++) {
              Ml = Ml + (MTX_ms[i])*(MTX_ml[i]);
              }

      return Ml;
}

/*#########################################################################*/
/*#               double F_NMET( int ORB, int no_e )                      #*/
/*#                                                                       #*/
/*#   Function que calcula o número de microestados de uma configuração   #*/
/*#   formada pelos argumentos 'ORB' e 'no_e'. A Function retorna NmeT.   #*/
/*#########################################################################*/

double F_NMET ( int ORB, int no_e ) {

    double NmeT = 0.0;

    NmeT = (F_FATORIAL(ORB) / (F_FATORIAL(ORB - no_e)*F_FATORIAL(no_e)));

    return NmeT;
}


/*#########################################################################*/
/*#                 double F_NME( int ml, int ms )                        #*/
/*#                                                                       #*/
/*#  Function que calcula o número de microestados de um termo descrito   #*/
/*#      pelos argumentos 'ml' e 'ms'. A Function retorna 'Nme'.          #*/
/*#########################################################################*/

double F_NME( int ms, int ml ) {

    double Nme = 0.0;

    Nme = ( ms + 1 )*(2*ml + 1 );

    return Nme;
}

/*#############################################################################*/
/*#                   int copy_MTX( int MTX_2, int MTX_1)                     #*/
/*#                                                                           #*/
/*#  Function que copia o conteudo de uma matriz numerica inteira para outra. #*/
/*#############################################################################*/
void copy_MTX( int MTX_2[NmeT_MAX], int MTX_1[NmeT_MAX] ) {
    
    int i;    //contador 'for'
    
    for(i = 0; i < NmeT_MAX; i++) {
        MTX_2[i] = MTX_1[i];
    }
}

/*#######################################################################
 # int F_SOMAMTX(int linha, int coluna, int MTX[coluna][lilnha+1])       #
 #                                                                       #
 #  Function que calcula o somatorio dos elementos de uma matriz dada    #
 #  O nº de linhas e colunas a serem somados sao os argumentos 'linha'   #
 #             e 'coluna'.  A Function retorna 'result'.                 #
 #########################################################################*/

float F_SOMAMTX(int linha, int coluna, int MTX[coluna][linha+1]){
    
    int i, ii ;                     // contadores 'for'
    float result=0;                 // resultado do somatório
    int L_lim = 0;                  // valor máximo de 'L'
    float S_lim = 0;                // valor máximo de 'S'
    
    
    for(  i = linha; i >=0; i--  ) {   // function que checa o valor máximo de 'L'
        for( ii = coluna; ii >=0; ii-- ) {
            if (MTX[ii][i] != 0) {
                L_lim = i;
                break;
            }
            if(L_lim!=0){break;}
        }
        if(L_lim!=0){break;}
    }    // final function que checa o valor máximo de 'L'
    
    for(  i = coluna; i >=0; i--  ) {   // function que checa o valor máximo de 'S'
        for( ii = linha; ii >=0; ii-- ) {
            if (MTX[i][ii] != 0) {
                S_lim = i;
                break;
            }
            if(S_lim!=0){break;}
        }
        if(S_lim!=0){break;}
    }    // final function que checa o valor máximo de 'S'
    
    printf("\n\n\n\t*** Anwser Matrix - all microstates computed ***\n\n");
    printf("MS:");
    
    // Numero par de eletrons = MS inteiro;
    // Numero impar de eletrons = MS fracionario
    
    
    for(i = S_lim; i>=0; i--){
        printf("\t%9.1f",i/2.0);
        i--;
    }
    
    printf("\n");
    
    for(  i = L_lim; i >=0; i--  ) {   // function Somatorio dos elementos da matriz resposta
        printf("\n");
        printf("ML:%2d\t", i);
        for( ii = S_lim; ii >=0; ii-- ) {
            printf("%9d\t", MTX[ii][i]);
            result = result + MTX[ii][i];
            ii--;
        }
    }
    
    printf("\n\nSum of all matrix elements: %g\n", result);
    printf("\n");
    
    return(result);
    
}

