/* Módulo criado para encapsular funções de leitura e escrita

*/
#include <fstream>
#include <iostream>
using namespace std;

int main () {
  ifstream infile ("Entradas ASM/bin.asm");
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
  } else {
      cout << "Problemas ao ler arquivo";
  }

   return 0;
}