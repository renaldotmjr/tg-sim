/*######################################################################*/
/*##                             globals.h                            ##*/
/*##                                                                  ##*/
/*##                             PTE.C                                ##*/
/*##                                                                  ##*/
/*######################################################################*/
/*##           PTE-SG v1.4 - Programa de Termos EspectroscÛpicos      ##*/
/*##                                                                  ##*/
/*##  Data da versao: 2015                                            ##*/
/*##                                                                  ##*/
/*##                                                                  ##*/
/*##                                                                  ##*/
/*##                                      PTE - SG - Janeiro de 2015  ##*/
/*######################################################################*/
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

/*#####################################################################*/
/*#           InÌcio de diretivas de pre-processamento                #*/
/*#####################################################################*/

#define ML 64            // Valor m·ximo de Ml mais uma unidade
#define MS 20            // Valor m·ximo de Ms mais uma unidade
#define ML_1 ML - 1      // ArtifÌcio para F_INTERPRET funcionar bem
#define MS_1 MS - 1
#define NmeT_MAX 49000    // N˙mero m·ximo de microestados de uma configuraÁ„o simples

/*#####################################################################*/
/*#             Fim de diretivas de pre-processamento                 #*/
/*#####################################################################*/

int i_global = 0;              // Contador Global

int MTX_MS_ML[MS][ML];         // Matriz de Resultado, vari·vel global
int MTX_MS_1[NmeT_MAX];        // Matriz de 'ms' do orbital '1', para configuraÁ„o mista/tripla
int MTX_ML_1[NmeT_MAX];        // Matriz de 'ml' do orbital '1', para configuraÁ„o mista/tripla
int MTX_MS_2[NmeT_MAX];        // Matriz de 'ms' do orbital '2', para configuraÁ„o mista/tripla
int MTX_ML_2[NmeT_MAX];        // Matriz de 'ml' do orbital '2', para configuraÁ„o mista/tripla
int MTX_MS_3[NmeT_MAX];        // Matriz de 'ms' do orbital '3', para configuraÁ„o mista/tripla (matrix resposta de F_LOOP)
int MTX_ML_3[NmeT_MAX];        // Matriz de 'ml' do orbital '3', para configuraÁ„o mista/tripla (matrix resposta de F_LOOP)

char CONF_TOTAL[10] = "";      // Configuracao eletronica
char _MTX_RI[15][5];           // TgSIM_ Matriz que guarda os NOMES das representaÁıes irredutÌveis
char _MTX_ELEM[16][10];        // TgSim_ Matriz que

float _MTX_CHAR[20];           // Matriz final com os valores da Representacao irredutivel

