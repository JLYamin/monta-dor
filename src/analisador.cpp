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

bool is_variable(const string s)
{
  if( s.empty() ) {
    return false;
  } 

  const string primeira_letra(1, s.at(0));

  if( is_decimal( primeira_letra ) ) return false;

  return find_if(s.begin(), 
      s.end(), [](char c) { return !isalpha(c) && !isdigit(c) && c != '_'; }) == s.end();
  return true;  
}