# monta-dor
Repositório do Primeiro Trabalho de Software Básico da Universidade de Brasília

### Alunos:
- João Lucas Azevedo Yamin Rodrigues da Cunha
- Thiago Luis Rodrigues Pinho

**Link da especificação do trabalho:** [1º Trabalho Prático - Aprender UnB](https://aprender.ead.unb.br/pluginfile.php/724430/mod_resource/content/0/Trabalho1.pdf)

## Regrinhas:
- Vamos seguir os rolês de git e criar branches para as funcionalidades que estaremos fazendo;
- É isto, acabou as regras não consigo pensar em outras.

## To do list:

(*Baseado nas funcionalidades que a princípio acho que existirão*)
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
  - [ ] Detecção de Erros
    - [x] Detecção de erros léxicos
    - [ ] Detecção de erros sintáticos
    - [ ] Detecção de erros semânticos
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

 Acho que é isso! Fique com esse gif fofo:

 ![Gif fofo](https://media.giphy.com/media/4Zo41lhzKt6iZ8xff9/giphy.gif "Cachorrinhoooo")


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
Após isso, você pode executar o montador usando o comando
```
./montador "bin.asm"
```
Para qualquer outro arquivo .asm dentro da pasta Entradas ASM, basta digitar seu nome com a extensão

```
./simulador "bin.obj"
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