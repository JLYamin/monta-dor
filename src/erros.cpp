#include "erros.hpp"

void ErrorPrinter::addError(int line, int type, string message)
{
  
  switch (type)
  {
  case 1:
    result += "Linha " + to_string(line) + ": Erro " + message;
    result += "\n";
    break;

  case 2:
    result += "Linha " + to_string(line) + ": Erro " + message;
    result += "\n";
    break;

  case 3:
    result += "Erro: " + message;
    result += "\n";
    break;
  }
}
void ErrorPrinter::printError() {
  cout << result;
}