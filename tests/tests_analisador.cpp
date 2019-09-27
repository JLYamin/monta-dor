#include "analisador.hpp"

TEST_CASE( "Número", "[Lexico]" ) 
{ 
  //! Testes focados em validar se o analisador léxico consegue reconhecer números
  SECTION("Decimal Posito")
  {
    REQUIRE( analisador_lexico("2"));
    REQUIRE( analisador_lexico("99999"));
    REQUIRE( analisador_lexico("80"));
  }// SECTION("Decimal Posito")

  SECTION("Somente letras")
  {
    REQUIRE_FALSE( analisador_lexico("LeTRas"));
    REQUIRE_FALSE( analisador_lexico("L"));
    REQUIRE_FALSE( analisador_lexico("25D"));


  }// SECTION("Decimal Posito")

  SECTION("Letras e Números")
  {
    REQUIRE_FALSE( analisador_lexico("4Let5ras2"));
    REQUIRE_FALSE( analisador_lexico("L3TR4S"));
    REQUIRE_FALSE( analisador_lexico("25D"));
  }// SECTION("Letras e Números")

  SECTION("Números, símbolos e letras")
  {
    REQUIRE_FALSE( analisador_lexico("2 4"));
    REQUIRE_FALSE( analisador_lexico("L E T R A S"));
    REQUIRE_FALSE( analisador_lexico("_!@2"));
    REQUIRE_FALSE( analisador_lexico("@2"));
    REQUIRE_FALSE( analisador_lexico("_3"));
    REQUIRE_FALSE( analisador_lexico("_JOSÉ"));



  }

} // TEST_CASE( "Number", "[Lexico]" ) 