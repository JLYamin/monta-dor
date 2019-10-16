#include "leitura_e_impressao.hpp"
#ifndef CATCH_H
#define CATCH_H
#include "catch.hpp"
#endif
#include <unordered_map> 

class Scanner
{
    public:
    unordered_map< string, vector<int> > tabela_opcodes;
    unordered_map< string, int > tabela_directives;
    Scanner( );
    ~Scanner();
    bool is_decimal(       string );
    bool is_variable(      string );
    bool is_comment(       string );
    bool is_label(         string );
    bool is_directive(     string );
    bool is_opcode(        string );
    bool is_symbol(        string );
    bool is_copyargumment( string );
    bool is_copysubargument( string );


    string tokenize(string);

};

class Parser
{   
    public:
    Parser();
    ~Parser();
    Scanner* analisador_lexico;
    string monta_linha(string);

    private:
    string monta_argumento(const string );
    string monta_subargumento(const string );


};




