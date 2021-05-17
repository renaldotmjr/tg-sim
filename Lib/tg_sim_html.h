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
/*#      void F_FILE_HTML(char _TERMO[3], char _GP[3], int _J, int _L)        #*/
/*#                                                                           #*/
/*#    Function que gera o output .html                                       #*/
/*#                                                                           #*/
/*#############################################################################*/

char _NAMEE[20] = "Tg-Sim Software";
char _VERSAO[20] = "Tg-Sim v.1.0";
char _DOCUMENTACAO[50] = "../Documentacao/Manual_Tg-SimV1.0.pdf";


void F_FILE_HTML(char _TERMO[3], char _GP[3], char _CONF[3], int _J, int _L, char _MTX_ELEM[15][10], float _MTX_REP_RED[15], float _size, float _MTX_COEF_RI[15], char _MTX_RI[15][5], int paridade){

    FILE *arquivo;             // Declaração do ponteito *arquivo
    int i;                     // Variavel contador
    char _FILENAME[20] = "Tg-Sim-",
         _TE_paridade[10];         // Paridade do _TERMO

     // Criando nome do arquivo de output
    strncat(_FILENAME, _TERMO, 7);
    strncat(_FILENAME, "_",1);
    strncat(_FILENAME, _GP,3);
    strncat(_FILENAME, "_",1);
    strncat(_FILENAME, _CONF,3);
    strncat(_FILENAME, ".htm",5);


    if (paridade == 1)
      strcpy(_TE_paridade,"even");
    else
      strcpy(_TE_paridade,"odd");


    printf("\n\nWriting \'%s\' result file...", _FILENAME);

    arquivo=fopen(_FILENAME,"w");

    if(!arquivo){
        printf("Failed to create %s file",_FILENAME);
    }

    // Começo da criação do arquivo HTML.

        // Título do arquivo HTML
        fprintf(arquivo,"<html>\n");
        fprintf(arquivo,"\n");
        fprintf(arquivo,"<head>\n");
        fprintf(arquivo,"<title>%s -> File created by %s</title>\n", _FILENAME, _VERSAO);
        fprintf(arquivo,"</head>\n");
        // Fim do título do arquivo HTML

        //Tabela de Apresentação do HTML Output
        fprintf(arquivo,"<body>\n");
        fprintf(arquivo,"\n");
        fprintf(arquivo,"<div align=\"center\">\n");
        fprintf(arquivo,"\n");
        fprintf(arquivo,"<table border=\"0\" width=\"400\" id=\"table1\">\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td align=\"center\">\n");
        fprintf(arquivo,"		<p><b><font size=\"7\" face=\"Century Gothic\">%s\n", _NAMEE);
        fprintf(arquivo,"</font></b></td>\n");
        fprintf(arquivo,"	</tr>\n");
    
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td align=\"center\">\n");
        fprintf(arquivo,"		<p><b><font size=\"3\" face=\"Century Gothic\">A Computational Tool for Electronic Spectroscopy \n");
        fprintf(arquivo,"</font></b></td>\n");
        fprintf(arquivo,"	</tr>\n");
    
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td align=\"center\">\n");
        fprintf(arquivo,"		<p align=\"right\"><font size=\"2.5\" face=\"Century Gothic\">Moura Jr, R. T.; Aguiar, E. C.; da Silva, J. C. \n");
        fprintf(arquivo,"		</font></td>\n");
        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td align=\"center\">\n");
        fprintf(arquivo,"		<p align=\"right\"><b><i>\n");
        fprintf(arquivo,"		<span style=\"font-size: 9pt; font-family: Century Gothic\">\n");
        fprintf(arquivo,"		<a href=\"http://dqfnet.ufpe.br/lqtc/tgsim\">http://dqfnet.ufpe.br/lqtc/tgsim/</span></i></b></td>\n");
        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td align=\"center\">\n");
        fprintf(arquivo,"		<p align=\"right\"><span style=\"font-size: 9pt\" lang=\"en-us\"><b><i>\n");
        //fprintf(arquivo,"		<span style=\"font-family: Century Gothic\">*For instructions, read the <a href=\"%s\">Tg-Sim manual</a></span></i></b></span></td>\n", _DOCUMENTACAO);
        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"\n");
        fprintf(arquivo,"</table>\n");
        fprintf(arquivo,"\n");
        // Final da tabela de Apresentação do HTML Output

        fprintf(arquivo,"\n");
        fprintf(arquivo,"<p>&nbsp;</p>\n");

        // Tabela com resumo do TE e do GP
        fprintf(arquivo,"<table border=\"1\" width=\"300\" id=\"table2\">\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td width=\"172\" align=\"center\" colspan=\"2\"><font face=\"Comic Sans MS\">Spectroscopic Term</font></td>\n");
        fprintf(arquivo,"		<td align=\"center\"><font face=\"Comic Sans MS\">Point Group</font></td>\n");
        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td width=\"172\" align=\"center\" colspan=\"2\"><font face=\"Comic Sans MS\"><font color=\"#000080\">%s</font></font></td>\n", _TERMO);
        fprintf(arquivo,"		<td align=\"center\"><font face=\"Comic Sans MS\"><font color=\"#000080\">%s</font></font></td>\n", _GP);
        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td width=\"83\" align=\"center\"><font face=\"Comic Sans MS\">L =\n");
        fprintf(arquivo,"		<font color=\"#000080\">%d</font></font></td>\n", _L);
        fprintf(arquivo,"		<td width=\"83\" align=\"center\"><font face=\"Comic Sans MS\">(2S+1) =\n");
        fprintf(arquivo,"		<font color=\"#000080\">%d</font></font></td>\n", _J);
        fprintf(arquivo,"		<td align=\"center\"></td>\n");
        fprintf(arquivo,"	</tr>\n");

        fprintf(arquivo,"</table>\n");
        // Fim da tabela com resumo do TE e do GP

        // Tabela com a paridade do TE
        fprintf(arquivo,"<p>&nbsp;<table border=\"1\" width=\"300\" id=\"table3\">\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td colspan=\"2\" align=\"center\">\n");
        fprintf(arquivo,"		<p><font face=\"Comic Sans MS\">\n");
        fprintf(arquivo,"Setting term parity <font color=\"#000080\">%s</font></font></td>\n", _TERMO);
        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td align=\"center\"><font face=\"Comic Sans MS\">\n");
        fprintf(arquivo,"		Electronic Configuration: <font color=\"#000080\">%s</font></font></td>\n", _CONF);
        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td colspan=\"2\" align=\"center\"><font face=\"Comic Sans MS\">\n");
        fprintf(arquivo,"The term <font color=\"#000080\">%s</font> has <font color=\"#000080\">%s</font> parity </font></td>\n", _TERMO, _TE_paridade);
        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"\n");
        fprintf(arquivo,"</table>\n");
        // Fim da tabela com a paridade do TE

        fprintf(arquivo,"<p>&nbsp;</div>\n");
        fprintf(arquivo,"<div align=\"center\">\n");

        // Criação de tabela com resultados do Tg-Sim
        fprintf(arquivo,"<table border=\"0\" id=\"table4\">\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td align=\"center\">\n");
        fprintf(arquivo,"		<p><font face=\"Comic Sans MS\">Reducible Representation \n");
        fprintf(arquivo,"		of the <font color=\"#000080\">%s</font> spectroscopic term:\n", _TERMO);
        fprintf(arquivo,"		</font></td>\n");
        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td align=\"center\">\n");
        fprintf(arquivo,"		<table border=\"1\" id=\"table5\">\n");
        fprintf(arquivo,"			<tr>\n");
        fprintf(arquivo,"				<td align=\"center\"><font face=\"Comic Sans MS\" color=\"#000080\">&nbsp; %s &nbsp;</font></td>\n", _GP);

	for(i=1; i<=_size; i++) {
        fprintf(arquivo,"				<td align=\"center\"><font face=\"Comic Sans MS\">&nbsp; %s &nbsp;</font></td>\n", _MTX_ELEM[i]);
    }

        fprintf(arquivo,"\n");
        fprintf(arquivo,"			</tr>\n");
        fprintf(arquivo,"			<tr>\n");
        fprintf(arquivo,"				<td align=\"center\"><font face=\"Symbol\">&#915<font size=\"1\" color=\"#000080\"><font face=\"Comic Sans MS\"> %s </font></font></td>\n", _TERMO);

    for(i=1; i<=_size; i++) {
        fprintf(arquivo,"				<td align=\"center\"><font face=\"Comic Sans MS\">&nbsp; %.0f &nbsp;</font></td>\n", _MTX_REP_RED[i]);
    }

        fprintf(arquivo,"\n");
        fprintf(arquivo,"			</tr>\n");
        fprintf(arquivo,"		</table>\n");
        fprintf(arquivo,"		</td>\n");
        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"</table>\n");
        // Fim da criação de tabela com resultados do Tg-Sim


        // Gerando tabela do desdobramento da RR em RI.
        fprintf(arquivo,"<p align=\"center\">&nbsp;</p>\n");
        fprintf(arquivo,"<p align=\"center\"><font face=\"Comic Sans MS\">Reducible Representation decomposition of <font color=\"#000080\">%s</font>:</font></p>\n", _TERMO);
        fprintf(arquivo,"<table border=\"1\" align=\"center\" id=\"table6\">\n");
        fprintf(arquivo,"	<tr>\n");
        fprintf(arquivo,"		<td><font face=\"Comic Sans MS\" color=\"#000080\">&nbsp; %s &nbsp;</font></td>\n", _TERMO);

	for(i=0; i<=_MTX_RI[0][0]; i++){

		if ( _MTX_COEF_RI[i] > 0.5){
           fprintf(arquivo,"		<td><font face=\"Comic Sans MS\">&nbsp;%.0f(</font><font face=\"Comic Sans MS\" color=\"#000080\">%d%s</font><font face=\"Comic Sans MS\">)&nbsp;</font>\n</td>", _MTX_COEF_RI[i], _J, _MTX_RI[i]);
        }
    }

        fprintf(arquivo,"	</tr>\n");
        fprintf(arquivo,"</table>\n");
        // Fim da criação de tabela do desdobramento da RR em RI.

        //Finalização do arquivo HTML
        fprintf(arquivo,"</div>\n");
        fprintf(arquivo,"\n");
        fprintf(arquivo,"</body>\n");
        fprintf(arquivo,"\n");
        fprintf(arquivo,"</html>\n");

    fclose(arquivo);

    printf("\n\nHTML file successfully generated: %s\n\n", _FILENAME);


}       // Final da função que gera o HTML
