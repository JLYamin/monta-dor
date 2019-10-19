#include "analisador.hpp"



int main(int argc, char *argumentos_terminal[])
{   
    string nome_arquivo = argumentos_terminal[1];
    string path_pasta_arquivos = ("Entradas ASM/");
    string codigo_objeto;
    Assembler* montador = new Assembler();
    codigo_objeto = montador->monta_texto(path_pasta_arquivos+nome_arquivo);
    cout << codigo_objeto << endl;
    return 0;
}
