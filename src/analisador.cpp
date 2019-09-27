/* Módulo criado para encapsular o analisador sintático e léxico

*/

#include "analisador.hpp"


bool is_decimal(const string token){
  /*
  Função recebe uma string sem espaços dentro e
  retorna se é um token válido ou não.
  */
  return !token.empty() && find_if(token.begin(), 
      token.end(), [](char caractere) { return !isdigit(caractere); }) == token.end();
}

bool is_variable(const string token)
{
  if( token.empty() ) {
    return false;
  } 

  const string primeira_letra(1, token.at(0));

  if( is_decimal( primeira_letra ) ) return false;

  return find_if(token.begin(), 
      token.end(), [](char caractere) { return !isalpha(caractere) && !isdigit(caractere) && caractere != '_'; }) == token.end();
  return true;  
}

bool is_comment(const string token){
    if( token.empty() ) {
    return false;
  } 

  if( token.empty() ) {
    return false;
  } 

  const string primeira_letra(1, token.at(0));

  if( ";" != primeira_letra ) return false;

  return true;
}

bool is_label(const string token)
{
  if( token.empty() ) {
    return false;
  } 

  const string primeira_letra(1, token.at(0));

  if( is_decimal( primeira_letra ) ) return false;

  return find_if(token.begin(), 
      token.end(), [](char caractere) { return !isalpha(caractere) && !isdigit(caractere) && caractere != '_'; }) == token.end();
  return true;  
}