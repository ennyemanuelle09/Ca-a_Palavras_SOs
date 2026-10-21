# Caça-Palavras --- Sistemas Operacionais

## 1. Apresentação

O **Caça-Palavras --- Sistemas Operacionais** é um projeto educativo
desenvolvido para praticar conceitos introdutórios de Sistemas
Operacionais por meio de um jogo de caça-palavras. O jogador deve
localizar termos relacionados ao funcionamento de um computador e ao
sistema operacional.

O projeto possui duas versões: - **Versão em C:** jogo executado no
terminal, com geração de grades e validação das palavras por
coordenadas. - **Versão web:** adaptação para navegador, construída com
HTML, CSS e JavaScript e publicada pelo GitHub Pages.

> A versão web é uma implementação em JavaScript das funcionalidades do
> jogo. O arquivo em C é mantido separadamente como código-fonte da
> versão de terminal; o GitHub Pages não executa diretamente arquivos
> `.c`.

## 2. Objetivos

### Objetivo geral

Apoiar a aprendizagem de conceitos de Sistemas Operacionais de forma
interativa e lúdica.

### Objetivos específicos

-   Reforçar o reconhecimento de termos técnicos da área.
-   Oferecer três níveis de dificuldade progressiva.
-   Apresentar textos de apoio relacionados às palavras de cada nível.
-   Praticar lógica de programação, manipulação de matrizes, strings,
    funções e validação de entradas na versão em C.
-   Demonstrar a separação entre estrutura, apresentação e comportamento
    na versão web.

## 3. Conteúdo e níveis

  --------------------------------------------------------------------------
  Nível            Tamanho da grade na        Quantidade de Palavras
                           versão em C             palavras 
  --------------- -------------------- -------------------- ----------------
  1 --- Fácil                    8 × 8                    4 CPU, RAM,
                                                            KERNEL, SISTEMA

  2 --- Médio                  12 × 12                    6 PROCESSO,
                                                            MEMORIA,
                                                            ARQUIVO, DRIVER,
                                                            NUCLEO, USUARIO

  3 --- Difícil                15 × 15                    7 ESCALONAMENTO,
                                                            PROCESSADOR,
                                                            SEGURANCA,
                                                            MULTITAREFA,
                                                            MEMORIA,
                                                            ARQUIVO,
                                                            PROCESSO
  --------------------------------------------------------------------------

A versão em C apresenta um texto de apoio em cada nível. Os textos
relacionam os termos do jogo com conceitos como kernel, processamento,
memória, arquivos, drivers, escalonamento, multitarefa e segurança.

## 4. Funcionamento da versão em C

O programa cria uma grade para cada nível e posiciona as palavras em
direções horizontais, verticais e diagonais, inclusive em sentidos
invertidos. As casas que não recebem palavras são preenchidas com letras
aleatórias.

Durante a partida, o jogador: 1. Consulta o texto de apoio. 2. Visualiza
a grade numerada e a lista de palavras. 3. Digita a palavra que deseja
marcar. 4. Informa a linha e a coluna inicial e a linha e a coluna
final. 5. Recebe uma mensagem indicando se a seleção está correta. 6.
Acompanha a pontuação e as palavras já encontradas.

O programa valida se a palavra pertence à lista, impede que uma palavra
já encontrada seja pontuada novamente e verifica as coordenadas. Digitar
`FIM` permite sair da partida antes de concluir o nível. Para avançar
automaticamente, é necessário concluir o nível atual.

### Principais recursos de programação em C

-   Bibliotecas padrão: `stdio.h`, `stdlib.h`, `string.h`, `ctype.h` e
    `time.h`.
-   Matrizes bidimensionais para representar a grade.
-   Vetores e strings para armazenar as palavras.
-   Funções para inicializar, preencher e exibir a grade.
-   Geração aleatória de posições e letras.
-   Conversão da entrada para letras maiúsculas.
-   Validação de coordenadas e comparação de palavras.
-   Controle de pontuação e progressão entre níveis.

## 5. Funcionamento da versão web

A versão web permite jogar no navegador sem compilar o programa C no
computador do jogador. Ela usa os seguintes arquivos:

-   **`index.html`** --- estrutura da página e elementos do jogo.
-   **`style.css`** --- estilos visuais e organização da interface.
-   **`app.js`** --- lógica de interação, seleção de letras, palavras,
    pontuação e progressão dos níveis.
-   **`caca_palavras_reserva_atualizado.c`** --- código-fonte da versão
    em C, disponibilizado separadamente no repositório.

A versão web possui grade interativa e lista de palavras, apresenta
textos de apoio, atualiza a pontuação e avança entre os níveis conforme
a implementação JavaScript. Ao concluir todos os níveis, apresenta uma
mensagem de congratulação e permite iniciar novamente.

## 6. Tecnologias utilizadas

  Tecnologia           Utilização
  -------------------- --------------------------------------------
  Linguagem C          Implementação do jogo de terminal
  HTML                 Estrutura da página web
  CSS                  Aparência da versão web
  JavaScript           Interações e regras da versão web
  Visual Studio Code   Edição dos arquivos e desenvolvimento
  GitHub               Armazenamento e compartilhamento do código
  GitHub Pages         Publicação da versão web

## 7. Como executar a versão em C

1.  Tenha um compilador C instalado, como GCC, ou utilize um ambiente de
    desenvolvimento compatível.

2.  Abra o terminal na pasta que contém
    `caca_palavras_reserva_atualizado.c`.

3.  Compile o programa. Com GCC, por exemplo:

    ``` bash
    gcc caca_palavras_reserva_atualizado.c -o caca_palavras
    ```

4.  Execute o programa:

    -   No Windows, dependendo do terminal: `caca_palavras.exe`
    -   No Linux ou macOS: `./caca_palavras`

Se o compilador ou o terminal tiver uma configuração diferente, os
comandos podem precisar de pequenos ajustes.

## 8. Como executar a versão web localmente

1.  Baixe ou clone o repositório.

2.  Abra a pasta do projeto no Visual Studio Code.

3.  Abra o terminal na pasta onde estão `index.html`, `style.css` e
    `app.js`.

4.  Inicie um servidor local com Python:

    ``` bash
    python -m http.server 8000
    ```

5.  Abra `http://localhost:8000/` no navegador, desde que os três
    arquivos estejam nessa pasta.

Mantenha o terminal aberto enquanto estiver usando o servidor local.
Para encerrar o servidor, pressione `Ctrl+C` no terminal.

## 9. Publicação e acesso

A versão web está configurada para publicação pelo GitHub Pages. O
endereço esperado do projeto é:

**https://ennyemanuelle09.github.io/Ca-a_Palavras_SOs/**

Se o endereço não abrir, confira em **Settings → Pages** se a publicação
está configurada para a branch `main` e a pasta `/(root)`, e aguarde a
conclusão da implantação em **Actions**.

O repositório também permite consultar os arquivos-fonte. O GitHub Pages
publica a versão web estática; ele não compila nem executa o arquivo C.

## 10. Regras e condições de conclusão

-   Cada nível apresenta uma lista específica de palavras.
-   O jogador deve selecionar ou informar corretamente a palavra e sua
    posição, conforme a versão utilizada.
-   Uma palavra encontrada é marcada na lista e contabilizada na
    pontuação.
-   A conclusão de um nível libera o próximo.
-   A conclusão dos três níveis representa a finalização do jogo.

## 11. Possíveis melhorias futuras

-   Exibir instruções iniciais mais detalhadas.
-   Adicionar botão de pausa e opção de reiniciar o nível atual.
-   Registrar o tempo de conclusão e a melhor pontuação.
-   Melhorar recursos de acessibilidade, como navegação por teclado e
    contraste.
-   Adicionar explicações ou um glossário para cada termo.
-   Automatizar testes das regras e da validação das palavras.

## 12. Considerações finais

O projeto combina conteúdo introdutório de Sistemas Operacionais com
prática de programação. A versão em C demonstra a construção de um jogo
de terminal com matrizes, strings, funções e validação de entradas. A
versão web torna a experiência acessível pelo navegador e permite
compartilhar o jogo por meio do GitHub Pages.

------------------------------------------------------------------------

**Nome do projeto:** Caça-Palavras --- Sistemas Operacionais\
**Arquivo principal em C:** `caca_palavras_reserva_atualizado.c`\
**Arquivos da versão web:** `index.html`, `style.css` e `app.js`
