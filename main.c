#include <stdio.h>
#include <stdlib.h>

//no
typedef struct no no;
struct no{
    int dado;
    no * esq;
    no * dir;
};

//tree
typedef struct
{
    no * root;
}ABB;

//------------------------------------------- Insere na Arvore --------------------------------------

void insere(ABB *t,int item)
{
    no *novo, *aux, *pos=NULL;
    novo = malloc(sizeof(no));
    novo->dado = item;
    novo->esq = NULL;
    novo->dir = NULL;
    
    if(t->root==NULL)
    {
        t->root = novo;
    }
    else
    {
        aux = t->root;
        while (aux!= NULL)
        {
           pos = aux;
           if(item <aux->dado)aux = aux->esq;
           else if(item > aux->dado) aux = aux->dir;
        }
        if(pos->dado > item) pos->esq = novo;
        else pos->dir = novo;
    }
}

//------------------------------------ Imprime a arvore identada -----------------------------------------

void imprime_dado(int c, int b) {
    int i;
    for (i = 0; i < b; i++) printf("-");
    printf("%d\n", c);
}

void imprime_arvore(no *x, int b) {
    if (x == NULL) {
        return;
    }
    imprime_arvore(x->esq, b+1);
    imprime_dado(x->dado, b);
    imprime_arvore(x->dir, b+1);
}

//-------------------------------------- Remove elementos da arvore ---------------------------------

no* busca_pos(ABB *t, int item, no **pai)
{
    no * aux;
    aux = t->root;
    while(aux != NULL && aux->dado != item)
    {
        if(item < aux->dado)
        {
            *pai = aux;
            aux = aux->esq;
            
        }
        else if(item > aux->dado)
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
        val = pai->dado;
        //printf("\nValor da Folha: %d", val);
        ant->dir = NULL;
        
    }
    return val;
}

void remove_elementos(ABB *t, int item)
{
    no * aux, * pai, * pos = busca_pos(t, item, &pai);
    //printf("\n\nPos->dado :%d || pai->dado:%d", pos->dado,pai->dado);
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
               if(pai->esq->dado==item) pai->esq = NULL;
               else pai->dir = NULL;
           }
           else // elemento tem dois filhos
           {
               if(pos->esq != NULL && pos->dir!= NULL)
               {
                   // busca folha para troca
                   int val = busca_folha(pos->esq);
                   //troca os valores dos filho mais a direita do filho esquerdo;
                   pos->dado = val;
               }
               else // elemento um dos dois filhos.
               {
                   if((pos->esq != NULL && pos->dir== NULL) ||(pos->esq == NULL && pos->dir!= NULL))
                   {
                       if(pos->dir != NULL) aux = pos->dir;
                       else aux = pos->esq;
                       
                       if(pai->esq->dado==item) pai->esq = aux;
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
    arq = fopen("listaNumeros.txt","w");
    if(!arq){
        printf("Não foi possivel salvar os dados da agenda.\n");
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
    arq = fopen("listaNumeros.txt","r");
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

    //salvaLista(lista, tamLista);
    carregaLista(lista, &tamLista);
    

    for(int i=0; i<tamLista; i++){
        printf("%d - ", lista[i]);
    }

    

    /*
    ABB *t = malloc (sizeof(ABB));
    t->root = NULL;
    
    //monta arvore.
    insere(t,10);
    insere(t,4);
    insere(t,2);
    insere(t,3);
    insere(t,20);
    insere(t,17);
    insere(t,29);
    insere(t,6);
    insere(t,9);
    
    printf("\n\n**********ARVORE MONTADA*********\n\n");
    imprime_arvore(t->root, 1);
    
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
   return 0;
}