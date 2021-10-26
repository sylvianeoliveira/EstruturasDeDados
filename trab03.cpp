#include <stdio.h>
#include <stdlib.h>

typedef struct _tno{
    int chave;
    int alt;
    int reg;
    struct _tno *esq;
    struct  _tno *dir;
} tno;

void insere(tno **pt_raiz, int x);
void imprime_pre_ordem(tno **pt_raiz);
void rotacao_simp_esq(tno **pt_raiz);
void rotacao_simp_dir(tno **pt_raiz);
void rotacao_dup_esq(tno **pt_raiz);
void rotacao_dup_dir(tno **pt_raiz);
int MAX(int a, int b);
int ALTURA(tno **ponteiro);

int main(void){

    int num = 0;
    char string[5];
    tno *pt_raiz;

    pt_raiz = NULL;

    while(!feof(stdin)){
        if(scanf("%s", string) == 1){
            if(string[0] == 'p'){
                imprime_pre_ordem(&pt_raiz);
                printf("\n");
            }
            if(string[0] == 'i'){
                if(scanf("%d", &num) == 1){
                    insere(&pt_raiz, num);
                }
            }
        }
    }
    return 0;
}
/*Função que calcula e retorna o máximo entre dois números inteiros*/
int MAX(int a, int b){
    if(a > b) return a;
    else return b;
}

/*Função que calcula e retorna a altura de um nó apontado pelo ponteiro. Caso o ponteiro seja nulo, retorna 0*/
int ALTURA(tno **ponteiro){
    if((*ponteiro) != NULL){
        return ((*ponteiro)->alt);
    }
    else{
        return 0;
    }
}

/*Rotação simples para a esquerda em uma árvore AVL*/
void rotacao_simp_esq(tno **pt_raiz){
    tno *pt;
    pt = (*pt_raiz)->dir;
    (*pt_raiz)->dir = pt->esq;
    pt->esq = (*pt_raiz);

    pt->alt = (*pt_raiz)->alt;
    (*pt_raiz)->alt = pt->alt - 1;

    (*pt_raiz) = pt;
}

/*Rotação simples para a direita em uma árvore AVL*/
void rotacao_simp_dir(tno **pt_raiz){
    tno *pt;
    pt = (*pt_raiz)->esq;
    (*pt_raiz)->esq = pt->dir;
    pt->dir = (*pt_raiz);

    pt->alt = (*pt_raiz)->alt;
    (*pt_raiz)->alt = pt->alt - 1;

    (*pt_raiz) = pt;
}

/*Rotação dupla para a esquerda em uma árvore AVL*/
void rotacao_dup_esq(tno **pt_raiz){
    rotacao_simp_dir(&(*pt_raiz)->dir);
    rotacao_simp_esq(&(*pt_raiz));
}

/*Rotação dupla para a direita em uma árvore AVL*/
void rotacao_dup_dir(tno **pt_raiz){
    rotacao_simp_esq(&(*pt_raiz)->esq);
    rotacao_simp_dir(&(*pt_raiz));
}

/*Função que insere um número em uma árvore AVL*/
void insere(tno **pt_raiz, int x){
    if((*pt_raiz) == NULL){ /*Cria o nó*/
        (*pt_raiz) = (tno*) malloc(sizeof (tno));
        if((*pt_raiz) != NULL){
            (*pt_raiz)->chave = x;
            (*pt_raiz)->alt = 1;
            (*pt_raiz)->esq = (*pt_raiz)->dir = NULL;
        }
    }
    else if (x < (*pt_raiz)->chave){ /*Chama recursivamente a função insere para o lado esquerdo*/
        //printf("esq\n");
        insere(&(*pt_raiz)->esq, x);
    }
    else{ /*Chama recursivamente a função insere para o lado direito*/
        insere(&(*pt_raiz)->dir, x);
    }

    (*pt_raiz)->reg = ALTURA(&(*pt_raiz)->esq) - ALTURA(&(*pt_raiz)->dir); /*Calcula a regulagem de um nó*/

    if ((*pt_raiz)->reg == 2){ /*Se a árvore da esquerda for maior*/
        if(((*pt_raiz)->esq)->reg == 1){ /*Se a árvore do nó desregulado estiver para a esquerda*/
            rotacao_simp_dir(&(*pt_raiz));
        }
        else if(((*pt_raiz)->esq)->reg == -1){ /*Se a árvore do nó desregulado estiver para a direita*/
            rotacao_dup_dir(&(*pt_raiz));
        }
    }
    else if((*pt_raiz)->reg == -2){ /*Se a árvore da direita for maior*/
        if((((*pt_raiz)->dir)->reg == 1)){ /*Se a árvore do nó desregulado estiver para a esquerda*/
            rotacao_dup_esq(&(*pt_raiz));
        }
        else if(((*pt_raiz)->dir)->reg == -1){ /*Se a árvore do nó desregulado estiver para a direita*/
            rotacao_simp_esq(&(*pt_raiz));
        }
    }
    else{ /*Se não está desregulado, calcula a altura novamente após a inserção*/
        (*pt_raiz)->alt = MAX(ALTURA(&(*pt_raiz)->esq), ALTURA(&(*pt_raiz)->dir)) + 1;
    }
}

/*Imprime a árvore e a altura de cada nó em pré-ordem por recursão*/
void imprime_pre_ordem(tno **pt_raiz){
    if((*pt_raiz) != NULL){
        printf("%d(%d) ", (*pt_raiz)->chave, (*pt_raiz)->alt);
        imprime_pre_ordem(&(*pt_raiz)->esq);
        imprime_pre_ordem(&(*pt_raiz)->dir);
    }
}