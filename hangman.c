#include <stdio.h>
#include <string.h>
#include <locale.h>

void cabecalho() { //Criando a funcao cabecalho usando void 
    printf("\n***************************************");
    printf("\n***          JOGO DA FORCA          ***");
    printf("\n***************************************\n");

    printf("\n");  
}

void chuta(char possibilidades[26], int * tentativas){
    char chute; 
    scanf("%c", &chute);

    possibilidades[(*tentativas)] = chute; 
    (*tentativas)++; //tentativas deve se direcionar ao valor da variavel definida fora desta função assim ao inves de apenas ao endereço
}

void palavraescolhida(char palavrasecreta[20]){
    sprintf(palavrasecreta, "MELANCIA"); //s - de string , strigprintf, "%s" representa o sprintf o \0 atalho para 0 que serve para indicar que uma string acaba - igual o sprintf faz 
}

int main() { //Função principal
    setlocale(LC_ALL, "Portuguese");

    //VARIAVEIS - Nao definida como global para nao alterar as mesmas
    char palavrasecreta [20]; 

    int acertou = 0; 
    int enforcou = 0; 

    char possibilidades[26];
    int tentativas = 0; 

    palavraescolhida(palavrasecreta);//chamada da função
    cabecalho(); //chamando a funcao, caso nao insira a funcao nao sera executada

    do {
    //inicio do jogo 


        for(int i=0; i < strlen(palavrasecreta); i++){ //strlen - usado para medir o tamanho de um array

            int letracorreta = 0; //variavel para encontrar a letra correta e verificar se equivale


            for(int j=0; j < tentativas; j++){

                if(possibilidades[j] == palavrasecreta[i]){

                    letracorreta = 1; 
                    break;
                }
            }
            
            if(letracorreta) {
                printf("%c", palavrasecreta[i]);
            } else {
                printf("_ ");
            }
        } 
        printf("\n");

        chuta(possibilidades, &tentativas); //Variavel tentativas usa o & para direcionar ao endereco de memoria

        } while(!acertou && !enforcou);
}
