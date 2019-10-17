#include "erros.hpp"

void ErrorPrinter::addError(int line, int type) {
  result += "Linha " + to_string(line) + ": Erro ";
  switch (type)
  {
  case 1:
    result += "léxico\n";
    break;

  case 2:
    result += "sintático\n";
    break;

  case 3:
    result += "semântico\n";
    break;
  }
}
void ErrorPrinter::printError() {
  cout << result;
}