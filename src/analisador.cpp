/* Módulo criado para encapsular o analisador sintático e léxico

*/

#include "analisador.hpp"


bool is_decimal(const string s){
  /*
  Função recebe uma string sem espaços dentro e
  retorna se é um token válido ou não.
  */
  return !s.empty() && find_if(s.begin(), 
      s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

bool is_label(const string s)
{
  return false;
}