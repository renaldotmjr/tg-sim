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

/*#############################################################################*/
/*#                     int F_PARITY( char orbital, int no_e)                 #*/
/*#                                                                           #*/
/*#  Function que retorna a paridade da configuração, definida por 'orbital'  #*/
/*#                                e 'no_e'.                                  #*/
/*#############################################################################*/

// Modo formal de definir a paridade:
//                                      P = (-1)^{sum_i(l_i)}
// Onde l_i é o número quântico orbital do elétron i.
// Corolario 1 - Orbitais completamente preenchidos fornecem 'P = 1', logo basta analisar a configuracao da valencia.
// Corolario 2 - Se n. de eletrons for par, logo 'P = 1'. Se n. eletrons for ímpar:
//                                                                                 'P = 1' caso 'l' for par;
//                                                                                 'P = -1' caso 'l' for ímpar.

int F_PARITY( char orbital, int no_e) {
    
    int ORB = 0,            // Valor de 'l' para os orbitais 's', 'p', 'd', 'f' e 'g'
        parity = 0;         // Valor da paridade, 'parity = 1' -> paridade PAR, 'parity = -1' -> paridade IMPAR


    switch (orbital) {
           case 's':  ORB = 0;  break;
           case 'p':  ORB = 1;  break;
           case 'd':  ORB = 2;  break;
           case 'f':  ORB = 3;  break;
           case 'g':  ORB = 4;  break;
           default:
              printf("\n\nF_PARITY(): Orbital not permitted: %c\n\n",orbital);
              exit(0);
    }

    // Definicao da paridade da configuracao
    if (ORB % 2 && no_e %2) {     // ORB = impar e no_e = impar
        parity = -1;
    }
    
    else {             // ORB = par e/ou  no_e = par
        parity = 1;
    }

    return(parity);
}


/*#############################################################################*/
/*#                    float F_BETHE( int _L, int _TETA)                      #*/
/*#                                                                           #*/
/*#    Function que calcula o traço da matrix correspondente a um elemento    #*/
/*#         de simetrica que atua com uma rotação _TETA em um termo _L.       #*/
/*#############################################################################*/

float F_BETHE(int _L, int _TETA) {

    float _TRACO = 0.0; // Inicializa o Traço da representação como nulo

    _TRACO = ((sin((_L + 0.5)*(_TETA*(3.1415/180.0))))/(sin((_TETA*(3.1415/180.0))/2.0))); // Equacao de Bethe
    
    _TRACO = ceilf(100*_TRACO)/100;
    
    return(_TRACO);
}


/*#############################################################################*/
/*#  float F_GTO( int _H, int _NCLASSE, float _REP_RED[], float _REP_IRRED)   #*/
/*#                                                                           #*/
/*#    Function que calcula o quanto uma representacao irredutivel compoe     #*/
/*#  a representacao redutivel, baseado no "Grande teorema da Ortogonalidade" #*/
/*#############################################################################*/

float F_GTO(float _H, float _NCLASSE, float _REP_RED, float _REP_IRRED) {

    float _N = 0;

    _N = (1/_H)*(_REP_RED)*(_REP_IRRED)*(_NCLASSE);

    _N = ceilf(100*_N)/100;
    
    return (_N);
}

/*#######################################################################
# int F_SOMAMTX(int linha, int coluna, int MTX[coluna][lilnha+1])       #
#                                                                       #
#  Function que calcula o somatório dos elementos de uma matriz dada    #
#  O nº de linhas e colunas a serem somados sao os argumentos 'linha'   #
#             e 'coluna'.  A Function retorna 'result'.                 #
#########################################################################*/

float F_SOMAMTX(int _coluna, float _MTX[_coluna]) {

	int i;
	float _result = 0.0;


	for( i = 1; i <= _coluna; i++) {

		_result = _result + _MTX[i];
	}

      return(_result);

}