#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include "functions.h"

// VARIAVEIS GLOBAIS
char palavrasecreta[TAMANHO_PALAVRA];
char possibilidades[26];
int tentou = 0;

void cabecalho() {
    printf("\n***************************************");
    printf("\n***          JOGO DA FORCA          ***");
    printf("\n***************************************\n\n");
}

void chuta() {
    char chute;
    printf("Qual letra deseja tentar? \n");
    scanf(" %c", &chute);

    possibilidades[tentou] = chute;
    tentou++;
}

void palavraescolhida(char palavra[]) {
    FILE *f;
    f = fopen("C:/Users/USER/OneDrive/Documentos/Arquivos de programas/C/Alura/hangman-game/words.txt", "r"); //Dentro dos parenteses enderece o caminho do arquivo txt em sua maquina. 
    //Ao apenas inserir o nome do arquivo txt pode ocorrer um erro ao localizar, busque copiar o caminho do arquivo e susbstituir. 

    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        printf("Certifique-se de que o arquivo 'words.txt' está no diretório correto.\n");
        exit(1);
    }

    int quantidadeDePalavras;
    if (fscanf(f, "%d", &quantidadeDePalavras) != 1 || quantidadeDePalavras == 0) {
        printf("Erro ao ler a quantidade de palavras do banco de dados!\n\n");
        fclose(f);
        exit(1);
    }

    srand(time(NULL));
    int random = rand() % quantidadeDePalavras;

    for (int i = 0; i < random; i++) {
        if (fscanf(f, "%19s", palavra) != 1) { //Depois de buscar um numero no inicio ele guia para ler as strings do txt assim indo em ordem e O 19 limita a leitura para evitar overflow
            printf("Erro ao ler a palavra do banco de dados!\n\n");
            fclose(f);  //Fechar o arquivo para reservar para essa funcao (evita que outras usem esse arquivo e ate o altere)
            exit(1);
        }
    }

    fclose(f);
}

void adicionaPalavra(){

    char adiciona;

    printf("\nVocê deseja adicionar uma nova palavra ao jogo? (S/N)");
    scanf(" %c", &adiciona);

    if(adiciona == 'S' ){
        
        char novaPalavra[TAMANHO_PALAVRA]; 
        printf("\nQual a palavra que deseja inserir?");
        scanf("%s", novaPalavra);

        FILE *f;
        f = fopen("C:/Users/USER/OneDrive/Documentos/Arquivos de programas/C/Alura/hangman-game/words.txt", "r+"); //"r+" serve para permissao e escrita

        int numeroDePalavras; 

        fscanf(f, "%d", &numeroDePalavras);
        numeroDePalavras++;

        fseek(f, 0, SEEK_SET);//Posiciona a leitura para a direcao que desejar assim ficando correta, por inserir 0 voce aponta para o comeco do arquivo
        fprintf(f, "%d", numeroDePalavras);

        fseek(f, 0, SEEK_END);//Posiciona a seta no final do arquivo "end" assim o fechando apos adicionar a nova palavra
        fprintf(f, "\n%s", novaPalavra);

        fclose(f); 
    }
}

int chuteDado(char letra) {
    int achou = 0;

    for (int j = 0; j < tentou; j++) {
        if (possibilidades[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void forca() {

    int erros = chutesErrados(); 

    printf("      _______        \n"  );
	printf("     |/      |       \n"  );
    printf("     |      %c%c%c   \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' ') );
	printf("     |      %c%c%c   \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
	printf("     |       %c      \n", (erros >= 2 ? '|' : ' '));
	printf("     |      %c %c    \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
	printf("     |               \n"  );
	printf("    _|___            \n"  );
    printf("\n\n"); 

    for (int i = 0; i < strlen(palavrasecreta); i++) {  //strlen - usado para medir o tamanho de um array
        
        int achou = chuteDado(palavrasecreta[i]);

        if (chuteDado(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int acertou() {
    for (int i = 0; i < strlen(palavrasecreta); i++) {
        if (!chuteDado(palavrasecreta[i])) {
            return 0;
        }
    }
    return 1;
}

int chutesErrados(){

    int erros = 0;

    for (int i = 0; i < tentou; i++) {
        int existe = 0;

        for (int j = 0; j < strlen(palavrasecreta); j++) {
            if (possibilidades[i] == palavrasecreta[j]) {
                existe = 1;
                break;
            }
        }

        if (!existe)erros++;
    }

    return erros; 
}

int enforcou() {

    return chutesErrados() >= 5;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    palavraescolhida(palavrasecreta);
    cabecalho();

    do {
        //inicio e loop do jogo 
        forca();
        chuta();
    } while (!acertou() && !enforcou());
    
    if(acertou()){
            printf("\nParabéns, você ganhou!\n\n");

			printf("  '._==_==_=_.'\n"  );
			printf("  .-\\:      /-.\n"  );
			printf(" | (|:.     |) |\n");
			printf("  '-|:.     |-'\n"    );
			printf("    \\::.    /\n"  );
			printf("     '::. .'\n"  );
			printf("       ) (\n"    );
			printf("     _.' '._\n"    );
			printf("    '*******'        \n");
    }else{
        printf("Puxa, você foi enforcado! A palavra era **%s** \n\n", palavrasecreta);

        printf("                 uuuuuuu\n");
        printf("             uu$$$$$$$$$$$uu\n");
        printf("          uu$$$$$$$$$$$$$$$$$uu\n");
        printf("         u$$$$$$$$$$$$$$$$$$$$$u\n");
        printf("        u$$$$$$$$$$$$$$$$$$$$$$$u\n");
        printf("       u$$$$$$$$$$$$$$$$$$$$$$$$$u\n");
        printf("       u$$$$$$$$$$$$$$$$$$$$$$$$$u\n");
        printf("       u$$$$$$\"   \"$$$\"   \"$$$$$$u\n");
        printf("       \"$$$$\"      u$u       $$$$\"\n");
        printf("        $$$u       u$u       u$$$\n");
        printf("        $$$u      u$$$u      u$$$\n");
        printf("         \"$$$$uu$$$   $$$uu$$$$\"\n");
        printf("          \"$$$$$$$\"   \"$$$$$$$\"\n");
        printf("            u$$$$$$$u$$$$$$$u\n");
        printf("             u$\"$\"$\"$\"$\"$\"$u\n");
        printf("  uuu        $$u$ $ $ $ $u$$       uuu\n");
        printf(" u$$$$        $$$$$u$u$u$$$       u$$$$\n");
        printf("  $$$$$uu      \"$$$$$$$$$\"     uu$$$$$$\n");
        printf("u$$$$$$$$$$$uu    \"\"\"\"\"    uuuu$$$$$$$$$$\n");
        printf("$$$$\"\"\"$$$$$$$$$$uuu   uu$$$$$$$$$\"\"\"$$$\n");
        printf("\"\"\"      \"\"$$$$$$$$$$$uu \"\"$$$$$$$\n");
        printf("           uuuu \"\"$$$$$$$$$$uuu\n");
        printf("  u$$$uuu$$$$$$$$$uu \"\"$$$$$$$$$$$uuu$$$\n");
        printf("  $$$$$$$$$$\"\"\"           \"\"$$$$$$$$$$$\"\n");
        printf("   \"$$$$$\"                      \"\"$$$$\"\"\n");
        printf("     $$$\"                         $$$$\"\n");

    }

    adicionaPalavra(); 

    return 0;
}