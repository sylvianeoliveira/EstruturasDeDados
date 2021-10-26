#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _Ponto{
    // coordenadas do ponto que representa a cidade
    int x;
    int y;
    int nome;
}Ponto;

typedef struct _Aresta{
    double distancia;
    int ponto1;
    int ponto2;
}Aresta;

double calc_dist_ponto(Ponto ponto1, Ponto ponto2);
void merge_sort(Aresta **vetor_arestas, int inicio, int fim);
void merge(Aresta **vetor_arestas, int inicio, int meio, int fim);
void une(int **conj, int **tam, int a, int b);
int find(int **conj, int x);

int main(void){

    int qtd_teste, qtd_cidade, qtd_arestas, qtd_estados, r, i, j, k, cont;
    int *conj, *tam;
    double estrada, ferrovia;

    Ponto *vect_pontos;
    Aresta *dist_cidades;

    scanf("%d", &qtd_teste);             // Quantidade de testes

    for(i=0; i < qtd_teste; i++){       // Para cada teste...
        scanf("%d %d", &qtd_cidade, &r); // Lê a quantidade de cidades e a constante r

        qtd_estados = 1;
        estrada = 0;
        ferrovia = 0;
        qtd_arestas = (qtd_cidade * (qtd_cidade - 1)) / 2; // Quantidade de arestas em um grafo completo

        vect_pontos = (Ponto*) malloc(qtd_cidade * sizeof(Ponto));      // Inicializa o vetor de pontos;
        dist_cidades = (Aresta*) malloc( qtd_arestas * sizeof(Aresta)); // Inicializa o vetor de arestas;
        conj = (int*) malloc(qtd_cidade * sizeof(int));                 // Inicializa o vetor conj;
        tam = (int*) malloc(qtd_cidade * sizeof(int));                  // Inicializa o vetor tam;

        for(j=0; j< qtd_cidade; j++){                                   // Para cada cidade...
            scanf("%d %d", &vect_pontos[j].x, &vect_pontos[j].y);
            vect_pontos[j].nome = j;                                    // Lendo as coordenadas da cidade

            conj[j] = j;                                                // Valor inicial de conj
            tam[j] = 1;                                                 // Valor inicial de tam
        }
        cont = 0;
        for(j=0; j < qtd_cidade; j++){ //Calcular cada distância e alocar no vetor de arestas
            for(k=j+1; k < qtd_cidade; k++){
                dist_cidades[cont].ponto1 = vect_pontos[j].nome;
                dist_cidades[cont].ponto2 = vect_pontos[k].nome;
                dist_cidades[cont].distancia = calc_dist_ponto(vect_pontos[j], vect_pontos[k]);
                cont++;
            }
        }

        // Para determinar a árvore geradora mínima, é preciso ordenar as distancias

        merge_sort(&dist_cidades, 0, qtd_arestas); /*Ordenada o vetor dist_cidades merge sort*/

        for(j=0; j < qtd_arestas; j++){
            //verifica se a aresta está em conjuntos diferentes
            int x1 = find(&conj, dist_cidades[j].ponto1);
            int x2 = find(&conj, dist_cidades[j].ponto2);
            double distancia;
            if(x1 != x2){
                une(&conj, &tam, dist_cidades[j].ponto1, dist_cidades[j].ponto2);
                distancia = dist_cidades[j].distancia;
                if(distancia <= r){
                    estrada += distancia;
                }
                else{
                    qtd_estados++; // Quantidade de estados = Quantidade de ferrovias + 1;
                    ferrovia += distancia;
                }
            }
        }
        printf("Case #%d: %d %d %d\n", i+1, qtd_estados, (int) round(estrada), (int) round(ferrovia));

        free(conj);
        free(tam);
        free(vect_pontos);
        free(dist_cidades);
    }

    return 0;
}

double calc_dist_ponto(Ponto ponto1, Ponto ponto2){
    return sqrt(pow(ponto2.x - ponto1.x, 2) + pow(ponto2.y - ponto1.y, 2));
}

void une(int **conj, int **tam, int a, int b){
    // Supondo que a e b são raízes de conj
    if(a != b){
        if ((*tam)[a] < (*tam)[b]){
            (*conj)[a] = b;
            (*tam)[b] += (*tam)[a];
        }
        else{
            (*conj)[b] = a;
            (*tam)[a] += (*tam)[b];
        }
    }
}

int find(int **conj, int x){
    if(x != (*conj)[x]){
        (*conj)[x] = find(&(*conj), (*conj)[x]);
	}
    return (*conj)[x];
}

/*Realiza o merge sort através das duas funções abaixo
*/
void merge_sort(Aresta **vetor_arestas, int inicio, int fim){
    int meio;
    if(fim - inicio > 1){
        meio = (inicio + fim)/2;
        merge_sort(&(*vetor_arestas), inicio, meio);
        merge_sort(&(*vetor_arestas), meio, fim);
        merge(&(*vetor_arestas), inicio, meio, fim);
    }
}

void merge(Aresta **vetor_arestas, int inicio, int meio, int fim){
    int i, j, pos;
    double *temp;
    i = inicio;
    j = meio;
    pos = 0;

    temp = (double *) malloc((fim-inicio) * sizeof(double));

    while(i < meio && j < fim){
        if((*vetor_arestas)[i].distancia <= (*vetor_arestas)[j].distancia){
            temp[pos] = (*vetor_arestas)[i].distancia;
            i++;
        }
        else{
            temp[pos] = (*vetor_arestas)[j].distancia;
            j++;
        }
        pos++;
    }

    while(i < meio){
        temp[pos] = (*vetor_arestas)[i].distancia;
        i++;
        pos++;
    }

    while(j < fim){
        temp[pos] = (*vetor_arestas)[j].distancia;
        j++;
        pos++;
    }

    for(i=0; i < pos; i++){
        (*vetor_arestas)[inicio+i].distancia = temp[i];
    }
    free(temp);
}