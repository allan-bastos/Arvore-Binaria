#include <stdio.h>
#include <stdlib.h>

//Nó
typedef struct no no;
struct no{
    int valor;
    struct no * esq;
    struct no * dir;
};

//Árvore
typedef struct
{
    no * root;
}ABB;

//INSERÇÃO
//balanceia a inserção na árvore
void balancoInsercao (int lista[], int tamLista, ABB *avr, int *tamArvore){
    int meio = tamLista/2; 
    int i = meio, j = meio+1;
        while (i>=0 || j<tamLista) {
        if (i>=0) {
            insere(avr,lista[i], tamArvore); 
            printf("%d Inserido \n", lista[i]);
            i--;
        }
        if (j<tamLista) {
            insere(avr,lista[j], tamArvore); 
            printf("%d Inserido \n", lista[j]);
            j++;
        }
    }
}

//Insere na árvore
void insere(ABB *avr,int item, int *tamArvore)
{
    *tamArvore=*tamArvore+1;
    no *novo, *aux, *pos=NULL;
    novo = malloc(sizeof(no));
    novo->valor = item;
    novo->esq = NULL;
    novo->dir = NULL;
    
    if(avr->root==NULL)
    {
        avr->root = novo;
    }
    else
    {
        aux = avr->root;
        while (aux!= NULL)
        {
           pos = aux;
           if(item < aux->valor)aux = aux->esq;
           else if(item >= aux->valor) aux = aux->dir;
        }
        if(pos->valor > item) pos->esq = novo;
        else pos->dir = novo;
    }
}

//Impressão da árvore

void imprime_valor(int c, int b) {
    int i;
    for (i = 0; i < b; i++) printf("-");
    printf("%d\n", c);
}

void imprime_arvore(no *x, int b) {
    if (x == NULL) {
        return;
    }
    imprime_arvore(x->esq, b+1);
    imprime_valor(x->valor, b);
    imprime_arvore(x->dir, b+1);
}

//Remoção da árvore

no* busca_pos(ABB *t, int item, no **pai)
{
    no * aux;
    aux = t->root;
    while(aux != NULL && aux->valor != item)
    {
        if(item < aux->valor)
        {
            *pai = aux;
            aux = aux->esq;
            
        }
        else if(item > aux->valor)
        {
            *pai = aux;
            aux = aux->dir;
            
        }
    }
    return aux;
}


int  busca_folha(no *pai)
{
    int val=0;
    no *ant= NULL;
    while(pai->dir != NULL)
    {
        ant = pai;
        pai = pai->dir;
    }
    if(pai->dir == NULL && pai->esq == NULL)
    {
        val = pai->valor;
        //printf("\nValor da Folha: %d", val);
        ant->dir = NULL;
        
    }
    return val;
}

void remove_elementos(ABB *t, int item)
{
    no * aux, * pai, * pos = busca_pos(t, item, &pai);
    //printf("\n\nPos->valor :%d || pai->valor:%d", pos->valor,pai->valor);
    if(pos == NULL)
        printf ("Elemento não encontrado");
    else
    {
        if(pos == t->root)
            t->root = NULL;
        else
        {
           // elemento folha
           if(pos->esq == NULL && pos->dir== NULL)
           {
               if(pai->esq->valor==item) pai->esq = NULL;
               else pai->dir = NULL;
           }
           else // elemento tem dois filhos
           {
               if(pos->esq != NULL && pos->dir!= NULL)
               {
                   // busca folha para troca
                   int val = busca_folha(pos->esq);
                   //troca os valores dos filho mais a direita do filho esquerdo;
                   pos->valor = val;
               }
               else // elemento um dos dois filhos.
               {
                   if((pos->esq != NULL && pos->dir== NULL) ||(pos->esq == NULL && pos->dir!= NULL))
                   {
                       if(pos->dir != NULL) aux = pos->dir;
                       else aux = pos->esq;
                       
                       if(pai->esq->valor==item) pai->esq = aux;
                       else pai->dir = aux;
                   }
               }
                
            }
        }
    }
}

void salvaLista(int lista[], int tamLista){
    FILE *arq;
    int i;
    arq = fopen("SaidaNumeros.txt","w");
    if(!arq){
        printf("Não foi possivel salvar os valors da agenda.\n");
        exit(1);
    }
    fprintf(arq,"%d\n",tamLista);
    for(i=0;i<tamLista;i++){
        fprintf(arq,"%d\n", lista[i]);
    }

    fclose(arq);
}

void carregaLista(int lista[], int *tamLista){
    FILE *arq;
    int i;
    arq = fopen("EntradaNumeros.txt","r");
    if(!arq){
        printf("Nao foi possivel carregar informacoes anteriores.\n");
        *tamLista=0;
    }
    else{
        fscanf(arq,"%d",tamLista);
        
        for(i=0;i<*tamLista;i++){
            fscanf(arq,"%d", &lista[i]);

        }
        
    }
}

int main(int argc, const char * argv[]) {
    int tamLista;
    int lista[500];
    
 

    carregaLista(lista, &tamLista);

    ABB *avr = malloc (sizeof(ABB));
    avr->root = NULL;
    int i = 0;
    int *tamArvore = &i;

    balancoInsercao(lista, tamLista, avr, tamArvore);

    //imprime_arvore(avr->root, 1);

    insere(avr, 5, tamArvore); 
    insere(avr, 3, tamArvore); 

    imprime_arvore(avr->root, 1);

/*

    remove_elementos(t, 4);
    printf("\n\n**********ARVORE RESULTANTE - Remocao 4 *********\n\n");
    imprime_arvore(t->root, 1);
    remove_elementos(t,6);
    printf("\n\n**********ARVORE RESULTANTE - Remocao 6 *********\n\n");
    imprime_arvore(t->root, 1);
    remove_elementos(t,29);
    printf("\n\n**********ARVORE RESULTANTE - Remocao 29 *********\n\n");
    imprime_arvore(t->root, 1);
    */

   salvaLista(lista, tamLista);
   return 0;
}