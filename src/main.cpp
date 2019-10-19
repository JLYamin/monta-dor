#include "analisador.hpp"



int main(int argc, char *argumentos_terminal[])
{   
    string nome_arquivo = argumentos_terminal[1];
    string nome_pasta = "Entradas ASM/"
    string codigo_objeto;
    Assembler* montador = new Assembler();
    codigo_objeto = montador->monta_texto(nome_arquivo, nome_pasta);
    cout << codigo_objeto << endl;
    return 0;
}
