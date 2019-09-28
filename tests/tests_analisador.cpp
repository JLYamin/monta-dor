#include "analisador.hpp"

TEST_CASE( "Número", "[Lexico]" ) 
{ 
  //! Testes focados em validar se o analisador léxico consegue reconhecer números
  SECTION("Decimal Posito")
  {
    REQUIRE( is_decimal("2"));
    REQUIRE( is_decimal("99999"));
    REQUIRE( is_decimal("80"));
  }// SECTION("Decimal Posito")

  SECTION("Somente letras")
  {
    REQUIRE_FALSE( is_decimal("LeTRas"));
    REQUIRE_FALSE( is_decimal("L"));
    REQUIRE_FALSE( is_decimal("25D"));


  }// SECTION("Decimal Posito")

  SECTION("Letras e Números")
  {
    REQUIRE_FALSE( is_decimal("4Let5ras2"));
    REQUIRE_FALSE( is_decimal("L3TR4S"));
    REQUIRE_FALSE( is_decimal("25D"));
  }// SECTION("Letras e Números")

  SECTION("Números, símbolos e letras")
  {
    REQUIRE_FALSE( is_decimal("2 4"));
    REQUIRE_FALSE( is_decimal("L E T R A S"));
    REQUIRE_FALSE( is_decimal("_!@2"));
    REQUIRE_FALSE( is_decimal("@2"));
    REQUIRE_FALSE( is_decimal("_3"));
    REQUIRE_FALSE( is_decimal("_JOSÉ"));
  } // SECTION("Números, símbolos e letras")

} // TEST_CASE( "Número", "[Lexico]" ) 

TEST_CASE( "Variável", "[Lexico]" ) 
{ 
  //! Testes focados em validar se o analisador léxico consegue reconhecer nomes de variáveis
  SECTION("Variável válida")
  {
    REQUIRE( is_variable("Variavel"));
    REQUIRE( is_variable("ROTULAO"));
    REQUIRE( is_variable("ROTU434lo"));
    REQUIRE( is_variable("Variavel_VALIDO"));
  } // SECTION("Variável válido")

  SECTION("Variável começando com dígito")
  {
    REQUIRE_FALSE( is_variable("4Variavel"));
    REQUIRE_FALSE( is_variable("5ROTULAO"));
    REQUIRE_FALSE( is_variable("2ROTU434lo"));
  } //SECTION("Variável começando com dígito")

  SECTION("Variável com símbolos")
  {
    REQUIRE_FALSE( is_variable("@TULO_INVALIDO"));
    REQUIRE_FALSE( is_variable("3@OTULO_INVAlIDO"));
    REQUIRE_FALSE( is_variable("3@OTULO_INVALIDO:"));
  } // SECTION("Variável com símbolos")
} // TEST_CASE( "Variável", "[Lexico]" ) 

TEST_CASE( "Comentários", "[Lexico]" ) 
{ 
  // Validar se consegue identificar comentários
  SECTION("Reconhece ponto e vírgula no começo")
  {
    REQUIRE( is_comment(";"));
    REQUIRE( is_comment(";ISSO É UM COMENTÁRIO"));
  } // SECTION("Reconhece ponto e vírgula no começo")

  SECTION("Rejeita frases que não começam com ponto e vírgula")
  {
    REQUIRE_FALSE( is_comment("NÃO É COMENTÁRIO;"));
    REQUIRE_FALSE( is_comment("ISSO NÃO É UM COMENTÁRIO"));
    REQUIRE_FALSE( is_comment("ISSO NÃO É UM; COMENTÁRIO"));
    REQUIRE_FALSE( is_comment("I;SSO NÃO É UM; COMENTÁRIO"));
  } // SECTION("Rejeita frases que não começam com ponto e vírgula")
} // TEST_CASE( "Comentários", "[Lexico]" )

TEST_CASE( "Rótulo", "[Lexico]" ) 
{ /* Validar se consegue reconhecer um rótulo */
  SECTION("Rótulo válido")
  {
    REQUIRE(is_label("Abacate:"));
    REQUIRE(is_label("Abac4te:"));
    REQUIRE(is_label("Abac_ate:"));
    REQUIRE(is_label("Abac_4te:"));

  } // SECTION("Rótulo válido")

  SECTION("Rótulo inválido")
  {
    REQUIRE_FALSE(is_label("5Abacate:"));
    REQUIRE_FALSE(is_label("5Ab@cate:"));
    REQUIRE_FALSE(is_label("Abacate"));
    REQUIRE_FALSE(is_label(":Abacat32"));
    REQUIRE_FALSE(is_label("Abac:at32"));
    REQUIRE_FALSE(is_label("Abacat32::"));
  } // SECTION("Rótulo inválido")
} //TEST_CASE( "Rótulo", "[Lexico]" ) 


TEST_CASE( "Sessão", "[Lexico]" )
{
  SECTION("Sessão válida")
  {
    REQUIRE(is_session  ("SECTION"));

  } // SECTION("Sessão válida")

  SECTION("Sessão inválida")
  {
    REQUIRE_FALSE(is_session  ("SESSÃO"));
    REQUIRE_FALSE(is_session  ("SESSAO"));
    REQUIRE_FALSE(is_session  ("SESSION"));
    REQUIRE_FALSE(is_session  ("3SADSADA"));
    REQUIRE_FALSE(is_session  ("2SECTION"));
    REQUIRE_FALSE(is_session  ("_SECTION"));
    REQUIRE_FALSE(is_session  ("S3CTION"));
    REQUIRE_FALSE(is_session  ("SECTION1"));
    REQUIRE_FALSE(is_session  ("SECTIONN"));
  } // SECTION("Sessão inválida")
} // TEST_CASE( "Sessão", "[Lexico]" )

TEST_CASE( "OPCODE", "[Lexico]" )
{
  SECTION("OPCODE válido")
  {
    REQUIRE(is_opcode("ADD"));
    REQUIRE(is_opcode("SUB"));
    REQUIRE(is_opcode("MULT"));

    REQUIRE(is_opcode("DIV"));
    REQUIRE(is_opcode("JMP"));
    REQUIRE(is_opcode("JMPN"));

    REQUIRE(is_opcode("JMPP"));
    REQUIRE(is_opcode("JMPZ"));
    REQUIRE(is_opcode("COPY"));

    REQUIRE(is_opcode("LOAD"));
    REQUIRE(is_opcode("STORE"));
    REQUIRE(is_opcode("INPUT"));

    REQUIRE(is_opcode("OUTPUT"));
    REQUIRE(is_opcode("STOP"));
  } // SECTION("OPCODE válido")

  SECTION("OPCODE inválido")
  {
    REQUIRE_FALSE(is_session  ("SESSÃO"));
    REQUIRE_FALSE(is_session  ("SESSAO"));
    REQUIRE_FALSE(is_session  ("SESSION"));
    REQUIRE_FALSE(is_session  ("3SADSADA"));
    REQUIRE_FALSE(is_session  ("2SECTION"));
    REQUIRE_FALSE(is_session  ("_SECTION"));
    REQUIRE_FALSE(is_session  ("S3CTION"));
    REQUIRE_FALSE(is_session  ("SECTION1"));
    REQUIRE_FALSE(is_session  ("SECTIONN"));
    REQUIRE_FALSE(is_label("5Abacate:"));
    REQUIRE_FALSE(is_label("5Ab@cate:"));
    REQUIRE_FALSE(is_label("Abacate"));
    REQUIRE_FALSE(is_label(":Abacat32"));
    REQUIRE_FALSE(is_label("Abac:at32"));
    REQUIRE_FALSE(is_label("Abacat32::"));
  }// SECTION("OPCODE inválido")
} // TEST_CASE( "OPCODE", "[Lexico]" )