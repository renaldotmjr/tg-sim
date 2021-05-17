/*######################################################################*/
/*##                           readtable.h                            ##*/
/*##                                                                  ##*/
/*##                             RTE.C                                ##*/
/*##                                                                  ##*/
/*######################################################################*/
/*##           PTE-SG v1.4 - Programa de Termos EspectroscÛpicos      ##*/
/*##                                                                  ##*/
/*##  Data da versao: 2015                                            ##*/
/*##                                                                  ##*/
/*##                                                                  ##*/
/*##                                                                  ##*/
/*##                                      RTE - SG - Janeiro de 2015  ##*/
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

/*#############################################################################*/
/*#                    void F_READ_TABLE(char _GP[5], char _REP[5])           #*/
/*#                                                                           #*/
/*#    Function que le, nos arquivos das tabelas de caracteres, determinada   #*/
/*#     representacao irredutivel, valores dos alfa ou fator da operacao      #*/
/*#############################################################################*/

void F_READ_TABLE(char _GP[5], char _REP[10]){
    
    
    char _linha[1000],          // String de linhas no arquivo
         _RepIrred_temp[10],     // String com conteudo da operacao em questao, TEMPORARIO
         _RepIrred[10],          // String com conteudo da Repretesentacao irredutivel
         _DIR[15]="Tabelas/";   // Diretorio das tabelas
    
    int _count_RI;              // Contador de RI que a tabela contÈm
    
    float _C[20],               // Matriz temporaria que pega os valores do arquivo
          _Classe = 0.0;        // Limite de operacoes que a tabela de caracteres tem
    
    
    FILE *_file_char;           //*********
    
    // Passado o conteudo da string _GP para _DIR
    strncat(_DIR,_GP,3);
    
    //Abrindo o arquivo de entrada de dados
    _file_char=fopen(_DIR,"r");
    
    if(!_file_char){
        printf("\n** Failed to open '%s' character table file, please check the chosen point group.\n\n",_GP);
        exit (0);
    }
    
    // Para certificar que o contador ira zerar toda vez que for chamado
    _count_RI = 0;
    
    // Varrendo o arquivo _GP aberto
    while (fgets(_linha, 1000, _file_char)) {
        

        
        // Procurando por representacoes IRREDUTIVEIS no arquivo do GP
        sscanf(_linha,"%s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", _RepIrred_temp ,
               &_C[0] ,&_C[1] ,&_C[2] ,&_C[3], &_C[4], &_C[5], &_C[6], &_C[7] ,&_C[8] ,&_C[9] ,
               &_C[10], &_C[11], &_C[12], &_C[13], &_C[14], &_C[15] );
        
        // Procurando os NOMES das RI, e atrelando a uma matriz STRING das RI => _MTX_RI[]
        if ( (strcmp(_RepIrred_temp,"Classe"))==0 || (strcmp(_RepIrred_temp,"nelet"))==0 || (strcmp(_RepIrred_temp,"elem"))==0 || (strcmp(_RepIrred_temp,"Teta"))==0 || (strcmp(_RepIrred_temp,"#"))==0){
        }
        
        else {
            _count_RI++;                 // contando a quantidade de RI que o GP contÈm.
            strcpy(_MTX_RI[_count_RI], _RepIrred_temp);
        }
        
        // Procurando o valor da CLASSE no GP e atrelando a _MTX_ELEM[0][0]
        if ((strcmp(_RepIrred_temp,"Classe"))==0){
            _Classe = _C[0];
            _MTX_ELEM[0][0] = _Classe;
            
        }
        
        // Procurando os NOMES dos ELEMENTOS DE SIMETRIA, e atrelando a uma matriz STRING => _MTX_ELEM[x], para x = 1, 2, 3, ..., 15
        if ((strcmp(_RepIrred_temp,"elem"))==0){
            sscanf(_linha,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", _RepIrred_temp,
                   _MTX_ELEM[1], _MTX_ELEM[2], _MTX_ELEM[3], _MTX_ELEM[4], _MTX_ELEM[5],
                   _MTX_ELEM[6], _MTX_ELEM[7] ,_MTX_ELEM[8] ,_MTX_ELEM[9] ,_MTX_ELEM[10],
                   _MTX_ELEM[11], _MTX_ELEM[12], _MTX_ELEM[13], _MTX_ELEM[14], _MTX_ELEM[15] );
            _MTX_ELEM[0][0] = _Classe;
        }
        
        // Atrelando os VALORES das OPERACOES DE SIMETRIA para cada RI
        if ( (strcmp(_RepIrred_temp, _REP)) == 0 ){
            strcpy(_RepIrred, _RepIrred_temp);
            _MTX_CHAR[0] = _Classe;
            _MTX_CHAR[1] = _C[0];
            _MTX_CHAR[2] = _C[1];
            _MTX_CHAR[3] = _C[2];
            _MTX_CHAR[4] = _C[3];
            _MTX_CHAR[5] = _C[4];
            _MTX_CHAR[6] = _C[5];
            _MTX_CHAR[7] = _C[6];
            _MTX_CHAR[8] = _C[7];
            _MTX_CHAR[9] = _C[8];
            _MTX_CHAR[10] = _C[9];
            _MTX_CHAR[11] = _C[10];
            _MTX_CHAR[12] = _C[11];
            _MTX_CHAR[13] = _C[12];
            _MTX_CHAR[14] = _C[13];
            _MTX_CHAR[15] = _C[14];
            _MTX_CHAR[16] = _C[15];
        }

        // OBS.1: a primeira casa das matrizes (_MTX_ELEM; _MTX_CHAR) CONTEM O VALOR DA CLASSE DO GP
        // OBS.2: a primeira casa da matriz _MTX_RI CONTEM O VALOR DE RI DO GP
        
    }
    
    fclose (_file_char);            // Final da leitura de arquivo
    _MTX_RI[0][0] = _count_RI;       // Passando o numero de RI que o GP contem
}

// fim da function void F_READ_TABLE