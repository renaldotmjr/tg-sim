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

/*######################################################################*/
/*##                             genmicrost.h                         ##*/
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

/*################################################################################*/
/*# int F_GENMICRO( int ORB, int i, int no_e, int MTX_ms[ORB], int MTX_ml[ORB])  #*/
/*#                                                                              #*/
/*#    Function recursiva que calcula todos as possibilidades de arranjo         #*/
/*# de 'no_e' elementos em 'ORB'. O argumento 'i' deve sempre receber valor      #*/
/*#   '-1' antes de entrar na function, para que a matriz MTX_ms[ORB] seja       #*/
/*#                         preenchida do zero.                                  #*/
/*################################################################################*/
int F_GENMICRO(char _print_micro,  int ORB, int i, int no_e, int MTX_ms[ORB], int MTX_ml[ORB] ) {
    
    int ii = 0, iv;       // Contadores 'for'
    int Ms = 0, Ml = 0;        // Valores de 'ms' e 'ml' do microestado
    
    // Teste para eliminar a indefinicao causada por um numero nulo de 'eletrons'
    if (no_e > 0) {

        // Inicio do preenchimento e da obtencao dos microestados (me's)
        for( ii = i + 1; ii < ORB; ii++ ) {
            
            // Um 'eletron' ‡ MTX_ms, sendo este
            //usado como referencia para a variacao dos seguintes
            MTX_ms[ii] = 1;
            
            // Retira um 'eletron' cada vez que o 'for' e iniciado
            if (ii == i + 1) {
                no_e--;
            }
            // Chama a function F_GENMICRO() enquanto o numero de 'eletrons' for nao-nulo
            // e adicionando, unitariamente, 'eletrons' em MTX_ms
            if (no_e > 0)
            {
                F_GENMICRO(_print_micro, ORB, ii, no_e, MTX_ms, MTX_ml );
            }
            
            
            if (no_e == 0) {
                
                // Imprime na tela os me's encontrados
                // IF que testa se vai imprimir os microestados
                if( _print_micro == 49){	// Char(1) = ASCII(49)
                    for(iv = 0; iv < ORB; iv += 1) {
                        printf("%3d ", MTX_ms[iv]);
                    }
                } // fim dessa porra de IF
                
                
                // Calcula o Ml e o Ms do microestado
                Ms = F_MS( ORB, MTX_ms );
                Ml = F_ML( ORB, MTX_ms, MTX_ml );
                
                
                // IF que testa se vai imprimir os microestados
                if( _print_micro == 49){	// Char(1) = ASCII(49)
                    printf("     Ms = %3d;    Ml = %3d\n", Ms, Ml);
                } // fim dessa porra de IF
                
                
                // Adiciona os valores de Ms e Ml ‡s matrizes do orbital
                MTX_MS_3[i_global] = Ms;
                MTX_ML_3[i_global] = Ml;
                i_global++;
            }          // fim do 'if( no_e == 0 )'
            
            MTX_ms[ii] = 0;           // Limpa a posicao do ultimo 'eletron'
                                      // para nao atrapalhar na obtencao dos me's
        } // Fim do 'for' de preenchimento
    } // Fim do 'if' de teste da existÍncia de 'elÈtrons'
    
    return 0;

}



