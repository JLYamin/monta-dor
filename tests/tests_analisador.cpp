#include "analisador.hpp"

Scanner* analisador_lexico = new Scanner();
TEST_CASE( "Número", "[Lexico]" ) 
{ 
  //! Testes focados em validar se o analisador léxico consegue reconhecer números
  SECTION("Decimal Posito")
  {
    REQUIRE( analisador_lexico->is_decimal("2"));
    REQUIRE( analisador_lexico->is_decimal("99999"));
    REQUIRE( analisador_lexico->is_decimal("80"));
  }// SECTION("Decimal Posito")

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
    REQUIRE( analisador_lexico->is_variable("Variavel_VALIDO"));
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
