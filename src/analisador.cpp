/* Módulo criado para encapsular o analisador sintático e léxico

*/

#include "analisador.hpp"

Scanner::Scanner()
{
  /* Na tabela de OPCODES, o primeiro termo é a chave, o segundo é um vetor de inteiro com 
  o código da instrução e o tamanho que ela ocupará 
  */
  tabela_opcodes = {   {"ADD", {1, 2}}, {"SUB", {2, 2}}, {"MULT", {3, 2}}
        , {"DIV", {4, 2}}, {"JMP", {5, 2}}, {"JMPN", {6, 2}}
        , {"JMPP", {7, 2}}, {"JMPZ", {8, 2}}, {"COPY", {9, 3}}
        , {"LOAD", {10, 2}}, {"STORE", {11, 2}}, {"INPUT", {12, 2}}
        , {"OUTPUT", {13, 2}}, {"STOP", {14, 1}}
    };

  tabela_directives = { {"SECTION", 1 }
        ,  {"SPACE", 1 }
        ,  {"CONST", 1 }
        ,  {"EQU", 1 }
        ,  {"IF", 1 }
    };
}

bool Scanner::is_decimal(const string token){
  /*
  Função recebe uma string sem espaços dentro e
  retorna se é um token válido ou não.
  */
  if( token.empty() ) return false;
  bool eh_inteiro = false;
  bool eh_hexadecimal = false;

  
  string primeiro_simbolo = token.substr(0, 1);
  // Primeiro validamos se é inteiro
  string possivel_numero = token;
  if (primeiro_simbolo == "-")
  {
    possivel_numero = possivel_numero.substr(1, possivel_numero.size() - 1);
  }

  eh_inteiro = find_if(possivel_numero.begin(), 
      possivel_numero.end(), [](char caractere) { return !isdigit(caractere); }) == possivel_numero.end();
  
  // Depois validamos se é hexadecimal
  if( token.size() > 2 )
  {
    string dois_primeiros_simbolos = token.substr(0, 2);
    if( dois_primeiros_simbolos == "0X")
    {
      string possivel_hexadecimal = token.substr(2, token.size() - 2);
      
      eh_hexadecimal = find_if(possivel_hexadecimal.begin(), 
      possivel_hexadecimal.end(), [](char caractere) { return !isxdigit(caractere); }) == possivel_hexadecimal.end();
    
    } else {

      eh_hexadecimal = false;
    }
  }

  return eh_inteiro || eh_hexadecimal;
}

bool Scanner::is_variable(const string token)
{
  /* Verifica se é o nome de uma variável válido */
  if( token.empty() ) {
    return false;
  } 

  const string primeiro_simbolo(1, token.at(0));

  if( is_decimal( primeiro_simbolo ) ) return false;

  return find_if(token.begin(), 
      token.end(), [](char caractere) { return !isalpha(caractere) && !isdigit(caractere) && caractere != '_'; }) == token.end();
  return true;  
}

bool Scanner::is_comment(const string token)
{
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

bool Scanner::is_label(const string token)
{
  if( token.empty() ) {
    return false;
  } 

  const string primeiro_simbolo(1, token.at(0));
  const string ultimo_simbolo(1, token.at(token.size()-1));
  
  if( is_decimal( primeiro_simbolo ) ) return false;

  //Valida se o último símbolo é : 
  if( ultimo_simbolo.find(":", 0) == string::npos ) return false;

  const string corpo_rotulo(token.substr(0, token.size() - 1));

  return find_if(corpo_rotulo.begin(), 
      corpo_rotulo.end(), [](char caractere) { return !isalpha(caractere) && !isdigit(caractere) && caractere != '_'; }) == corpo_rotulo.end();
  return true;  
}

bool Scanner::is_directive(const string token)
{
  if (!is_label( token )) 
  {
    return ( tabela_directives.find(token)  != tabela_directives.end() );
  } else {
    return false;
  }
}

bool Scanner::is_opcode(const string token)
{

  if (!is_label( token )) 
  {
    return ( tabela_opcodes.find(token)  != tabela_opcodes.end() );
  } else {
    return false;
  }
}

bool Scanner::is_symbol(const string token)
{
  if ( token.empty() ) return false;
  if ( token == "+") return true;
  else return false;
}

bool Scanner::is_copyargumment( string token )
{ 
  if( token.empty() ) return false;
  //Procuramos a primeira vírgula
  size_t coordenada_primeira_virgula = token.find(",", 0);
  if( coordenada_primeira_virgula == string::npos ) return false;

  // Se ela existir, validamos se o primeiro argumento é ou um decimal ou uma variável
  string primeiro_argumento = token.substr(0, coordenada_primeira_virgula);
  if( !is_variable(primeiro_argumento) && !is_decimal(primeiro_argumento) ) return false;

  //Se o primeiro for, validamos para o segundo
  string segundo_argumento = token.substr( coordenada_primeira_virgula + 1 , token.size()-1 );
  if( !is_variable(segundo_argumento) && !is_decimal(segundo_argumento) ) return false;
  
  return true;
}

string Scanner::tokenize(const string token )
{
  // A ordem das validações é importante para OPCODE, DIRECTIVE e VARIABLE
  if ( is_decimal(   token ) )    return "DECIMAL";
  if ( is_comment(   token ) )    return "COMMENT";
  if ( is_label(     token ) )    return "LABEL";

  if ( is_opcode(    token ) )    return "OPCODE";
  if ( is_directive( token ) )    return "DIRECTIVE";
  if ( is_variable(  token ) )    return "VARIABLE";

  // Se não for um token conhecido, ele é inválido
  return "INVALID";

}