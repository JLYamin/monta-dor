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
  - [ ] Leitura
    - [ ] Receber e abrir o arquivo
    - [ ] Contador de endereços/posição
  - [ ] Parser
    - [ ] Detecção das áreas de texto e *data*
    - [ ] Deteção das linhas
    - [ ] Detecção das instruções
    - [ ] Detecção dos argumentos das instruções
    - [ ] Detecção de rótulos (com ou sem enter após)
  - [ ] Tabelas
    - [ ] Tabela de Instruções para consulta
    - [ ] Montagem da tabela de símbolos
  - [ ] Detecção de Erros
    - [ ] Detecção de erros léxicos
    - [ ] Detecção de erros sintáticos
    - [ ] Detecção de erros semânticos
    - [ ] Exibição das linhas e classificação dos erros
  - [ ] Código de Máquina
    - [ ] Adicionar o *opcode*
    - [ ] Resolver as pendências dos endereços da Tabela de Símbolos
  - [ ] Arquivos de Saída
    - [ ] Geração do arquivo pré-processado (*não sei se entendi do que se trata*)
    - [ ] Geração do arquivo objeto contendo o código de máquina
 #### Simulador:
   - [ ] Receber o programa de entrada
   - [ ] Identificar as instruções de INPUT e OUTPUT, exibindo o texto pedido
   - [ ] Identificar e executar as instruções
   - [ ] Exibir o conteúdo do acumulador ao executar uma instrução
   - [ ] Exibir o endereço e conteúdo de endereços modificados pela instrução
   
 Acho que é isso! Fique com esse gif fofo:
 
 ![Gif fofo](https://media.giphy.com/media/4Zo41lhzKt6iZ8xff9/giphy.gif "Cachorrinhoooo")


### Instalação

Depois de extrair ou clonar o repositório, entre na pasta principal e digite em seu terminal:
```
make
```

### Usando o Simulador
Após isso, você pode executar o simulador usando  ocomando
```
./play_assembler
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