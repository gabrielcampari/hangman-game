#include <stdio.h>
#include <string.h>

int main() {

char palavrasecreta [20]; 

sprintf(palavrasecreta, "MELANCIA"); //s - de string , strigprintf, "%s" representa o sprintf o \0 atalho para 0 que serve para indicar que uma string acaba - igual o sprintf faz 

int acertou = 0; 
int enforcou = 0; 

do {
    char chute;  //inicio do jogo 
    scanf("%c", &chute);

    for(int i=0; i < strlen(palavrasecreta); i++){ //strlen - usado para medir o tamanho de um array
        if(palavrasecreta[i] == chute){
            printf("\nA posicao %d tem essa letra!", i); 
        }
    } 

} while(!acertou && !enforcou);
}
