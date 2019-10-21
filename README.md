## Montador e Simulador de Assembly Inventado
### Disciplina de Software Básico - Turma B - 2019/2
Alunos:
- João Lucas Azevedo Yamin Rodrigues da Cunha - 17/0013731
- Thiago Luis Rodrigues Pinho - 15/0065205

## Informações a respeito do trabalho:

Este trabalho foi desenvolvido com C++ utilizando-se dois sistemas operacionais diferentes: tanto no Ubuntu quanto no Linux Subsystem do Windows.

Este trabalho foi feito orientado a testes ao final desse documento há uma explicação de como rodar os testes.

## Nós nos organizamos por funcionalidades a serem cumpridas

#### Montador:
  - [x] Leitura
    - [x] Receber e abrir o arquivo
    - [x] Contador de endereços/posição 
  - [x] Parser
    - [x] Detecção das áreas de texto e *data*
    - [x] Detecção das linhas
    - [x] Detecção das instruções
    - [x] Detecção dos argumentos das instruções
    - [x] Detecção de rótulos (com ou sem enter após)
  - [x] Tabelas
    - [x] Tabela de Instruções para consulta
    - [x] Montagem da tabela de símbolos
  - [x] Detecção de Erros
    - [x] Detecção de erros léxicos
    - [x] Detecção de erros sintáticos
    - [x] Detecção de erros semânticos
    - [x] Exibição das linhas e classificação dos erros
  - [x] Código de Máquina
    - [x] Adicionar o *opcode*
    - [x] Resolver as pendências dos endereços da Tabela de Símbolos
  - [x] Arquivos de Saída
    - [x] Geração do arquivo pré-processado (*não sei se entendi do que se trata*)
    - [x] Geração do arquivo objeto contendo o código de máquina
 #### Simulador:
   - [x] Receber o programa de entrada
   - [x] Identificar as instruções de INPUT e OUTPUT, exibindo o texto pedido
   - [x] Identificar e executar as instruções
   - [x] Exibir o conteúdo do acumulador ao executar uma instrução
   - [x] Exibir o endereço e conteúdo de endereços modificados pela instrução


### Instalação

Depois de extrair ou clonar o repositório, entre na pasta principal e digite em seu terminal:
Para compilar o montador:
```
make montador
```

Para compilar o simulador
```
make simulador
```


### Usando o Montador e o Simulador
Após isso, você pode executar o montador ou o simulador usando o comando
```
./montador bin.asm
```

```
./simulador bin.obj
```

Para qualquer outro arquivo .asm dentro da pasta entradas_asm, basta digitar seu nome com a extensão. Também é possível especificar qual pasta você gostaria de buscar o arquivo a ser aberto.
```
./montador bin.asm ./entradas_asm/
```

```
./simulador bin.obj ./saidas/
```


## Executando os testes

Na pasta principal:
Para compilar todos os testes, basta digitar:
```
make all_tester
```
Se você quiser ver os testes antes de executá-los:
```
./all_tester --list-tests
```
Ou pode somente rodar os testes:
```
./all_tester
```

## Para limpar arquivos intermediários
```
make clean
```
