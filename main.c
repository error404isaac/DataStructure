/***************************************

Algoritmo QuickSort em C
Autor: Isaac Ramon Rodrigues da Silva
Estrutura de Dados I
06/05/2022 - v 1.0

****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Função de troca usada nas funções abaixo
Fiz assim pro código ficar mais limpo*/

void  trocaPivot (int *vet, int i, int j){
 int aux = vet[i];
 vet[i] = vet[j];
 vet[j] = aux;
}

/*Função separa transcrita para a linguagem C
do pseudocódigo do slide 27 da aula de ordenação.*/

static int separa (int *v, int inicio, int final){
    int pivo = v[(inicio + final)/2];
    int i = inicio - 1;
    int j = final + 1;
    while (i < j){
        do{
            j--;
    } while(v[j] > pivo);
    do{
        i++;
    } while(v[i] < pivo);
    if (i < j){
         trocaPivot (v, i, j);
    }
    }
    return j;
}

/*Função que escolha o pivô de forma aleatória
Para isso usei a chamada do método rand()
e delimitei os valores pra ele escolher entr
todos os números do vetor.*/

static int separaAleatorio ( int *v, int inicio, int final){
    int pivo = ( rand () % (final - inicio + 1 )) + inicio;

 trocaPivot (v, pivo, final);
 return  separa (v, inicio, final);
}

/*Função para escolher o pivô de forma que seja a median
entre 3 valores, nesse caso, os três valores sã
o início, o meio e o fim do vetor de n posições.*/

static int separaMediana(int *v, int inicio, int final){
    int meio = (inicio + final) / 2;
    int a = v[inicio];
    int b = v[meio];
    int c = v[final];
    int medianaIndice;
    if (a < b) {
        if (b < c) {
            medianaIndice = meio;
        } else {
            if (a < c) {
                medianaIndice = final;
            } else {
                medianaIndice = inicio;
            }
        }
    } else {
        if (c < b) {
            medianaIndice = meio;
        } else {
            if (c < a) {
                medianaIndice = final;
            } else {
                medianaIndice = inicio;
            }
        }
    }
    trocaPivot(v, medianaIndice, final);
    return separa(v, inicio, final);
}

/*Função principal do QuickSort, onde é chamad
a função de separa, e logo após a própria funçã
é chamada dentro dela mesma para ordenar o
subvetores até que não tenha mais como subdividir.*/

/*Para usar cada função de separa é só comentar a
outras com "//" e deixar a a que quer usar sem comentar.*/

void quicksort (int *v, int inicio, int final){
    if(inicio < final){
        //int pi = separa(v, inicio, final);
        //int pi = separaAleatorio(v, inicio, final);
        int pi = separaMediana(v, inicio, final);
        quicksort (v, inicio, pi);
        quicksort (v, pi+1, final);
   }
}

/*Função para mostrar o vetor ordenado, junto com o temp
de execução em ms para cada função. Porém não achei u
bom método para mostrar o tempo, pois ele sempre esper
terminar de mostrar todos os valores pra poder mostra
o tempo, o que acaba aumentando bastante o tempo.*/

void mostrar(int *v, int tamanho){
    clock_t Ticks[2];
    Ticks[0] = clock();   
    
    printf("Vetor ordenado:\n");
    for (int i = 0; i < tamanho; ++i){
    printf("%d\n", v[i]);
  }
  printf("\n");
  Ticks[1] = clock();
  double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
  printf("Tempo gasto: %g ms.", Tempo);
  getchar();
}

/*Função principal*/
int main(){
    
    int *vet, i, n, op, tam;
    
    printf("Qual o tamanho do vetor a ser ordenado?\n"
    "1- 100000\n"
    "2- 1000000\n"
    "3- 10000000\n"
    "0- Sair\n");
    
    scanf("%d", &op);
    
    switch (op){
    
    case 0:
    system ("exit");
    break;
    
    case 1:
    /*Alocando o vetor dinamicamente de acordo com seu tamanho.*/
    tam = 100000;
    vet = (int *)malloc(tam * sizeof(int));
    /*Gerando números aleatórios para o vetor, em um interval
    de 0 até 10 vezes o tamanho do vetor.*/
    srand(time(NULL));
    
    for (i = 0; i < tam; i++){
        vet[i] = rand() % tam * 10;
    }

/*Chamada da função QuickSort para ordenar o vetor*/
    quicksort (vet, 0, tam);
    mostrar (vet, tam);
    
/*Comentar as duas linhas acima se quiser usar o método abaixo.*/

/*No método abaixo, o vetor não é mostrado ordenado, é mostrad
apenas o tempo de execução para ordenar o vetor. Para montar 
tabela do artigo eu usei esse método para contar o tempo./*


/*Em cada case (1, 2 e 3) tem um código desse. Porém para usa
em cada case, o do restante tem que estar comentado para nao da
conflito nas variáveis.*/
      
    /*clock_t Ticks[2];
    Ticks[0] = clock();
    
    quicksort (vet, 0, tam);    
    
    Ticks[1] = clock();
    double tempo = (Ticks[1] - Ticks[0])
    * 1000.0 / CLOCKS_PER_SEC;
    
    printf("Tempo gasto: %g ms.", tempo);
    
    getchar();*/

/*Liberando o vetor da memória.*/
    free(vet);
    system("pause");
  
    break;
    
    case 2:
    
    tam = 1000000;
    
    vet = (int *)malloc(tam * sizeof(int));
        
    srand(time(NULL));
    
    for (i = 0; i < tam; i++){
        vet[i] = rand() % tam * 10;
    }
    
    quicksort (vet, 0, tam);
    mostrar(vet, tam);
    
    /*clock_t Ticks[2];
    Ticks[0] = clock();
    
    quicksort (vet, 0, tam);
    
    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0])
    * 1000.0 / CLOCKS_PER_SEC;
    
    printf("Tempo gasto: %g ms.", Tempo);
    
    getchar();*/
    
    free(vet);
    system("pause");
    
    break;
    
    case 3:
    
    tam = 10000000;
    
    vet = (int *)malloc(tam * sizeof(int));
        
    srand(time(NULL));
    
    for (i = 0; i < tam; i++){
        vet[i] = rand() % tam;
    }
    
    quicksort (vet, 0, tam);
    mostrar(vet, tam);
    
    /*clock_t Ticks[2];
    Ticks[0] = clock();
    
    quicksort (vet, 0, tam);
    
    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0])
    * 1000.0 / CLOCKS_PER_SEC;
    
    printf("Tempo gasto: %g ms.", Tempo);
  
    getchar();*/
    
    free(vet);
    system("pause");
  
    break;
    }
    return 0;
  }