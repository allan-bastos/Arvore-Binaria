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
void balanco(int lista[], int tamLista, ABB *avr){
    int meio = tamLista/2; 
    int i = meio, j = meio+1;
        while (i>=0 || j<tamLista) {
        if (i>=0) {
            insere(avr,lista[i]); 
            i--;
        }
        if (j<tamLista) {
            insere(avr,lista[j]); 
            j++;
        }
    }
}

//Insere na árvore
void insere(ABB *avr,int item)
{
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
no* busca_pos(ABB *avr, int item, no **pai)
{
    no * aux;
    aux = avr->root;
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

int  busca_folha(no *pai, no **rai)
{
    int val=0;
    no *ant= NULL;

    while(pai->esq != NULL)
    {
        ant = pai;
        pai = pai->esq;
        
    }
    if(pai->esq == NULL && pai->dir == NULL)
    {
        val = pai->valor;
        *rai = NULL;
               
    }
    return val;
}

void remove_elemento(ABB *avr, int item)
{
    no * aux, * pai, * pos = busca_pos(avr, item, &pai);
    //printf("\n\nPos->valor :%d || pai->valor:%d", pos->valor,pai->valor);
    if(pos == NULL)
        printf ("\n\n Elemento não encontrado para remoção");
    else {
        if(pos == avr->root) {
            printf ("\n\nVOCÊ ESTÁ REMOVENDO A RAIZ -> APAGANDO A ARVORE");
            avr->root = NULL;
        }
        else
        {
           // elemento folha
           if(pos->esq == NULL && pos->dir== NULL)
           {
               if(pai->dir->valor==item) pai->dir = NULL;
               else pai->esq = NULL;
           }
           else // elemento tem dois filhos
           {
               if(pos->esq != NULL && pos->dir!= NULL)
               {
                   // busca folha para troca
                   int val = busca_folha(pos->dir, &pos->dir);
                   //troca os valores dos filho mais a esquerda do filho direito;
                   pos->valor = val;
               }
              else // elemento um dos dois filhos.
               {
                   if((pos->esq != NULL && pos->dir== NULL) ||(pos->esq == NULL && pos->dir!= NULL))
                   {
                       if(pos->dir != NULL) aux = pos->dir;
                       else aux = pos->esq;

                       if(pai->dir->valor==item) pai->dir = aux;
                       else pai->esq = aux;
                   }
               }
                
            }
        }
    }
}


//Carregando e Salvando a árvore

void salva_valor(int c, int b, FILE *arq) {
    int i;
    for (i = 0; i < b; i++);
     fprintf(arq,"%d \n", c);
}

void salva_arvore(no *x, int b, FILE *arq) {
    if (x == NULL) {
        return;
    }
    salva_arvore(x->esq, b+1, arq);
    salva_valor(x->valor, b, arq);
    salva_arvore(x->dir, b+1, arq);
}

void salvaLista(ABB *avr){
    FILE *arq;
    int i;
    arq = fopen("SaidaNumeros.txt","w");
    if(!arq){
        printf("Não foi possivel salvar a árvore.\n");
        exit(1);
    }
    fprintf(arq, "Resultado da árvore em-ordem \n");
    salva_arvore(avr->root, 1, arq);
    fclose(arq);
}

void carregaLista(int lista[], int *tamLista){
    FILE *arq;
    int i;
    arq = fopen("EntradaNumeros.txt","r");
    if(!arq){
        printf("Nao foi possivel carregar informacoes do arquivo.\n");
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

    //Balanceia, cria e imprime a arvore inicial
    balanco(lista, tamLista, avr);
    printf("\n\n - Árvore criada: -\n\n");
    imprime_arvore(avr->root, 1);

    //Inserindo na Árvore binária
    insere(avr, 85); 
    insere(avr, 35);
    insere(avr, 33);
    insere(avr, 37);
    printf("\n\n - Resultado Inserção do 85, 35, 33 e 37 -\n\n");
    imprime_arvore(avr->root, 1);

    //Buscando na Árvore Binária
    printf ("\nBuscando o numero 10 na Arvore Binaria: \n");
    no * pai;
    no * pos = busca_pos(avr, 10, &pai);
    if(pos == NULL) printf ("Elemento não encontrado");
    else if (pos->valor == avr->root->valor) printf("Encontrado: Pos->valor :%d É a raiz ", pos->valor);
    else printf("Encontrado - valor :%d || pai:%d", pos->valor,pai->valor);

    //Removendo da Árvore Binária
    remove_elemento(avr, 35);
    remove_elemento(avr, 90);
    printf("\n\n - Resultado Remocao do 35 e do 90-\n\n");
    imprime_arvore(avr->root, 1);

    //Rebalanceando a árvore


    //Salvando a Árvore binária em-ordem
    salvaLista(avr);
   return 0;
}