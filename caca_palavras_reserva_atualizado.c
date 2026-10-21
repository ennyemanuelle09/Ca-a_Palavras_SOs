
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX 15
#define MAX_WORDS 10
#define WORD_LEN 24

char grade[MAX][MAX];
char palavras[MAX_WORDS][WORD_LEN];
int encontradas[MAX_WORDS];
int tamanho, totalPalavras;

int dl[8] = {-1,-1,-1,0,0,1,1,1};
int dc[8] = {-1,0,1,-1,1,-1,0,1};

/* Converte uma palavra para letras maiusculas */
void maiusculo(char texto[]) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        texto[i] = toupper((unsigned char)texto[i]);
    }
}

/* Inicializa a grade */
void inicializarGrade(void) {
    int i, j;

    for (i = 0; i < tamanho; i++)
        for (j = 0; j < tamanho; j++)
            grade[i][j] = '.';
}

/* Verifica se uma palavra cabe na posicao */
int podeInserir(char palavra[], int l, int c, int d) {
    int i, x, y;
    int n = strlen(palavra);

    for (i = 0; i < n; i++) {
        x = l + i * dl[d];
        y = c + i * dc[d];

        if (x < 0 || x >= tamanho ||
            y < 0 || y >= tamanho)
            return 0;

        if (grade[x][y] != '.' &&
            grade[x][y] != palavra[i])
            return 0;
    }

    return 1;
}

/* Insere uma palavra em uma das oito direcoes */
int inserirPalavra(char palavra[]) {
    int tentativa, l, c, d, i;

    if ((int)strlen(palavra) > tamanho)
        return 0;

    for (tentativa = 0; tentativa < 10000; tentativa++) {
        l = rand() % tamanho;
        c = rand() % tamanho;
        d = rand() % 8;

        if (podeInserir(palavra, l, c, d)) {
            for (i = 0; palavra[i] != '\0'; i++) {
                grade[l + i * dl[d]]
                     [c + i * dc[d]] = palavra[i];
            }
            return 1;
        }
    }

    return 0;
}

/* Preenche os espacos restantes */
void completarGrade(void) {
    int i, j;

    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            if (grade[i][j] == '.')
                grade[i][j] = 'A' + rand() % 26;
        }
    }
}

/* Exibe a grade com numeracao */
void mostrarGrade(void) {
    int i, j;

    printf("\n    ");
    for (j = 0; j < tamanho; j++)
        printf("%2d ", j + 1);

    printf("\n");

    for (i = 0; i < tamanho; i++) {
        printf("%2d  ", i + 1);

        for (j = 0; j < tamanho; j++)
            printf(" %c ", grade[i][j]);

        printf("\n");
    }
}

/* Exibe as palavras pendentes */
void mostrarPalavras(void) {
    int i;

    printf("\nPalavras para encontrar:\n");

    for (i = 0; i < totalPalavras; i++)
        printf("[%c] %s\n",
               encontradas[i] ? 'X' : ' ',
               palavras[i]);
}

/*
   Le dois numeros de uma linha.
   Aceita: 5 8, 5 e 8 ou 5,8.
*/
int lerPar(int *a, int *b, char mensagem[]) {
    char linha[100];
    char *p, *fim;
    long primeiro, segundo;

    while (1) {
        printf("%s", mensagem);

        if (fgets(linha, sizeof(linha), stdin) == NULL)
            return 0;

        p = linha;

        while (*p && !isdigit((unsigned char)*p))
            p++;

        if (!*p) {
            printf("Digite dois numeros. Exemplo: 5 e 8.\n");
            continue;
        }

        primeiro = strtol(p, &fim, 10);
        p = fim;

        while (*p && !isdigit((unsigned char)*p))
            p++;

        if (!*p) {
            printf("Informe linha e coluna. Exemplo: 5 8.\n");
            continue;
        }

        segundo = strtol(p, &fim, 10);

        if (primeiro < 1 || primeiro > tamanho ||
            segundo < 1 || segundo > tamanho) {
            printf("Valores devem estar entre 1 e %d.\n",
                   tamanho);
            continue;
        }

        *a = (int)primeiro;
        *b = (int)segundo;

        return 1;
    }
}

/* Confere se as coordenadas formam a palavra */

int conferirPalavra(int l1, int c1, int l2, int c2,
                    char palavra[]) {
    int deltaL, deltaC, passoL, passoC;
    int i, n = strlen(palavra);

    if (l1 < 0 || l1 >= tamanho ||
        l2 < 0 || l2 >= tamanho ||
        c1 < 0 || c1 >= tamanho ||
        c2 < 0 || c2 >= tamanho)
        return 0;

    deltaL = l2 - l1;
    deltaC = c2 - c1;

    /* Verifica se a selecao e reta */
    if (deltaL != 0 && deltaC != 0 &&
        abs(deltaL) != abs(deltaC))
        return 0;

    /* Verifica se a distancia corresponde a palavra */
    if (abs(deltaL) != 0 && abs(deltaL) != n - 1)
        return 0;

    if (abs(deltaC) != 0 && abs(deltaC) != n - 1)
        return 0;

    if (deltaL == 0 && deltaC == 0)
        return 0;

    passoL = (deltaL > 0) - (deltaL < 0);
    passoC = (deltaC > 0) - (deltaC < 0);

    /* Testa a palavra no sentido informado */
    for (i = 0; i < n; i++) {
        if (grade[l1 + i * passoL]
                 [c1 + i * passoC] != palavra[i])
            break;
    }

    if (i == n)
        return 1;

    /* Testa a palavra no sentido contrario */
    for (i = 0; i < n; i++) {
        if (grade[l1 - i * passoL]
                 [c1 - i * passoC] != palavra[i])
            return 0;
    }

    return 1;
}


/* Controla o jogo */
int jogar(void) {
    char tentativa[WORD_LEN];
    int l1, c1, l2, c2;
    int i, indice, pontos = 0;

    while (pontos < totalPalavras) {
        mostrarGrade();
        mostrarPalavras();

        printf("\nDigite a palavra encontrada (FIM para sair): ");

        if (scanf("%23s", tentativa) != 1)
            return 0;

        /* Limpa o restante da linha do teclado */
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
        }

        maiusculo(tentativa);

        if (strcmp(tentativa, "FIM") == 0)
            break;

        indice = -1;

        for (i = 0; i < totalPalavras; i++) {
            if (strcmp(tentativa, palavras[i]) == 0) {
                indice = i;
                break;
            }
        }

        if (indice == -1) {
            printf("Essa palavra nao esta na lista!\n");
            continue;
        }

        if (encontradas[indice]) {
            printf("Voce ja encontrou essa palavra!\n");
            continue;
        }

        if (!lerPar(&l1, &c1, "Linha e coluna INICIAL: "))
            return 0;

        if (!lerPar(&l2, &c2, "Linha e coluna FINAL: "))
            return 0;

        /* Converter coordenadas para indices da matriz */
        l1--; c1--; l2--; c2--;

        if (conferirPalavra(l1, c1, l2, c2, tentativa) ||
            conferirPalavra(l2, c2, l1, c1, tentativa)) {
            encontradas[indice] = 1;
            pontos++;

            printf("Correto! Você encontrou %s!\n", tentativa);
        } else {
            printf("Coordenadas incorretas. Tente novamente!\n");
        }
    }

    printf("\nPontuação: %d de %d\n", pontos, totalPalavras);

    if (pontos == totalPalavras) {
        printf("Parabéns! Voce completou o nível!\n");
        return 1;
    }

    return 0;
}

/* Programa principal */
int main(void) {
    const char *facil[] = {
        "CPU", "RAM", "KERNEL", "SISTEMA"
    };

    const char *medio[] = {
        "PROCESSO", "MEMORIA", "ARQUIVO",
        "DRIVER", "NUCLEO", "USUARIO"
    };

    const char *dificil[] = {
        "ESCALONAMENTO", "PROCESSADOR", "SEGURANCA",
        "MULTITAREFA", "MEMORIA", "ARQUIVO", "PROCESSO"
    };

    const char **listaNivel;
    int nivel, i, rodada, sucesso;

    srand((unsigned int)time(NULL));

    printf("====================================\n");
    printf(" CACA-PALAVRAS - SISTEMAS OPERACIONAIS\n");
    printf("====================================\n");
    printf("Voce jogara os tres niveis em sequencia!\n");

    for (nivel = 1; nivel <= 3; nivel++) {
        sucesso = 0;

        if (nivel == 1) {
            tamanho = 8;
            totalPalavras = 4;
            listaNivel = facil;
            printf("\n====================================\n");
            printf(" NIVEL 1 - FACIL\n");
            printf("====================================\n");
        } else if (nivel == 2) {
            tamanho = 12;
            totalPalavras = 6;
            listaNivel = medio;
            printf("\n====================================\n");
            printf(" NIVEL 2 - MEDIO\n");
            printf("====================================\n");
        } else {
            tamanho = 15;
            totalPalavras = 7;
            listaNivel = dificil;
            printf("\n====================================\n");
            printf(" NIVEL 3 - DIFICIL\n");
            printf("====================================\n");
        }

        for (i = 0; i < totalPalavras; i++) {
            strcpy(palavras[i], listaNivel[i]);
            encontradas[i] = 0;
        }

        /* Gera novamente a grade se alguma palavra nao couber */
        for (rodada = 0; rodada < 100; rodada++) {
            inicializarGrade();

            for (i = 0; i < totalPalavras; i++) {
                if (!inserirPalavra(palavras[i]))
                    break;
            }

            if (i == totalPalavras) {
                sucesso = 1;
                break;
            }
        }

        if (!sucesso) {
            printf("Nao foi possivel montar a grade do nivel %d.\n", nivel);
            return 1;
        }

        completarGrade();

        printf("\n--- TEXTO DE APOIO ---\n");

        if (nivel == 1) {
            printf("O SISTEMA operacional gerencia o computador. "
                   "O KERNEL controla recursos importantes. "
                   "A CPU processa instrucoes e a RAM guarda "
                   "dados temporarios.\n");
        } else if (nivel == 2) {
            printf("O USUARIO utiliza o sistema operacional para "
                   "executar cada PROCESSO. A MEMORIA guarda dados, "
                   "o ARQUIVO organiza informacoes, o DRIVER permite "
                   "a comunicacao com dispositivos e o NUCLEO coordena "
                   "as operacoes.\n");
        } else {
            printf("O ESCALONAMENTO organiza os processos para o "
                   "PROCESSADOR. A MULTITAREFA permite executar "
                   "varias atividades. A MEMORIA armazena dados, "
                   "o ARQUIVO guarda informacoes e a SEGURANCA "
                   "ajuda a proteger o sistema.\n");
        }

        if (!jogar()) {
            printf("\nVoce saiu do jogo antes de concluir os tres niveis.\n");
            return 0;
        }

        if (nivel < 3) {
            printf("\nMuito bem! Preparando o proximo nivel...\n");
        }
    }

    printf("\n");
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*      PARABÉNS, VOCÊ É FERA!          *\n");
    printf("*                                      *\n");
    printf("* Voce completou os tres niveis!       *\n");
    printf("****************************************\n");

    return 0;
}
