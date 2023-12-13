#include <stdio.h>
#include <string.h>

int main() {

char palavrasecreta [20]; 

sprintf(palavrasecreta, "MELANCIA"); //s - de string , strigprintf, "%s" representa o sprintf o \0 atalho para 0 que serve para indicar que uma string acaba - igual o sprintf faz 

int acertou = 0; 
int enforcou = 0; 

char possibilidades[26];
int tentativas = 0; 

do {
//inicio do jogo 


    for(int i=0; i < strlen(palavrasecreta); i++){ //strlen - usado para medir o tamanho de um array
        for(int j=0; j < tentativas; j++){
            if(possibilidades[j] == palavrasecreta[i]){
                printf("%c ");
                break;
            }
        }
        printf("_ ");
    } 
    printf("\n");

    char chute; 
    scanf("%c", &chute);

    possibilidades[tentativas] = chute; 
    tentativas++;

    } while(!acertou && !enforcou);
}
