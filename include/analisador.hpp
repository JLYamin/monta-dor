#include "reader_writer.hpp"
#include "escritor.hpp"
#include "preprocessador.hpp"
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
    bool is_decimal(       string );
    bool is_variable(      string );
    bool is_comment(       string );
    bool is_label(         string );
    bool is_directive(     string );
    bool is_opcode(        string );
    bool is_symbol(        string );
    bool is_copyargumment( string );
    bool is_variable_plus_decimal(  string );


    string tokenize(string);

};

class Parser
{   
    public:
    Parser();
    ~Parser();
    Scanner* analisador_lexico;
    string monta_linha(string);
    int get_ultimo_endereco();
    void reset_endereco();

    private:
    vector<int> indice_enderecos;
    int contagem_endereco;
    string monta_argumento( const string );
    string monta_subargumento( const string, const int );


};

class Assembler
{   
    public:
    Assembler();
    ~Assembler();
    Parser* analisador_sintatico;
    ReaderWriter* leitor;
    string monta_texto( string, string );


};




