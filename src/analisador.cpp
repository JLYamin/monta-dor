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

bool Scanner::is_copysubargument( string argumento )
{
  size_t coordenada_primeira_soma = argumento.find("+", 0);
  if( coordenada_primeira_soma == string::npos ){
    // Se não possuir operador de soma então
    // validamos se o primeiro argumento é ou um decimal ou uma variável
    if( !is_variable(argumento) && !is_decimal(argumento) ) return false;

  } else {
    // Caso possua, validamos se o primeiro subargumento é um label e se o segundo é um 
    // decimal
      string primeiro_subargumento = argumento.substr(0, coordenada_primeira_soma);
      if ( !is_variable(primeiro_subargumento) ) return false;
      string segundo_subargumento = argumento.substr( coordenada_primeira_soma + 1, argumento.size()-1 );
      if( !is_decimal(segundo_subargumento) ) return false;
  }

  return true;
}
bool Scanner::is_copyargumment( string palavra )
{ 
  if( palavra.empty() ) return false;
  //Procuramos a primeira vírgula
  size_t coordenada_primeira_virgula = palavra.find(",", 0);
  if( coordenada_primeira_virgula == string::npos ) return false;

  // Se ela existir, primeiro validamos se o primeiro argumento possui um sinal de soma
  string primeiro_argumento = palavra.substr(0, coordenada_primeira_virgula);
  if( !is_copysubargument( primeiro_argumento) ) return false;

  // Repetimos o processo para o segundo argumento
  string segundo_argumento = palavra.substr( coordenada_primeira_virgula + 1, palavra.size()-1 );
  if( !is_copysubargument( segundo_argumento )) return false;

  
  
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

Parser::Parser()
{
  analisador_lexico = new Scanner();
  contagem_endereco = 0;
}

int Parser::get_ultimo_endereco()
{
  return contagem_endereco;
}


Parser::~Parser()
{
  delete(analisador_lexico);
}

string Parser::monta_subargumento(const string  subargumento )
{
  size_t coordenada_simbolo_soma = subargumento.find("+", 0);
  string codigo_subargumento;
  string rotulo = subargumento.substr(0, coordenada_simbolo_soma);
  string decimal = subargumento.substr( coordenada_simbolo_soma + 1, subargumento.size()-1 );
  codigo_subargumento = " 00" + decimal;
  return codigo_subargumento;
}

string Parser::monta_argumento(const string argumento )
{
  string codigo_objeto_argumento;
  string token_argumento = analisador_lexico->tokenize(argumento);

  if( token_argumento == "VARIABLE" )
  // Dependendo do tipo do TOKEN, a linha é montada de forma diferente
  {
    codigo_objeto_argumento = " 00";
  } else if( token_argumento == "DECIMAL" ) {
    codigo_objeto_argumento = " " + argumento;
  }  else if( token_argumento == "COPYARGS" ) {
    size_t coordenada_primeira_virgula = argumento.find(",", 0);

    string primeiro_subargumento = argumento.substr( 0, coordenada_primeira_virgula );
    string segundo_subargumento = argumento.substr( coordenada_primeira_virgula + 1, argumento.size()-1 ); 
    
    string primeiro_subtoken = analisador_lexico->tokenize( primeiro_subargumento );
    string segundo_subtoken = analisador_lexico->tokenize( segundo_subargumento );
    
    if( primeiro_subtoken == "VARIABLE" )
    {
      codigo_objeto_argumento = " 00";
    } else if( primeiro_subtoken == "DECIMAL" ) {
      codigo_objeto_argumento = " " + primeiro_subargumento;
    } else {
      // Se não for nem variável nem decimal, mas ainda for um copyarg válido 
      // então deve haver um símbolo de soma separando um rotulo e um decimal
      codigo_objeto_argumento = monta_subargumento( primeiro_subargumento );
    }

    if( segundo_subtoken == "VARIABLE")
    {
      codigo_objeto_argumento = codigo_objeto_argumento + " 00";
    } else if ( segundo_subtoken == "DECIMAL" ) {
      codigo_objeto_argumento = codigo_objeto_argumento + " " + segundo_subargumento;
    } else {
      codigo_objeto_argumento = codigo_objeto_argumento + monta_subargumento( segundo_subargumento );
    }
  }
  return codigo_objeto_argumento;
}

string Parser::monta_linha(const string linha)
{ 
  if( linha.empty() ) return "";

  //Procuramos o primeiro espaço
  size_t coordenada_primeiro_espaco = linha.find(" ", 0);
  string primeira_palavra;
  string codigo_objeto;
  // Caso não haja o primeiro espaço, então há uma palavra ou nenhuma
  if( coordenada_primeiro_espaco == string::npos ) 
      { 
        primeira_palavra = linha.substr(0, linha.size() );
      } else {
        primeira_palavra = linha.substr(0, coordenada_primeiro_espaco );
      }
  // Validamos a primeira palavra e a partir do token, fazemos diferentes comportamentos
  string primeiro_token = analisador_lexico->tokenize(primeira_palavra);
  if( primeiro_token == "INVALID" ) return "";
  if( primeiro_token == "OPCODE")
  {
    vector<int> dados_opcode = analisador_lexico->tabela_opcodes[primeira_palavra];
    // O segundo inteiro dos dados da tabela de opcodes é o tamanho da instrução
    // uma instrução sempre tem o tamanho do mnemônico somado ao número de argumentos
    // O primeiro é o seu código objeto
    string opcode = to_string(dados_opcode[0]);
    contagem_endereco += dados_opcode[1];
    int quantidade_argumentos = dados_opcode[1] - 1;
    codigo_objeto = opcode;

    if ( quantidade_argumentos > 0 ) {
    // Se for um opcode de somente um argumento, ele aceita operações com variáveis
    // ou com números
      //Procuramos o segundo espaço
      size_t coordenada_segundo_espaco = linha.find(" ", coordenada_primeiro_espaco+1);
      string argumento; 
      // Se não houver segundo espaço, buscamos o segundo token como a última palavra
      // Se houver, é a segunda palavra
      if( coordenada_segundo_espaco == string::npos ) 
      { 
        argumento = linha.substr(coordenada_primeiro_espaco + 1, linha.size()-1 );
      } else {
        argumento = linha.substr(coordenada_primeiro_espaco + 1, coordenada_segundo_espaco - coordenada_primeiro_espaco -1 );
      }
      codigo_objeto = codigo_objeto + monta_argumento(argumento);
    } 
  } else if( primeiro_token == "LABEL" ){
    // Se for um label, adiciona o endereço a tabela de símbolos e avalia o resto da linha normalmente
    string resto_linha;
    if( coordenada_primeiro_espaco == string::npos ) 
      { 
        resto_linha = "";
      } else {
        resto_linha = linha.substr(coordenada_primeiro_espaco + 1, linha.size()-coordenada_primeiro_espaco-1);
      }
    
    codigo_objeto = monta_linha(resto_linha);
    }
  return codigo_objeto;

  // Se for um decimal já imprime direto
  // se for uma variável verificar se está tabela de símbolos, se não estiver declarada adicionar 
  // na lista de pendências. Adiciona o endereço, se não tiver, adiciona 0
  // Depois que validar o código todo validar se todas as pendÊncias foram resolvidas.
}

Assembler::Assembler()
{
  analisador_sintatico = new Parser();
}

Assembler::~Assembler()
{
  delete(analisador_sintatico);
}


string Assembler::monta_texto( string nome_arquivo )
{
  string texto = leitor->carrega_texto( nome_arquivo );
  string codigo_objeto = "";
  int contagem_linha = 0;
  istringstream iss(texto);

  for (string linha; getline(iss, linha); contagem_linha += 1, codigo_objeto = codigo_objeto + " ")
  {
    codigo_objeto = codigo_objeto + analisador_sintatico->monta_linha(linha);
  }
  codigo_objeto = codigo_objeto.substr(0, codigo_objeto.size()-1);
  
  return codigo_objeto;
}