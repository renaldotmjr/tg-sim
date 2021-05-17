//
//  confdouble.h
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
/*# int CONF_DOUBLE( char orbital_1, int no_e_1, char orbital_2, int no_e_2) #*/
/*#                                                                          #*/
/*#AlgorÌtimo de c·lculo para configurÁ„o de dois orbitais, onde 'orbital_1' #*/
/*# È o caractere representativo do primeiro orbital, 'orbital_2' È o para o #*/
/*# segundo orbital e 'no_e_1' e 'no_e_2' È o n˙mero de elÈtrons que popula  #*/
/*#                cada orbital da configuraÁ„o escolhida                    #*/
/*############################################################################*/

int CONF_DOUBLE(char _print_mtx, char _print_micro,  char orbital_1, int no_e_1, char orbital_2, int no_e_2) {
    
    int i = 0, ii = 0;      // Contadores 'for'
    int ORB = 20,           // Tamanho das matrizes de 'ms' e 'ml', modificado por entrada do usu·rio
    MTX0_ms[ORB],       // Matriz dos momentos de spin do microestado
    MTX0_ml[ORB],       // Matriz dos momentos magnÈticos do orbital
    Ms = 0,             // Momento de spin total da configuraÁ„o (vari·vel tempor·ria)
    Ml =0;              // Momento magnÈtico total da configuraÁ„o (vari·vel tempor·ria)
    
    double NmeT_T = 0.0;       // Numero de Microestados da configuraÁ„o completa
    double NmeT_1 = 0.0;       // Numero de Microestados da configuracao do primeiro orbital
    double NmeT_2 = 0.0;       // Numero de Microestados da configuracao do segundo orbital
    
    float SOMA;              // Vari·vel somatÛrio dos termos da matriz
    
    // Inicializa a matriz de ml com valor nulo
    for(i=0; i <= ORB; i++) {
        MTX0_ml [i] = 0;
    }
    
    //
    // Trabalhando o primeiro orbital
    //
    // Pega a entrada do usu·rio e seta o tamanho das matrizes de ms e ml, zerando esta ˙ltima
    switch (orbital_1) {
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
    // permitida 'ORB', os termos s„o computados
    if( no_e_1 <= ORB) {
        
        // C·lculo do n˙mero de microestados da configuraÁ„o
        NmeT_1 = F_NMET( ORB, no_e_1 );
        
        // Inicializando matrizes com o valor nulo
        
        // Matriz de spins
        for(i=0; i < ORB; i++) {
            MTX0_ms[i] = 0;
        }
        
        // Matrizes de ml e ms do orbitais mistos
        for(i=0; i < NmeT_MAX; i++) {
            MTX_MS_1[i] = 0;
            MTX_ML_1[i] = 0;
            MTX_MS_2[i] = 0;
            MTX_ML_2[i] = 0;
            MTX_MS_3[i] = 0;
            MTX_ML_3[i] = 0;
        }
        
        // Matriz de resultado
        for( i = 0; i <= MS; ++i ) {
            for( ii = 0; ii <= (ML + 1); ++ii ) {
                MTX_MS_ML[i][ii] = 0;
            }
        }
        
        // Impress„o do NmeT na tela
        printf("\n\nThe electronic configuration %c^%d has %.0lf microstates\n", orbital_1, no_e_1, NmeT_1);
        
        
        // IF que testa se vai imprimir os microestados
        if( _print_micro == 49){	// Char(1) = ASCII(49)
            
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
            // Imprime a Matriz Ml na tela
            for(i = 0; i < ORB; i++) {
                printf("%3d ", MTX0_ml[i]);
            }
            
            printf("\n\n");
        } // fim do IF que testa a impressao dos microestados
        
        
        i = -1;          // ArtifÌcio para F_LOOP() funcionar corretamente
        
        F_GENMICRO(_print_micro, ORB, i, no_e_1, MTX0_ms, MTX0_ml );
        
        
        copy_MTX(MTX_MS_1, MTX_MS_3);
        copy_MTX(MTX_ML_1, MTX_ML_3);
        
        i_global = 0;
        
        // Trabalhando o segundo orbital
        
        // Pega a entrada do usu·rio e seta o tamanho das matrizes de ms e ml, zerando esta ˙ltima
        switch (orbital_2) {
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
        
        // Testando o numero de elÈtrons
        if( no_e_2 <= ORB) {
            
            // C·lculo do n˙mero de microestados da configuraÁ„o
            NmeT_2 = F_NMET( ORB, no_e_2 );
            
            // Inicializando matrizes com o valor nulo
            
            // Matriz de spins
            for(i=0; i < ORB; i++) {
                MTX0_ms[i] = 0;
            }
            
            // Matrizes de ml e ms do orbitais mistos
            for(i=0; i < NmeT_MAX; i++) {
                MTX_MS_3[i] = 0;
                MTX_ML_3[i] = 0;
            }
            
            // Impress„o do NmeT na tela
            printf("\n\nThe electronic configuration %c^%d has %.0lf microstates\n", orbital_2, no_e_2, NmeT_2);
            
            
            // IF que testa se vai imprimir os microestados
            if( _print_micro == 49){	// Char(1) = ASCII(49)
                
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
                
                // Imprime a Matriz Ml na tela
                for(i=0; i < ORB; i++) {
                    printf("%3d ", MTX0_ml[i]);
                }
                
                printf("\n\n");
            } // fim do IF que testa a impressao dos microestados
            
            i=-1;          // ArtifÌcio para F_LOOP() funcionar corretamente
            
            F_GENMICRO(_print_micro, ORB, i, no_e_2, MTX0_ms, MTX0_ml );
            
            copy_MTX(MTX_MS_2, MTX_MS_3);
            copy_MTX(MTX_ML_2, MTX_ML_3);
            
            ///// ALTERA«√O DO ALGORITMO - UTILIZANDO POUCA MEMORIA PARA ORBITAIS MISTOS
            
            // Gera matriz MTX_MS_T e MTX_ML_T pela combinaÁ„o das MTX_MS_X e MTX_ML_X
            
            i_global = 0;
            
            for(i = 0; i < NmeT_1; i++) {
                for(ii = 0; ii < NmeT_2; ii++) {
                    Ms = MTX_MS_1[i] + MTX_MS_2[ii];
                    Ml = MTX_ML_1[i] + MTX_ML_2[ii];
                    
                    // Adiciona o microestado a matriz resultado
                    if ( Ms >= 0 && Ml >= 0 ) {
                        MTX_MS_ML[Ms][Ml] += 1;
                    }
                }
            }
            
            ////// FINAL DA ALTERA«√O DO ALGORITMO
            
            // Imprime o n˙mero de microestados totais da configuraÁ„o mista
            printf("\n\nThe electronic configuration %c%d%c%d has %0.1f microstates\n",
                   orbital_1, no_e_1, orbital_2, no_e_2, NmeT_1*NmeT_2);
            
            
            // Imprime as combinaÁıes de Ms e Ml possÌveis provinientes da matriz de resutado
            printf("\n-> Grouping microstates into the anwser matrix... (in terms of L and S) \n\n");
            
            // somatÛrio dos elementos da matriz
            SOMA = F_SOMAMTX(ML_1 , MS_1 , MTX_MS_ML);
            
            
            // Interpretando a matriz resposta
            F_INTERPRET(_print_mtx, ML_1, MS_1, MTX_MS_ML);
            
            printf("\n\n\t*** The obtension of all Spectroscopic Terms (Term Symbols) for configuration '%s' ended normally!***", CONF_TOTAL);
            
            
        } // fim do 'if' que testa o n˙mero de elÈtrons do segundo orbital
        
    }  // fim do 'if' que testa o n˙mero de elÈtrons do primeiro orbital
    
    else {
        printf("\nNumber of electrons for orbitals %c and %c: %d and %d.\nAre you sure?\nChoose a valid electronic configuration or go work with human sciences or biology...\n",
               orbital_1, orbital_2, no_e_1, no_e_2);
    } // fim do 'else' do 'if' que testa o n˙mero de elÈtrons
    
    return 0;
    
}
