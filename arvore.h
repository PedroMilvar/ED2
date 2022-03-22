typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
void opentxt(char *arquivo, char *vetaux);
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, char* palavra, int linha);
int estaVazia_ArvAVL(ArvAVL *raiz);
void emOrdem_ArvAVL(ArvAVL *raiz);

