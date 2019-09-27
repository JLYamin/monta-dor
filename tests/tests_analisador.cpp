#include "analisador.hpp"

TEST_CASE( "Número", "[Lexico]" ) 
{ 
  //! Testes focados em validar se o analisador léxico consegue reconhecer números
  SECTION("Decimal Posito")
  {
    REQUIRE( analisador_lexico("2"));
  }// SECTION("Decimal Posito")

} // TEST_CASE( "Number", "[Lexico]" ) 