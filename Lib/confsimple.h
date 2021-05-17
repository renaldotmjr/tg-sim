//
//  confsimple.h
//  TgSim_1.5
//
//  Created by Renaldo Tenorio de Moura Junior on 4/14/15.
//  Copyright (c) 2015 Renaldo Tenorio de Moura Junior. All rights reserved.
//

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

/*############################################################################*/
/*#             int CONF_SIMPLE( char orbital, int no_e)                     #*/
/*#                                                                          #*/
/*#AlgorÌtimo de c·lculo para configuraÁ„o de um orbital. Onde 'orbital' È o #*/
/*# caractere representativo do orbital e 'no_e' È o n˙mero de elÈtrons que  #*/
/*#           popula cada orbital da configuraÁ„o escolhida                  #*/
/*############################################################################*/

int CONF_SIMPLE(char _print_mtx, char _print_micro, char orbital, int no_e) {
    
    
    int i = 0, ii = 0;      // Contadores 'for'
    int ORB = 20,      // Tamanho das matrizes de 'ms' e 'ml', modificado por entrada do usu·rio
    MTX0_ms[ORB],  // Matriz dos momentos de spin do microestado
    MTX0_ml[ORB],  // Matriz dos momentos magnÈticos do orbital
    Ms = 0,        // Valores de 'ms' e 'ml' do microestado
    Ml = 0;
    
    double NmeT = 0.0;       // N˙mero de Microestados da configuraÁ„o
    
    float SOMA;              // Vari·vel somatÛrio dos termos da matriz
    
    // Pega a entrada do usu·rio e seta o tamanho das matrizes de 'ms' e 'ml', zerando esta ˙ltima
    switch (orbital) {
        case 's':
            ORB = 2;
            MTX0_ml[0] = 0; MTX0_ml[1] = 0;
            break;
            
        case 'p':
            ORB = 6;
            MTX0_ml[0] =  1;  MTX0_ml[1] =  0;
            MTX0_ml[2] = -1;  MTX0_ml[3] =  1;
            MTX0_ml[4] =  0;  MTX0_ml[5] = -1;
            break;
            
        case 'd':
            ORB = 10;
            MTX0_ml[0] =  2; MTX0_ml[1] =  1;
            MTX0_ml[2] =  0; MTX0_ml[3] = -1;
            MTX0_ml[4] = -2; MTX0_ml[5] =  2;
            MTX0_ml[6] =  1; MTX0_ml[7] =  0;
            MTX0_ml[8] = -1; MTX0_ml[9] = -2;
            break;
            
        case 'f':
            ORB = 14;
            MTX0_ml[0]  =  3; MTX0_ml[1]  =  2;
            MTX0_ml[2]  =  1; MTX0_ml[3]  =  0;
            MTX0_ml[4]  = -1; MTX0_ml[5]  = -2;
            MTX0_ml[6]  = -3; MTX0_ml[7]  =  3;
            MTX0_ml[8]  =  2; MTX0_ml[9]  =  1;
            MTX0_ml[10] =  0; MTX0_ml[11] = -1;
            MTX0_ml[12] = -2; MTX0_ml[13] = -3;
            break;
            
        case 'g':
            ORB = 18;
            MTX0_ml[0]  =  4; MTX0_ml[1]  =  3;
            MTX0_ml[2]  =  2; MTX0_ml[3]  =  1;
            MTX0_ml[4]  =  0; MTX0_ml[5]  = -1;
            MTX0_ml[6]  = -2; MTX0_ml[7]  = -3;
            MTX0_ml[8]  = -4; MTX0_ml[9]  =  4;
            MTX0_ml[10] =  3; MTX0_ml[11] =  2;
            MTX0_ml[12] =  1; MTX0_ml[13] =  0;
            MTX0_ml[14] = -1; MTX0_ml[15] = -2;
            MTX0_ml[16] = -3; MTX0_ml[17] = -4;
            break;
    }
    
    // Testando o n˙mero de elÈtrons, caso seja menor que a quantidade m·xima
    // permitida 'ORB', os termos sao computados
    if( no_e <= ORB) {
        
        // Inicializa a matriz de spins com valor nulo
        for(i=0; i < ORB; i++) {
            MTX0_ms[i] = 0;
        }
        
        // Inicializa a matriz de resultado com valor nulo
        for( i = 0; i <= MS; ++i ) {
            for( ii = 0; ii <= (ML + 1); ++ii ) {
                MTX_MS_ML[i][ii] = 0;
            }
        }
        
        // C·lculo do n˙mero de microestados da configuraÁ„o
        NmeT = F_NMET( ORB, no_e );
        
        // Impress„o do NmeT na tela
        //        printf("Numero de microestados para a configuracao %c^%d: %.0lf\n\n", orbital, no_e, NmeT);
        printf("Number of microstates for configuration %c^%d: %.0lf\n\n", orbital, no_e, NmeT);
        
        // IF que testa se vai imprimir os microestados
        if( _print_micro == 49){	// Char(1) = ASCII(49)
            // Imprime a Matriz Ml na tela
            
            
            
            if(ORB == 2) {
                
                printf("\n  *** Spin Factoring Like microstates ***  \n");
                printf(" ml+ ml- \n");
                printf("[___|___]\n");
                printf("----------\n");
                
            }
            
            
            if(ORB == 6) {
                
                printf("\n  *** Spin Factoring Like microstates ***  \n");
                printf("ml(Spin UP) ml(Spin Down)\n");
                printf("[___ ___ ___|___ ___ ___]\n");
                printf("--------------------------\n");
                
            }
            
            
            if(ORB == 10) {
                
                printf("\n  *** Spin Factoring Like microstates ***  \n");
                printf("     ml (Spin UP)       ml (Spin Down)   \n");
                printf("[___ ___ ___ ___ ___|___ ___ ___ ___ ___]\n");
                printf("-------------------------------------------\n");

            }
            
            if(ORB == 14) {
                
                printf("\n  *** Spin Factoring Like microstates ***  \n");
                printf("        ml (Spin UP)                ml (Spin Down)\n");
                printf("[___ ___ ___ ___ ___ ___ ___|___ ___ ___ ___ ___ ___ ___]\n");
                printf("----------------------------------------------------------\n");
                
            }
            
            
            if(ORB == 18) {
                
                printf("\n  *** Spin Factoring Like microstates ***  \n");
                printf("            ml (Spin UP)                        ml (Spin Down)  \n");
                printf("[___ ___ ___ ___ ___ ___ ___ ___ ___|___ ___ ___ ___ ___ ___ ___ ___ ___]\n");
                printf("--------------------------------------------------------------------------\n");
                
            }

            
            for(i = 0; i < ORB; i++) {
                printf("%3d ", MTX0_ml[i]);
            }
            
            printf("\n\n");
        } // fim do IF que testa a impressao dos microestados
        
        
        i = -1;          // ArtifÌcio para F_LOOP() funcionar corretamente
        
        F_GENMICRO(_print_micro, ORB, i, no_e, MTX0_ms, MTX0_ml );
        
        
        // Adiciona o microestado a matriz resultado
        for(i = 0; i < NmeT; i++) {
            Ms = MTX_MS_3[i];
            Ml = MTX_ML_3[i];
            
            if ( Ms >= 0 && Ml >= 0 ) {
                MTX_MS_ML[Ms][Ml] += 1;
            }
        }
        
        // Imprime as combinaÁıes de Ms e Ml possÌveis provinientes da matriz de resutado
        printf("\n-> Grouping microstates into the answer matrix... (in terms of L and S) \n\n");
        
        // somatorio dos elementos da matriz resultado
        SOMA = F_SOMAMTX(ML_1 , MS_1 , MTX_MS_ML);
        
        // Interpretando a matriz resultado
        F_INTERPRET(_print_mtx, ML_1, MS_1, MTX_MS_ML);
        
        printf("\n\n\t*** The obtension of all Spectroscopic Terms (Term Symbols) for configuration '%s' ended normally!***", CONF_TOTAL);
        
        
    }  // fim do 'if' que testa o n˙mero de elÈtrons
    
    else {
        printf("Number of electrons not permitted for orbital '%c': %d !\n", orbital, no_e);
        printf("The maximum number of electrons supported for this orbital is %d.",ORB);
    } // fim do 'else' do 'if' que testa o n˙mero de elÈtrons
    
    return 0;
}
