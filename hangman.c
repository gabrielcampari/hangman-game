#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "functions.h"

//VARIAVEIS GLOBAIS
char palavrasecreta [20]; 
char possibilidades[26];
int tentou = 0;

void cabecalho() { //Criando a funcao cabecalho usando void 
    printf("\n***************************************");
    printf("\n***          JOGO DA FORCA          ***");
    printf("\n***************************************\n");

    printf("\n");  
}

void chuta(){
    char chute; 
    printf("Qual letra deseja tentar? \n");
    scanf(" %c", &chute);

    possibilidades[tentou] = chute; 
    tentou++; 
}

void palavraescolhida(){
    sprintf(palavrasecreta, "MELANCIA"); //s - de string , strigprintf, "%s" representa o sprintf o \0 atalho para 0 que serve para indicar que uma string acaba - igual o sprintf faz 
}

int chuteDado(char letra){ 

    int achou = 0; 

        for(int j = 0; j < tentou; j++){

            if(possibilidades[j] == letra) {
                achou = 1; 
                break; 
            }
        }

        return achou; 
}

void forca(){
    
    //printf("Você já deu %d chutes! \n", tentativas); 

        for(int i = 0; i < strlen(palavrasecreta); i++){ //strlen - usado para medir o tamanho de um array

            int letracorreta = 0; 
            
            if(chuteDado(palavrasecreta[i])) {
                printf("%c ", palavrasecreta[i]);
            } else {
                printf("_ ");
            }

        } 
        printf("\n");
}

int acertou(){
    for(int i = 0; i < strlen(palavrasecreta); i++){
        if(!chuteDado(palavrasecreta[i])){
            return 0; 
        }
    }

    return 1; 

}

int enforcou(){

    int erros = 0; 

    for(int i = 0; i < tentou; i++){

        int existe = 0; 

        for(int j = 0; j < strlen(palavrasecreta); j++){

            if(possibilidades[i] == palavrasecreta[j]){

                    existe = 1; 
                    break;
                }
        }

        if(!existe) erros++; 
    }

    return erros >= 5;
}

int main() { //Função principal
    setlocale(LC_ALL, "Portuguese"); 

    palavraescolhida();//chamada da função
    cabecalho(); //chamando a funcao, caso nao insira a funcao nao sera executada

    do {
    //inicio e loop do jogo 

        forca(); 
        chuta(); 

        } while(!acertou() && !enforcou());
}
