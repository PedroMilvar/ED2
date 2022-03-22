#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "arvore.h" //inclui os Protótipos

struct NO{
    char palavra[100];
    int linha[100];
    int altura;
    struct NO *esq;
    struct NO *dir;
};

void opentxt(char *arquivo, char *vetaux){
        FILE *fp = fopen(arquivo, "r");
        if(fp == NULL){
            return ;
        }
        char c;
        int i=0;
        c = fgetc(fp);
        while(c != EOF){
            vetaux[i] = c;
            c = fgetc(fp);
            i++;
        }
}

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc (sizeof(ArvAVL));
    /*for(int i=0;i<100;i++){
        (*raiz)->linha[i] = 0;
    }*/
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}


int consulta_ArvAVL(ArvAVL *raiz, char* palavra){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(strcmp(palavra,atual->palavra) == 0){
            return 1;
        }
        if(strcmp(palavra,atual->palavra) > 0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

//=================================
int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

void RotacaoDireita(ArvAVL *A){//LL
    printf("\nRotacao Direita");
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoEsquerda(ArvAVL *A){//RR
    printf("\nRotacao Esquerda");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoDuplaDireita(ArvAVL *A){//LR
    printf("\nRotacao Dupla Direita");
    RotacaoEsquerda(&(*A)->esq);
    RotacaoDireita(A);
}

void RotacaoDuplaEsquerda(ArvAVL *A){//RL
    printf("\nRotacao Dupla Esquerda");
    RotacaoDireita(&(*A)->dir);
    RotacaoEsquerda(A);
}


int insere_ArvAVL(ArvAVL *raiz, char* palavra, int linha){
    int r;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        strcpy(novo->palavra, palavra);
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->linha[linha] = 1;
        *raiz = novo;
        return 1;
    }
    struct NO *atual = *raiz;
    if(strcmp(palavra, atual->palavra) < 0){
        r = insere_ArvAVL(&(atual->esq), palavra, linha);
        if(r == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(strcmp(palavra, (*raiz)->esq->palavra) < 0){
                    RotacaoDireita(raiz);
                }else{
                    RotacaoDuplaDireita(raiz);
                }
            }
        }
    }else{
        if(strcmp(palavra,atual->palavra) > 0){
            r = insere_ArvAVL(&(atual->dir), palavra, linha); 
            if(r == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if(strcmp((*raiz)->dir->palavra, palavra) < 0){
                        RotacaoEsquerda(raiz);
                    }else{
                        RotacaoDuplaEsquerda(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }
    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return r;
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL){
        printf("RAIZ NULL");
        return;
    }
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("%s ", (*raiz)->palavra);
        for(int i=0; i<100; i++){
            if((*raiz)->linha[i] == 1){
                printf("%d ", i);
            }
        }
        printf("\n");
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}
 
