/* Módulo criado para encapsular funções de leitura e escrita

*/

#include "reader_writer.hpp"

string ReaderWriter::carrega_texto(string caminho_do_arquivo_completo = "Entradas ASM/bin.asm")
{
  ifstream infile (caminho_do_arquivo_completo);
  string data;

  if (infile) {
    // open a file in read mode.
    
    infile.seekg (0, infile.end);
    int length = infile.tellg();
    infile.seekg (0, infile.beg);

    char * buffer = new char [length];

    // read data as a block:
    infile.read (buffer,length);
    infile.close();

    data = buffer;

    // ...buffer contains the entire file...

    transform(data.begin(), data.end(), data.begin(), ::toupper);

    regex multiplos_espacos_comeco_linha("\n([\t ]+)");
    regex multiplos_espacos("([\t ]+)");
    regex multiplos_saltos_linha("(\n+)");

    data = regex_replace(data, multiplos_espacos, " ");
    data = regex_replace(data, multiplos_espacos_comeco_linha, "\n");
    data = regex_replace(data, multiplos_saltos_linha, "\n");
  } else {
    return "";
    cout << "Problemas ao ler arquivo";
  }
    return data;
}

/*
int main(){
  ReaderWriter leitura;
  cout << leitura.texto_lido;
  return 0;
}
*/