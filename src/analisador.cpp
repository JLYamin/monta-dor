/* Módulo criado para encapsular o analisador sintático e léxico

*/

#include "analisador.hpp"
#include "tabelas.hpp"

extern vector<SymbolRow> symbolTable;

// Tabela de símbolos

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

void Parser::reset_endereco()
{
  contagem_endereco = 0;
}


Parser::~Parser()
{
  delete(analisador_lexico);
}

string Parser::monta_subargumento(const string  subargumento, const int contagem_argumentos )
{
  size_t coordenada_simbolo_soma = subargumento.find("+", 0);
  string codigo_subargumento;
  string rotulo = subargumento.substr(0, coordenada_simbolo_soma);
  string decimal = subargumento.substr( coordenada_simbolo_soma + 1, subargumento.size()-1 );
  codigo_subargumento = " 00" + decimal;
  if( !checkSymbol( rotulo) ) addSymbol(rotulo, 0, false);
      addPendency(rotulo, get_ultimo_endereco() + contagem_argumentos );
  return codigo_subargumento;
}

string Parser::monta_argumento(const string argumento )
{
  string codigo_objeto_argumento;
  int endereco_atual = get_ultimo_endereco();
  string token_argumento = analisador_lexico->tokenize(argumento);

  if( token_argumento == "VARIABLE" )
  // Dependendo do tipo do TOKEN, a linha é montada de forma diferente
  {
    // Se for uma variável e não tiver sido adicionada à tabela, adiciona ela como não definida
    //if( !checkSymbol(argumento) ) addSymbol(argumento, 0, false);
    codigo_objeto_argumento = " 00";
    // Adicionamos então o símbolo à tabela de pendências para depois trocarmos pelo valor correto
    if(!checkSymbol(argumento)) addSymbol(argumento, endereco_atual+1, false);
    addPendency(argumento, endereco_atual + 1);
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
      if( !checkSymbol(primeiro_subargumento) ) addSymbol(primeiro_subargumento, 0, false);
      addPendency(primeiro_subargumento, endereco_atual + 1);
      codigo_objeto_argumento = " 00";
    } else if( primeiro_subtoken == "DECIMAL" ) {
      codigo_objeto_argumento = " " + primeiro_subargumento;
    } else {
      // Se não for nem variável nem decimal, mas ainda for um copyarg válido 
      // então deve haver um símbolo de soma separando um rotulo e um decimal
      codigo_objeto_argumento = monta_subargumento( primeiro_subargumento, 1 );
    }

    if( segundo_subtoken == "VARIABLE")
    {
      if( !checkSymbol(segundo_subargumento) ) addSymbol(segundo_subargumento, 0, false);
      addPendency(segundo_subargumento, endereco_atual + 2);
      codigo_objeto_argumento = codigo_objeto_argumento + " 00";
    } else if ( segundo_subtoken == "DECIMAL" ) {
      codigo_objeto_argumento = codigo_objeto_argumento + " " + segundo_subargumento;
    } else {
      codigo_objeto_argumento = codigo_objeto_argumento + monta_subargumento( segundo_subargumento, 2 );
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
        argumento = linha.substr(coordenada_primeiro_espaco + 1, linha.size() - coordenada_primeiro_espaco-1 );
      } else {
        argumento = linha.substr(coordenada_primeiro_espaco + 1, coordenada_segundo_espaco - coordenada_primeiro_espaco -1 );
      }
      codigo_objeto = codigo_objeto + monta_argumento( argumento );
    } 
    contagem_endereco += dados_opcode[1];

  } else if( primeiro_token == "LABEL" ) {
    // Se for um label, adiciona o endereço a tabela de símbolos e avalia o resto da linha normalmente
    string resto_linha;
    
    
    if( coordenada_primeiro_espaco == string::npos ) 
      { 
        resto_linha = "";
    } else {
        resto_linha = linha.substr(coordenada_primeiro_espaco + 1, linha.size()-coordenada_primeiro_espaco-1);
    }
    size_t coordenada_segundo_espaco = resto_linha.find(" ", 0);
    string segunda_palavra, segundo_token;
    segunda_palavra = resto_linha.substr(0, coordenada_segundo_espaco);
    segundo_token = analisador_lexico->tokenize( segunda_palavra );

    if( segundo_token == "DIRECTIVE") {
    // Caso seja uma diretiva, após o pré-processamento ela pode ser uma SECTION, um CONST ou um SPACE
        size_t coordenada_terceiro_espaco = resto_linha.find(" ", coordenada_segundo_espaco+1 );
        string terceira_palavra, terceiro_token;

      if( segunda_palavra == "CONST" )
      {
        if( coordenada_terceiro_espaco == string::npos ) 
        {
          terceira_palavra = resto_linha.substr(coordenada_segundo_espaco + 1, resto_linha.size() - coordenada_segundo_espaco - 1);
        } else {
          terceira_palavra = resto_linha.substr(coordenada_segundo_espaco + 1, coordenada_terceiro_espaco - coordenada_segundo_espaco - 1);
        }
        // Caso exista uma segunda palavra, ela deve ser obrigatoriamente um decimal
        terceiro_token = analisador_lexico->tokenize( terceira_palavra );

        if( terceiro_token != "DECIMAL" ) return ""; // HOUVE UM ERRO, DEVERIA SER UM DECIMAL

        if( checkSymbol( primeira_palavra.substr(0, primeira_palavra.size()-1)  ) )
        // Se o símbolo já tiver sido adicionado, atualiza seu endereço e o define
        {
          updateSymbol( primeira_palavra.substr(0, primeira_palavra.size()-1) , get_ultimo_endereco() );
        } else {
        // Se não o símbolo é adicionado a tabela já definido
          addSymbol( primeira_palavra.substr(0, primeira_palavra.size()-1) , get_ultimo_endereco(), true );
        }
        codigo_objeto = terceira_palavra;
        contagem_endereco += 1;
      } else if( segunda_palavra == "SPACE") {
      // Se for um SPACE devemos verificar se há um argumento e alocar isso em memória
        if(coordenada_terceiro_espaco == string::npos )
        // Se não há argumento, aloca-se somente um espaço
        {
          if( checkSymbol( primeira_palavra.substr(0, primeira_palavra.size()-1)  ) )
          // Se o símbolo já tiver sido adicionado, atualiza seu endereço e o define
          {
          updateSymbol( primeira_palavra.substr(0, primeira_palavra.size()-1) , get_ultimo_endereco() );
          } else {
          // Se não o símbolo é adicionado a tabela já definido
          addSymbol( primeira_palavra.substr(0, primeira_palavra.size()-1) , get_ultimo_endereco(), true );
          }
        } else {
          terceira_palavra = resto_linha.substr(coordenada_segundo_espaco + 1, coordenada_terceiro_espaco - coordenada_segundo_espaco - 1);
          // Caso exista uma segunda palavra, ela deve ser obrigatoriamente um decimal
          terceiro_token = analisador_lexico->tokenize( terceira_palavra );

          if( terceiro_token != "DECIMAL" ) return ""; // HOUVE UM ERRO, DEVERIA SER UM DECIMAL

          if( checkSymbol( primeira_palavra.substr(0, primeira_palavra.size()-1)  ) )
          // Se o símbolo já tiver sido adicionado, atualiza seu endereço e o define
          {
            updateSymbol(primeira_palavra, get_ultimo_endereco() );
          } else {
          // Se não o símbolo é adicionado a tabela já definido
            addSymbol( primeira_palavra.substr(0, primeira_palavra.size()-1) , get_ultimo_endereco(), true );
          }
        } 
        contagem_endereco += 1;
        codigo_objeto = codigo_objeto + "00";
      }
    } else {
      if( !checkSymbol( primeira_palavra ) )
      {
        addSymbol( primeira_palavra.substr(0, primeira_palavra.size()-1), get_ultimo_endereco(), true );
      } else {
        cout << "Erro" << endl; // UM ERRO OCORREU, DUAS DEFINIÇÕES DO MESMO ROTULO
      } 
      
      codigo_objeto = codigo_objeto + monta_linha(resto_linha);
    }
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
  string nome_pasta = "Entradas ASM/";
  string codigo_objeto = "";
  string codigo_objeto_linha, nome_rotulo, codigo_pendente, codigo_corrigido, texto_preprocessado;
  int endereco_pendencia, coordenada_equ, indice_inicio_codigo_objeto, indice_final_codigo_objeto, contagem_linha = 0;
  vector<int> indice_enderecos;

  string texto = leitor->carrega_texto( nome_pasta+nome_arquivo );
  coordenada_equ = texto.find("EQU", 0);
  if( coordenada_equ == string::npos ){
    texto_preprocessado = texto;
  } else {
    texto_preprocessado = ifProcessor(texto);
  }
  createFilePre(texto_preprocessado, nome_arquivo );
  istringstream iss(texto_preprocessado);

  symbolTable.clear();
  analisador_sintatico->reset_endereco();
  for (string linha; getline(iss, linha); contagem_linha += 1)
  { 
    codigo_objeto_linha = analisador_sintatico->monta_linha(linha);
    if( codigo_objeto_linha != "") 
    {
      codigo_objeto = codigo_objeto + codigo_objeto_linha + " ";
      // Armazenamos então o índice do endereço
    }
  }
  // Remove o último espaço
  codigo_objeto = codigo_objeto.substr(0, codigo_objeto.size()-1);
  indice_enderecos.push_back(0);
  for(unsigned int i = 0; i < codigo_objeto.length(); ++i) 
  {
    char caractere_objeto = codigo_objeto[i];
    char espaco = ' ';

    if( caractere_objeto == espaco )
    {
      indice_enderecos.push_back(i);
    }
  }
  // Depois precisamos resolver as pendências
  for(unsigned int i = 0; i < symbolTable.size(); i++ )
  {
    if( symbolTable[i].is_defined )
    { 
      nome_rotulo = symbolTable[i].symbol;
      do{
        endereco_pendencia = resolvePendency(nome_rotulo);
        indice_inicio_codigo_objeto = indice_enderecos[endereco_pendencia];
        indice_final_codigo_objeto = indice_enderecos[endereco_pendencia+1];

        if( endereco_pendencia == -1 ) break;

        codigo_corrigido = to_string(symbolTable[i].address);
        codigo_objeto.replace(indice_inicio_codigo_objeto+1, indice_final_codigo_objeto - indice_inicio_codigo_objeto - 1, codigo_corrigido);
      } while( endereco_pendencia != -1 );
    }
  }
  createFileObj( codigo_objeto, nome_arquivo );

  return codigo_objeto;
}