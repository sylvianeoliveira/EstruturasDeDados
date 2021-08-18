#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _tno{
    int chave;
    struct _tno *prox;
} tno;

void insere(tno** ptlista, int x);

int main(){
    int i, pos;
    int *grau_ver, *ordem;
    char *linha = NULL;
    size_t tamLinha = 0;
    int vertices, arestas;
    tno **adj;

    /*Leitura da quantidade vértices e arestas*/
    scanf("%d %d\n", &vertices, &arestas);

    adj = (tno**) malloc((vertices+1)*(sizeof(tno*)));
    grau_ver = (int*) malloc((vertices+1)*(sizeof(int)));
    ordem = (int*) malloc((vertices+1)*(sizeof(int)));

    for(int i = 1; i <= vertices; i++){
        /*Inicializações*/
        adj[i] = NULL;
        grau_ver[i] = 0;
        ordem[i]  = 0;
    }

    for(int i = 1; i <= vertices; i++){
        /*Leitura das inforações*/
        getline(&linha,&tamLinha,stdin);
        int pos = 0;
        int numLido = 0;
        int numChars;

        while (sscanf(&linha[pos], " %d %n", &numLido, &numChars) > 0) {
            pos += numChars;
            if(strlen(linha) != 0){
                insere(&adj[i], numLido); /*Insere no vetor adj, na posição i, o número lido*/
                grau_ver[numLido]++;    /*Identifica os graus de vértices*/
            }
        }
    }

    pos=1;

    /*Adiciona os vértices com grau zero no vetor ordem*/
    for(i=1; i <= vertices; i++){
        if (grau_ver[i] == 0){
            ordem[pos] = i;
            pos++;
        }

    }

    /*Diminui um grau dos vértices dependentes dos vértices indicados no vetor ordem*/
    for(i=1; i <= vertices; i++){
        tno *pt;
        pt = adj[ordem[i]];
        /*Percorre a lista*/
        while(pt != NULL){
            grau_ver[pt->chave]--;
            if(grau_ver[pt->chave] == 0){
                ordem[pos] = pt->chave;
                pos++;
            }
            pt = pt->prox;
        }
    }
    /*Imprime o vetor ordem com a ordeneção topológica e libera as posições de memória alocadas para adj[i]*/
    for(i=1; i <= vertices; i++){
        printf("%d ", ordem[i]);
        tno *pt = adj[i];
        while(pt != NULL){
            pt = pt->prox;
            free(adj[i]);
            adj[i] = pt;
        }
    }

    free(grau_ver);
    free(ordem);
    free(adj);
    return 0;
}

/*Função que insere elementos em uma lista encadeana*/
void insere(tno** ptlista, int x){
    tno *novo;
    novo = (tno*) malloc(sizeof(tno));
    if (novo != NULL){
        novo->chave = x;
        novo->prox = (*ptlista);
        (*ptlista) = novo;
    }
}