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

  const string primeiro_simbolo(1, token.at(0));

  if( is_decimal( primeiro_simbolo ) ) return false;

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

  const string primeiro_simbolo(1, token.at(0));

  if( ";" != primeiro_simbolo ) return false;

  return true;
}

bool is_label(const string token)
{
  if( token.empty() ) {
    return false;
  } 

  const string primeiro_simbolo(1, token.at(0));
  if( is_decimal( primeiro_simbolo ) ) return false;

  if( token.at(token.size()-1) != ':') return false;

  const string corpo_rotulo(token.substr(0, token.size() - 1));

  return find_if(corpo_rotulo.begin(), 
      corpo_rotulo.end(), [](char caractere) { return !isalpha(caractere) && !isdigit(caractere) && caractere != '_'; }) == corpo_rotulo.end();
  return true;  
}

bool is_session(const string token)
{
  if (!is_label(token )) 
  {
    
    return ( token == "SECTION" );
  } else {
    return false;
  }
}

bool is_opcode(const string token)
{
  return false;
}