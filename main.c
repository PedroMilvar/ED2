#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <string.h>

int main(int argc, char *argv[]){
    ArvAVL *avl, *avlc;
    int res,j=0, cont=1, palavras=0;

    char vetaux[100];
    opentxt(argv[1], vetaux);
    printf("%s", vetaux);
    
    avl = cria_ArvAVL();
    avlc = cria_ArvAVL();

    char poema[100] = {"Os sois e as luas\nCreio bem que Deus os fez\nPara outras vidas\n"}; 
    char teste[100];

    for(int i=0; poema[i] != '\0'; i++){
        if(poema[i] == ' ' || poema[i] == '\n'); palavras++;
        while(poema[i] != ' ' && poema[i] != '\n'){
            teste[j] = poema[i];

            
        i++;
        j++;
    }

    if(poema[i] == '\n')
        cont++;

    insere_ArvAVL(avl, teste, cont);
    cont=1;
}
    printf("------------------\n");
    printf("Indice:\n");
    emOrdem_ArvAVL(avl);
    printf("Numero total de palavras: %d\n", palavras);//número total de palavras

    char aux[50];
    char *n;
    j=0;
    for(int i=0;i<100;i++){
        while(poema[i]!= ' ' && poema[i]!= '\n'){
            aux[j] = poema[i];
            i++;
            j++;
        }
        aux[j] = '\0';
        n = strstr(aux,poema);
        if(n!= NULL){
            palavras--;
        }
        j=0;
        
    }
    printf("Numero de palavras distintas: %d\n", palavras);//palavras distintas

    char aux2[100];
     for(int i=0;i<100;i++){
        while(poema[i]!= ' ' && poema[i]!= '\n'){
            aux2[j] = poema[i];
            i++;
            j++;
        }
        aux2[j] = '\0';
        n = strstr(aux2,poema);
        if(n!= NULL){
            palavras--;
        }
        j=0;
        
    }
    libera_ArvAVL(avl);
    return 0;
}
