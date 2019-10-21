#include "analisador.hpp"



int main(int numero_argumentos, char *argumentos_terminal[])
{   
  string nome_arquivo, nome_pasta, codigo_objeto;
  Assembler* montador = new Assembler();

  if( numero_argumentos > 2 )
  {
    nome_pasta = argumentos_terminal[2];
    nome_arquivo = argumentos_terminal[1];
  } else if ( numero_argumentos > 1 ) {
    nome_pasta = "entradas_asm/";
    nome_arquivo = argumentos_terminal[1];
  } else {
    nome_pasta = "entradas_asm/";
    nome_arquivo = "bin.asm";
  }
  codigo_objeto = montador->monta_texto(nome_arquivo, nome_pasta);
  
  return 0;
}
