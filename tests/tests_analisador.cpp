#include "analisador.hpp"

Scanner* analisador_lexico = new Scanner();
Parser* analisador_sintatico = new Parser();

TEST_CASE( "Número", "[Lexico]" ) 
{ 
  //! Testes focados em validar se o analisador léxico consegue reconhecer números
  SECTION("Decimal Positivo")
  {
    REQUIRE( analisador_lexico->is_decimal("2"));
    REQUIRE( analisador_lexico->is_decimal("99999"));
    REQUIRE( analisador_lexico->is_decimal("80"));
  }// SECTION("Decimal Positivo")

  SECTION("Decimal Negativo")
  {
    REQUIRE( analisador_lexico->is_decimal("-3"));
    REQUIRE( analisador_lexico->is_decimal("-1"));
    REQUIRE( analisador_lexico->is_decimal("-34"));
  }// SECTION("Decimal Negativo")

  SECTION("Hexadecimal Válido")
  {
    REQUIRE( analisador_lexico->is_decimal("0XA3"));
    REQUIRE( analisador_lexico->is_decimal("0X33"));
    REQUIRE( analisador_lexico->is_decimal("0X0"));
  }// SECTION("Hexadecimal Válido")

  SECTION("Hexadecimal Inválido")
  {
    REQUIRE_FALSE( analisador_lexico->is_decimal("0X"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("0X3G"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("0X96X"));
  }// SECTION("Hexadecimal Inválido")

  SECTION("Somente letras")
  {
    REQUIRE_FALSE( analisador_lexico->is_decimal("LeTRas"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("L"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("25D"));


  }// SECTION("Decimal Posito")

  SECTION("Letras e Números")
  {
    REQUIRE_FALSE( analisador_lexico->is_decimal("4Let5ras2"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("L3TR4S"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("25D"));
  }// SECTION("Letras e Números")

  SECTION("Números, símbolos e letras")
  {
    REQUIRE_FALSE( analisador_lexico->is_decimal("2 4"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("L E T R A S"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("_!@2"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("@2"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("_3"));
    REQUIRE_FALSE( analisador_lexico->is_decimal("_JOSÉ"));
  } // SECTION("Números, símbolos e letras")

} // TEST_CASE( "Número", "[Lexico]" ) 

TEST_CASE( "Variável", "[Lexico]" ) 
{ 
  //! Testes focados em validar se o analisador léxico consegue reconhecer nomes de variáveis
  SECTION("Variável válida")
  {
    REQUIRE( analisador_lexico->is_variable("Variavel"));
    REQUIRE( analisador_lexico->is_variable("ROTULAO"));
    REQUIRE( analisador_lexico->is_variable("ROTU434lo"));
    REQUIRE( analisador_lexico->is_variable("Variavel_VALIDA"));
    REQUIRE( analisador_lexico->is_variable("_Variavel_VALIDA"));

  } // SECTION("Variável válido")

  SECTION("Variável começando com dígito")
  {
    REQUIRE_FALSE( analisador_lexico->is_variable("4Variavel"));
    REQUIRE_FALSE( analisador_lexico->is_variable("5ROTULAO"));
    REQUIRE_FALSE( analisador_lexico->is_variable("2ROTU434lo"));
  } //SECTION("Variável começando com dígito")

  SECTION("Variável com símbolos")
  {
    REQUIRE_FALSE( analisador_lexico->is_variable("@TULO_INVALIDO"));
    REQUIRE_FALSE( analisador_lexico->is_variable("3@OTULO_INVAlIDO"));
    REQUIRE_FALSE( analisador_lexico->is_variable("3@OTULO_INVALIDO:"));
  } // SECTION("Variável com símbolos")
} // TEST_CASE( "Variável", "[Lexico]" ) 

TEST_CASE( "Comentários", "[Lexico]" ) 
{ 
  // Validar se consegue identificar comentários
  SECTION("Reconhece ponto e vírgula no começo")
  {
    REQUIRE( analisador_lexico->is_comment(";"));
    REQUIRE( analisador_lexico->is_comment(";ISSO É UM COMENTÁRIO"));
  } // SECTION("Reconhece ponto e vírgula no começo")

  SECTION("Rejeita frases que não começam com ponto e vírgula")
  {
    REQUIRE_FALSE( analisador_lexico->is_comment("NÃO É COMENTÁRIO;"));
    REQUIRE_FALSE( analisador_lexico->is_comment("ISSO NÃO É UM COMENTÁRIO"));
    REQUIRE_FALSE( analisador_lexico->is_comment("ISSO NÃO É UM; COMENTÁRIO"));
    REQUIRE_FALSE( analisador_lexico->is_comment("I;SSO NÃO É UM; COMENTÁRIO"));
  } // SECTION("Rejeita frases que não começam com ponto e vírgula")
} // TEST_CASE( "Comentários", "[Lexico]" )

TEST_CASE( "Rótulo", "[Lexico]" ) 
{ /* Validar se consegue reconhecer um rótulo */
  SECTION("Rótulo válido")
  {
    REQUIRE(analisador_lexico->is_label("Abacate:"));
    REQUIRE(analisador_lexico->is_label("Abac4te:"));
    REQUIRE(analisador_lexico->is_label("Abac_ate:"));
    REQUIRE(analisador_lexico->is_label("Abac_4te:"));
    REQUIRE(analisador_lexico->is_label("_Abacate:"));


  } // SECTION("Rótulo válido")

  SECTION("Rótulo inválido")
  {
    REQUIRE_FALSE(analisador_lexico->is_label("5Abacate:"));
    REQUIRE_FALSE(analisador_lexico->is_label("5Ab@cate:"));
    REQUIRE_FALSE(analisador_lexico->is_label("Abacate"));
    REQUIRE_FALSE(analisador_lexico->is_label(":Abacat32"));
    REQUIRE_FALSE(analisador_lexico->is_label("Abac:at32"));
    REQUIRE_FALSE(analisador_lexico->is_label("Abacat32::"));
  } // SECTION("Rótulo inválido")
} //TEST_CASE( "Rótulo", "[Lexico]" ) 


TEST_CASE( "Diretiva", "[Lexico]" )
{
  SECTION("Diretivas válidas")
  {
    REQUIRE(analisador_lexico->is_directive  ("SECTION"));
    REQUIRE(analisador_lexico->is_directive  ("CONST"));
    REQUIRE(analisador_lexico->is_directive  ("SPACE"));
    REQUIRE(analisador_lexico->is_directive  ("EQU"));
    REQUIRE(analisador_lexico->is_directive  ("IF"));

  } // SECTION("Diretiva válida")

  SECTION("Diretivas inválidas")
  {
    REQUIRE_FALSE(analisador_lexico->is_directive  ("SESSÃO"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("SESSAO"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("SESSION"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("3SADSADA"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("2SECTION"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("_SECTION"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("S3CTION"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("SECTION1"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("SECTIONN"));

    REQUIRE_FALSE(analisador_lexico->is_directive  ("ADD"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("MULT"));

  } // SECTION("Sessão inválida")
} // TEST_CASE( "Sessão", "[Lexico]" )

TEST_CASE( "OPCODE", "[Lexico]" )
{
  SECTION("OPCODE válido")
  {
    REQUIRE(analisador_lexico->is_opcode("ADD"));
    REQUIRE(analisador_lexico->is_opcode("SUB"));
    REQUIRE(analisador_lexico->is_opcode("MULT"));

    REQUIRE(analisador_lexico->is_opcode("DIV"));
    REQUIRE(analisador_lexico->is_opcode("JMP"));
    REQUIRE(analisador_lexico->is_opcode("JMPN"));

    REQUIRE(analisador_lexico->is_opcode("JMPP"));
    REQUIRE(analisador_lexico->is_opcode("JMPZ"));
    REQUIRE(analisador_lexico->is_opcode("COPY"));

    REQUIRE(analisador_lexico->is_opcode("LOAD"));
    REQUIRE(analisador_lexico->is_opcode("STORE"));
    REQUIRE(analisador_lexico->is_opcode("INPUT"));

    REQUIRE(analisador_lexico->is_opcode("OUTPUT"));
    REQUIRE(analisador_lexico->is_opcode("STOP"));
  } // SECTION("OPCODE válido")

  SECTION("OPCODE inválido")
  {
    REQUIRE_FALSE(analisador_lexico->is_directive  ("SESSÃO"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("SESSAO"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("SESSION"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("3SADSADA"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("2SECTION"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("_SECTION"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("S3CTION"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("SECTION1"));
    REQUIRE_FALSE(analisador_lexico->is_directive  ("SECTIONN"));
    REQUIRE_FALSE(analisador_lexico->is_label("5Abacate:"));
    REQUIRE_FALSE(analisador_lexico->is_label("5Ab@cate:"));
    REQUIRE_FALSE(analisador_lexico->is_label("Abacate"));
    REQUIRE_FALSE(analisador_lexico->is_label(":Abacat32"));
    REQUIRE_FALSE(analisador_lexico->is_label("Abac:at32"));
    REQUIRE_FALSE(analisador_lexico->is_label("Abacat32::"));
  }// SECTION("OPCODE inválido")
} // TEST_CASE( "OPCODE", "[Lexico]" )

TEST_CASE( "Exceções ", "[Lexico]" )
{
  SECTION("Sinal de Soma")
  {
    REQUIRE( analisador_lexico->is_symbol("+") );
    REQUIRE_FALSE( analisador_lexico->is_symbol("PARA+QUE+TER+SOMENTE+UM+SINAL+NA+LINGUAGEM+TODA") );
  }

  SECTION("Argumentos do COPY")
  {
    REQUIRE( analisador_lexico->is_copyargumment("PARAQUE,SOMENTENOCOPY") );
    REQUIRE( analisador_lexico->is_copyargumment("PARAQUE+2,SOMENTENOCOPY") );
    REQUIRE( analisador_lexico->is_copyargumment("PARAQUE,SOMENTENOCOPY+4") );
    REQUIRE( analisador_lexico->is_copyargumment("PARAQUE,3") );
    REQUIRE( analisador_lexico->is_copyargumment("PARAQUE+2,3") );
    REQUIRE( analisador_lexico->is_copyargumment("2,SOMENTENOCOPY") );
    REQUIRE( analisador_lexico->is_copyargumment("2,3") );
    REQUIRE_FALSE( analisador_lexico->is_copyargumment("PARA,QUE,SOMENT2ENOCOPY") );
  }
} // TEST_CASE( "Exceções ", "[Lexico]" )

TEST_CASE( "Retorna Token", "[Lexico]" )
{
  SECTION("Token válido")
  {
    REQUIRE(analisador_lexico->tokenize("1")      == "DECIMAL");
    REQUIRE(analisador_lexico->tokenize("-30")    == "DECIMAL");
    REQUIRE(analisador_lexico->tokenize("298302") == "DECIMAL");
    REQUIRE(analisador_lexico->tokenize("0XFFFF") == "DECIMAL");


    REQUIRE(analisador_lexico->tokenize(";comentário")  == "COMMENT");
    REQUIRE(analisador_lexico->tokenize(";PAPO;MA@SSA") == "COMMENT");
    REQUIRE(analisador_lexico->tokenize(";298302")      == "COMMENT");

    REQUIRE(analisador_lexico->tokenize("Start:")  == "LABEL");
    REQUIRE(analisador_lexico->tokenize("MEXICO:") == "LABEL");
    REQUIRE(analisador_lexico->tokenize("CAFE23:") == "LABEL");

    REQUIRE(analisador_lexico->tokenize("VARIAVEL") == "VARIABLE");
    REQUIRE(analisador_lexico->tokenize("V4R4V3L")  == "VARIABLE");
    REQUIRE(analisador_lexico->tokenize("POPOPO")   == "VARIABLE");

    REQUIRE(analisador_lexico->tokenize("ADD")  == "OPCODE");
    REQUIRE(analisador_lexico->tokenize("SUB")  == "OPCODE");
    REQUIRE(analisador_lexico->tokenize("JMPP") == "OPCODE");

    REQUIRE(analisador_lexico->tokenize("SECTION") == "DIRECTIVE");
    REQUIRE(analisador_lexico->tokenize("EQU")     == "DIRECTIVE");
    REQUIRE(analisador_lexico->tokenize("IF")      == "DIRECTIVE");

    REQUIRE(analisador_lexico->tokenize("+") == "SYMBOL");
    REQUIRE(analisador_lexico->tokenize("CHOCOLATE,PIMENTA")     == "COPYARGS");
  } // SECTION("Token válido")

  SECTION("Token inválido")
  {
    REQUIRE(analisador_lexico->tokenize("1NVALIDO") == "INVALID");
    REQUIRE(analisador_lexico->tokenize("!NVALIDO") == "INVALID");
    REQUIRE(analisador_lexico->tokenize("NTA@ONISTA") == "INVALID");

  } // SECTION("Token inválido")

} // TEST_CASE( "Token", "[Lexico]" )

TEST_CASE( "Valida linha", "[Sintático]" ) 
{ 
  SECTION("Linhas com opcodes de um argumento")
  {
    REQUIRE( analisador_sintatico->monta_linha("ADD 1") == "1 1");
    REQUIRE( analisador_sintatico->monta_linha("ADD VARIAVEL ;CURTO COMENTAR CODIGO PORQUE É UMA BOA PRATICA") == "1 00");
    REQUIRE( analisador_sintatico->monta_linha("ADD VARIAVEL") == "1 00");
    REQUIRE( analisador_sintatico->monta_linha("SUB VARIAVEL") == "2 00");
    REQUIRE( analisador_sintatico->monta_linha("MULT 5 ;COMENTARIO") == "3 5");
    REQUIRE( analisador_sintatico->monta_linha("JMP VARIAVEL") == "5 00");
    REQUIRE( analisador_sintatico->monta_linha("STORE 43") == "11 43");
  } // SECTION("Linhas com opcodes de um argumento")

  SECTION( "Monta linha com opcodes sem argumentos")
  {
    REQUIRE( analisador_sintatico->monta_linha("STOP") == "14");
    REQUIRE( analisador_sintatico->monta_linha("STOP ;COMENTARIO") == "14");
  } // SECTION("Linhas com opcodes de um argumento")

  SECTION( "Monta linha com opcodes com dois argumentos")
  {
    REQUIRE( analisador_sintatico->monta_linha("COPY 1,2") == "9 1 2");
    REQUIRE( analisador_sintatico->monta_linha("COPY NEW_DATA,2") == "9 00 2");
    REQUIRE( analisador_sintatico->monta_linha("COPY 1,OLD_DATA") == "9 1 00");
    REQUIRE( analisador_sintatico->monta_linha("COPY NEW_DATA,OLD_DATA") == "9 00 00");
    REQUIRE( analisador_sintatico->monta_linha("COPY NEW_DATA+1,OLD_DATA") == "9 001 00");
    REQUIRE( analisador_sintatico->monta_linha("COPY NEW_DATA,OLD_DATA+2") == "9 00 002");

  }
} // TEST_CASE( "Valida linha", "[Sintático]" ) 
