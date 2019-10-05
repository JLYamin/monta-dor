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

bool Scanner::is_decimal(const string palavra ){
  /*
  Função recebe uma string sem espaços dentro e
  retorna se é um palavra válido ou não.
  */
  if( palavra.empty() ) return false;
  bool eh_inteiro = false;
  bool eh_hexadecimal = false;

  
  string primeiro_simbolo = palavra.substr(0, 1);
  // Primeiro validamos se é inteiro
  string possivel_numero = palavra;
  if (primeiro_simbolo == "-")
  {
    possivel_numero = possivel_numero.substr(1, possivel_numero.size() - 1);
  }

  eh_inteiro = find_if(possivel_numero.begin(), 
      possivel_numero.end(), [](char caractere) { return !isdigit(caractere); }) == possivel_numero.end();
  
  // Depois validamos se é hexadecimal
  if( palavra.size() > 2 )
  {
    string dois_primeiros_simbolos = palavra.substr(0, 2);
    if( dois_primeiros_simbolos == "0X")
    {
      string possivel_hexadecimal = palavra.substr(2, palavra.size() - 2);
      
      eh_hexadecimal = find_if(possivel_hexadecimal.begin(), 
      possivel_hexadecimal.end(), [](char caractere) { return !isxdigit(caractere); }) == possivel_hexadecimal.end();
    
    } else {

      eh_hexadecimal = false;
    }
  }

  return eh_inteiro || eh_hexadecimal;
}

bool Scanner::is_variable(const string palavra )
{
  /* Verifica se é o nome de uma variável válido */
  if( palavra.empty() ) {
    return false;
  } 

  const string primeiro_simbolo(1, palavra.at(0));

  if( is_decimal( primeiro_simbolo ) ) return false;

  return find_if(palavra.begin(), 
      palavra.end(), [](char caractere) { return !isalpha(caractere) && !isdigit(caractere) && caractere != '_'; }) == palavra.end();
  return true;  
}

bool Scanner::is_comment(const string palavra )
{
    if( palavra.empty() ) {
    return false;
  } 

  if( palavra.empty() ) {
    return false;
  } 

  const string primeiro_simbolo(1, palavra.at(0));

  if( ";" != primeiro_simbolo ) return false;

  return true;
}

bool Scanner::is_label(const string palavra )
{
  if( palavra.empty() ) {
    return false;
  } 

  const string primeiro_simbolo(1, palavra.at(0));
  const string ultimo_simbolo(1, palavra.at(palavra.size()-1));
  
  if( is_decimal( primeiro_simbolo ) ) return false;

  //Valida se o último símbolo é : 
  if( ultimo_simbolo.find(":", 0) == string::npos ) return false;

  const string corpo_rotulo(palavra.substr(0, palavra.size() - 1));

  return find_if(corpo_rotulo.begin(), 
      corpo_rotulo.end(), [](char caractere) { return !isalpha(caractere) && !isdigit(caractere) && caractere != '_'; }) == corpo_rotulo.end();
  return true;  
}

bool Scanner::is_directive(const string palavra )
{
  if (!is_label( palavra )) 
  {
    return ( tabela_directives.find(palavra )  != tabela_directives.end() );
  } else {
    return false;
  }
}

bool Scanner::is_opcode(const string palavra )
{

  if (!is_label( palavra )) 
  {
    return ( tabela_opcodes.find(palavra )  != tabela_opcodes.end() );
  } else {
    return false;
  }
}

bool Scanner::is_symbol(const string palavra )
{
  if ( palavra.empty() ) return false;
  if ( palavra == "+") return true;
  else return false;
}

bool Scanner::is_copyargumment( string palavra )
{ 
  if( palavra.empty() ) return false;
  //Procuramos a primeira vírgula
  size_t coordenada_primeira_virgula = palavra.find(",", 0);
  if( coordenada_primeira_virgula == string::npos ) return false;

  // Se ela existir, validamos se o primeiro argumento é ou um decimal ou uma variável
  string primeiro_argumento = palavra.substr(0, coordenada_primeira_virgula);
  if( !is_variable(primeiro_argumento) && !is_decimal(primeiro_argumento) ) return false;

  //Se o primeiro for, validamos para o segundo
  string segundo_argumento = palavra.substr( coordenada_primeira_virgula + 1 , palavra.size()-1 );
  if( !is_variable(segundo_argumento) && !is_decimal(segundo_argumento) ) return false;
  
  return true;
}

string Scanner::tokenize(const string palavra )
{
  // A ordem das validações é importante para OPCODE, DIRECTIVE e VARIABLE
  if ( is_decimal(       palavra ) )    return "DECIMAL";
  if ( is_comment(       palavra ) )    return "COMMENT";
  if ( is_label(         palavra ) )    return "LABEL";

  if ( is_opcode(        palavra ) )    return "OPCODE";
  if ( is_directive(     palavra ) )    return "DIRECTIVE";
  if ( is_variable(      palavra ) )    return "VARIABLE";
  
  if ( is_symbol(        palavra ) )    return "SYMBOL";
  if ( is_copyargumment( palavra ) )    return "COPYARGS";

  // Se não for um palavra conhecido, ele é inválido
  return "INVALID";

}