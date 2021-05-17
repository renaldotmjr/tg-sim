/*######################################################################*/
/*##                            interpret.h                           ##*/
/*##                                                                  ##*/
/*######################################################################*/
/*##           PTE-SG v1.5 - Programa de Termos Espectroscopicos      ##*/
/*##                                                                  ##*/
/*##  Data da versao: Marco de 2015                                   ##*/
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

/*################################################################################
#     void F_INTERPRET(int linha, int coluna, int MTX[coluna][linha+1])          #
#                                                                                #
#   Function que calcula o somatório dos elementos de uma matriz dada            #
#   O nº de linhas e colunas a serem somados são os argumentos 'linha'           #
#            e 'coluna'.  A Function retorna 'result'.                           #
##################################################################################*/

void F_INTERPRET(char _print, int linha, int coluna, int MTX[coluna][linha+1]){

     int i=0, ii=0, iii=0, iv=0;        // Contadores 'for'
     int cont_vect=0;                   // contador da casa da matriz que guarda os termos
     int n_TE=0;
     int BACK_hund[coluna+5][linha+5];  // Backup da matriz resposta

     long int  VECT_TERMOS[3][150000];

     float cont_i;                      // contador float para termos semi-inteiros
     float J_max = 0,                   // valor máximo do 'J' para o acoplamento spin-órbita
           J_min = 0;                   // valor mínimo do 'J' para o acoplamento spin-órbita

     // Matriz Representando os termos
     char MULT_TERMOS[80][4] = {{"S"},  {"P"},  {"D"},  {"F"},  {"G"},  {"H"},  {"I"},  {"K"},  {"L"},  {"M"},
                                {"N"},  {"O"},  {"Q"},  {"R"},  {"T"},  {"U"},  {"V"},  {"W"},  {"X"},  {"Y"},
                                {"Z"},  {"A"},  {"B"},  {"C"},  {"E"},
                                {"SS"}, {"PP"}, {"DD"}, {"FF"}, {"GG"}, {"HH"}, {"II"}, {"KK"}, {"LL"}, {"MM"},
                                {"NN"}, {"OO"}, {"QQ"}, {"RR"}, {"TT"}, {"UU"}, {"VV"}, {"WW"}, {"XX"}, {"YY"},
                                {"ZZ"}, {"AA"}, {"BB"}, {"CC"}, {"EE"},
                                {"SSS"},{"PPP"},{"DDD"},{"FFF"},{"GGG"},{"HHH"},{"III"},{"KKK"},{"LLL"},{"MMM"},
                                {"NNN"},{"OOO"},{"QQQ"},{"RRR"},{"TTT"},{"UUU"},{"VVV"},{"WWW"},{"XXX"},{"YYY"},
                                {"ZZZ"},{"AAA"},{"BBB"},{"CCC"},{"EEE"}};

     // vetor que guarda os termos espectroscópicos.
     //--- primeira linha= 2S+1 ---- segunda linha= L

     		   // Inicializando o valor de TE inicial igual a zero
     		   VECT_TERMOS[0][0] = 0;

     // copiando MTX para MTX_hund
     for(  i = linha ; i >=0; i--  ) {
             for( ii = coluna + 1; ii >=0; ii-- ) {
			      BACK_hund[ii][i] = 0;
			      BACK_hund[ii][i] = MTX[ii][i];
			      }
             } //fim da cópia de MTX para MTX_hund

// if que testa se o programa vai imprimir as matrizes
if( _print == 49){	// Char(1) = ASCII(49)


     // Calcula e Imprime os Termos Espectroscopicos
     printf("\n\n-> Interpreting the Anwser Matrix to compute the Spectroscopic Terms (Terms Symbols)\n\n");
     printf("   *** Printing the Spectroscopic Terms of the electronic configuration ***\n\n\n");

     // Iterpretando a Matriz Resposta e Obtendo os Termos Espectroscopicos
     for( i = linha; i >=0; i-- ) {
             for( ii = coluna; ii >=0; ii-- ) {
                  while ( MTX[ii][i] != 0 ){
                         printf("\n-> Spectroscopic Term found:");
                         // 'L' é o termo -valor de i-
                         // 'S' é a soma dos spins -valor de ii/2-
                         // '2S+1' é a multiplicidade -valor de ii +1-
                         printf("\nL=%d, S=%g --- %d%s  (M.E.= %.0lf)",i, ii/2.0 ,(ii + 1) ,MULT_TERMOS[i], F_NME( ii, i));

                         // loop para decrementar cada elemento de MTX_MS_ML que tenha Ml e Ms menores que o valor corrente
                         for ( iii = i ; iii >=0; iii--) {
                             for( iv = ii ; iv >=0; iv--) {
                                  if ( MTX[iv][iii] > 0 ) {  // impondo o elemento maior que zero
                                       MTX[iv][iii]--;
                                       }
                                  }
                             } // fim do for de decremento

                         printf("\n\n-> Eliminating the %d%s microstates from Anwser Matrix.",(ii + 1), MULT_TERMOS[i]);
                         // Imprimindo a matriz resposta e somando os elementos
                         F_SOMAMTX(linha ,coluna , MTX);
                         }

             }
     }// fim do 'for' que escreve os termos

} // final do if que testa impressao das matrizes

else {

	}

// ******** Dispondo os termos pela regra de hund **********
     for( ii = coluna; ii >=0; ii-- ) {
          for( i = linha; i >=0; i-- ) {
                while ( BACK_hund[ii][i] != 0 ) {
                      // 'L' é o termo -valor de i-
                      // 'S' é a soma dos spins -valor de ii/2-
                      // '2S+1' é a multiplicidade -valor de ii +1-

					  // Registrando o TE
					  VECT_TERMOS[1][cont_vect] = ii + 1;
					  VECT_TERMOS[2][cont_vect] = i;

					  VECT_TERMOS[0][cont_vect + 1] = 0;
					  // ----------------

					  // Incrementando o numero de TE iguais
					  if ( VECT_TERMOS[0][cont_vect] == 0 ){


					  		VECT_TERMOS[0][cont_vect]++;
					  		// ---
							}

					  else {

					  		VECT_TERMOS[0][cont_vect] = 1;

					  		}
					  // -----------------------------------

                      // loop para decrementar cada elemento de MTX_MS_ML que tenha Ml e Ms menores que o valor corrente
                      for ( iii = i ; iii >=0; iii--) {
                            for( iv = ii ; iv >=0; iv--) {
                                if ( BACK_hund[iv][iii] > 0 ) { // impondo o elemento maior que zero
                                      BACK_hund[iv][iii]--;
                                      }
                                }
                            } // fim do 'for' de decremento

					  // Concatena os TE pelo tipo
					  if( (cont_vect != 0) && (VECT_TERMOS[1][cont_vect] == VECT_TERMOS[1][cont_vect - 1]) && (VECT_TERMOS[2][cont_vect] == VECT_TERMOS[2][cont_vect - 1]) ) {

						  // decrementando a contagem do vetor
						  cont_vect--;

						  // incrementando o numero de TE iguais
						  VECT_TERMOS[0][cont_vect]++;

					  	  } // fim do rearanjo da matriz VECT_TERMOS

					  cont_vect++;

					  // contando o numero de TE
					  n_TE++;

                      }
          }
     }// fim do 'for' da regra de hund

// ******** fim da regra de hund *****************

     // Imprimindo resumo de todos os termos espectroscopicos calculados dispostos pela regra de hund
     printf("\n\t**** ALL SPECTROCOPIC TERMS FOUND *****");
     printf("\n\tOrdered according Hund's rule");
     printf("\n\tTotal amount of Terms: %d\n\n", n_TE);

     for (i=0; i<cont_vect; i++) {
         printf("!-> %3ld%s     (M.E.= %5.0lf   |   N terms:  %-8ld)\n", VECT_TERMOS[1][i], MULT_TERMOS[VECT_TERMOS[2][i]], F_NME((VECT_TERMOS[1][i] - 1), VECT_TERMOS[2][i]), VECT_TERMOS[0][i]);
     } // fim da Impressao do resumo de todos os termos

     // calculando desdobramento devido ao acoplamento spin-orbita
     printf("\n\t*** SPIN ORBIT COUPLING ***\n\n");

     for (i=0; i<cont_vect; i++) {
         printf("-> H(E-E): %ld%s (M.E.= %.0lf)\n", VECT_TERMOS[1][i], MULT_TERMOS[VECT_TERMOS[2][i]], F_NME((VECT_TERMOS[1][i] - 1), VECT_TERMOS[2][i]));
 		 // calculo dos 'J' de acoplamento spin-orbita.
		 J_max = VECT_TERMOS[2][i]*1.0 + (VECT_TERMOS[1][i] - 1)/2.0;
		 J_min = fabs(VECT_TERMOS[2][i]*1.0 - (VECT_TERMOS[1][i] - 1)/2.0);

		 printf("-> H(S-O):");

		 for (cont_i = J_max; cont_i >=J_min ; cont_i--) {
             printf(" %ld%s%g ", VECT_TERMOS[1][i], MULT_TERMOS[VECT_TERMOS[2][i]], cont_i);
			 }
 		 printf("\n\n");

      } // fim do 'for' do desdobramento spin-orbita


}
