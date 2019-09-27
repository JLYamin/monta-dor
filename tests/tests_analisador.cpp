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
  }

} // TEST_CASE( "Número", "[Lexico]" ) 

TEST_CASE( "Rótulo", "[Lexico]" ) 
{ 
  //! Testes focados em validar se o analisador léxico consegue reconhecer números
  SECTION("Rótulo válido")
  {
    REQUIRE( is_variable("Variavel"));
    REQUIRE( is_variable("ROTULAO"));
    REQUIRE( is_variable("ROTU434lo"));
    REQUIRE( is_variable("Variavel_VALIDO"));
  }

  SECTION("Rótulo começando com dígito")
  {
    REQUIRE_FALSE( is_variable("4Variavel"));
    REQUIRE_FALSE( is_variable("5ROTULAO"));
    REQUIRE_FALSE( is_variable("2ROTU434lo"));
  }

  SECTION("Rótulo com símbolos")
  {
    REQUIRE_FALSE( is_variable("@TULO_INVALIDO"));
    REQUIRE_FALSE( is_variable("3@OTULO_INVAlIDO"));
    REQUIRE_FALSE( is_variable("3@OTULO_INVALIDO:"));
  }
} // TEST_CASE( "Rótulo", "[Lexico]" ) 

TEST_CASE( "Comentários", "[Lexico]" ) 
{ 
  SECTION("Reconhece ponto e vírgula")
  {
    REQUIRE( is_comment(";"));
  }
}