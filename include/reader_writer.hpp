#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

using namespace std;

class ReaderWriter
{
    public:
    string carrega_texto(string);

    private:
    string texto_lido;
};