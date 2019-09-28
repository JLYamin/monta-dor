/* Módulo criado para encapsular funções de leitura e escrita

*/

#include "leitura_e_impressao.hpp"


Leitor::Leitor(string caminho_do_arquivo_completo = "Entradas ASM/bin.asm")
{
  ifstream infile (caminho_do_arquivo_completo);
  if (infile) {
    string data;
    // open a file in read mode.
    
    cout << "Reading from the file" << endl; 
    infile >> data; 

    infile.seekg (0, infile.end);
    int length = infile.tellg();
    infile.seekg (0, infile.beg);

    char * buffer = new char [length];

    std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    infile.read (buffer,length);

    cout << "Arquivo lido com sucesso";
    cout << buffer;
    
    infile.close();

    // ...buffer contains the entire file...

    delete[] buffer;
    transform(data.begin(), data.end(), data.begin(), ::toupper);
  } else {
      cout << "Problemas ao ler arquivo";
  }
}

/*
int main(){
  /* Main criada para testes manuais 
  Leitor leitura;
  cout << leitura.texto_lido;
  return 0;
}
*/