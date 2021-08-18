#include<stdio.h>
#include <stdlib.h>

#define TAM 10

int* insere_vetor(int *vetor_num, int num, int *qtd_elem, int *tam);
int* overflow(int *vetor_num, int *tam, int qtd_elem);
void merge_sort(int *vetor_num, int inicio, int fim);
void merge(int *vetor_num, int inicio, int meio, int fim);

int main(void){

    int num, qtd_elem=0;
    int *vetor_num, tam;
    int i;

    tam = TAM;
    vetor_num = (int*) malloc(tam * sizeof(int));

    scanf("%d", &num);
    while(!feof(stdin)){ /*Lê todos os números e os insere no vetor vetor_num*/
        vetor_num = insere_vetor(vetor_num, num, &qtd_elem, &tam);
        scanf("%d", &num);
    }

    merge_sort(vetor_num, 0, qtd_elem); /*Ordenada a lista utilizando merge sort*/

    for(i=0; i < qtd_elem; i++){  /*Imprime o resultado linha a linha*/
        printf("%d\n", vetor_num[i]);
    }

    return 0;
}

/* Função que insere no vetor "vetor_num" o elemento "num".
*/

int* insere_vetor(int *vetor_num, int num, int *qtd_elem, int *tam){
    
    if (*qtd_elem == *tam){ /*Realiza o aumento do vetor para que não ocorra overflow*/
        vetor_num = overflow(vetor_num, tam, *qtd_elem);
    }
    if (*qtd_elem < *tam){
        vetor_num[*qtd_elem] = num;
        (*qtd_elem)++;
    }
    return vetor_num;
}

/* Aumenta o tamanho do vetor para que não ocorra overflow
*/
int* overflow(int *vetor_num, int *tam, int qtd_elem){
    int i;
    int *temp;

    temp = (int*) malloc(2*(*tam)*sizeof(int));

    for(i=0; i < qtd_elem; i++){
        temp[i] = vetor_num[i];
    }
    free(vetor_num);
    vetor_num = temp;
    (*tam) *= 2;
    return vetor_num;
}

/*Realiza o merge sort através das duas funções abaixo
*/
void merge_sort(int *vetor_num, int inicio, int fim){
    int meio;
    if(fim - inicio > 1){
        meio = (inicio + fim)/2;
        merge_sort(vetor_num, inicio, meio);
        merge_sort(vetor_num, meio, fim);
        merge(vetor_num, inicio, meio, fim);
    }
}

void merge(int *vetor_num, int inicio, int meio, int fim){
    int i, j, *temp, pos;
    i = inicio;
    j = meio;
    pos = 0;

    temp = malloc((fim-inicio) * sizeof(int));
    

    while(i < meio && j < fim){
        if(vetor_num[i] <= vetor_num[j]){
            temp[pos] = vetor_num[i];
            i++;  
        }
        else{
            temp[pos] = vetor_num[j];
            j++;
        }
        pos++;
    }

    while(i < meio){
        temp[pos] = vetor_num[i];
        i++;
        pos++;
    }

    while(j < fim){
        temp[pos] = vetor_num[j];
        j++;
        pos++;
    }

    for(i=0; i < pos; i++){
        vetor_num[inicio+i] = temp[i]; 
    }   
    free(temp);
}