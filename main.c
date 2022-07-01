#include <stdio.h>
#include <stdlib.h>

//CRIAÇÃO DA ÁRVORE

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

//balanceia a árvore
/*
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
*/

void balanco(int lista[], ABB *avr, int inicio, int fim){
    int meio = (inicio+fim)/2; 
    if (fim<inicio) return;
    insere(avr,lista[meio]);
    balanco(lista, avr, inicio, meio-1);
    balanco(lista, avr, meio+1, fim);
}

//INSERÇÃO

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

void remove_elemento(ABB *avr, int item, FILE *arq)
{
    no * aux, * pai, * pos = busca_pos(avr, item, &pai);
    //printf("\n\nPos->valor :%d || pai->valor:%d", pos->valor,pai->valor);
    if(pos == NULL)
        fprintf (arq, "\nElemento não encontrado para remoção");
    else {
        if(pos == avr->root) {
            fprintf (arq, "\nVOCÊ ESTÁ REMOVENDO A RAIZ -> APAGANDO A ARVORE");
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

//REBALANCEANDO A ARVORE
void coleta_valor(int c, int *b, int *listaRebal[]) {
    listaRebal[*b] = c;
    (*b)++;
}

void coleta_arvore(no *x, int *b, int *listaRebal[]) {
    if (x == NULL) {
        return;
    }
    coleta_arvore(x->esq, b, listaRebal);
    coleta_valor(x->valor, b, listaRebal);
    coleta_arvore(x->dir, b, listaRebal);
}


//CARREGANDO E SALVANDO INFORMAÇÕES EM ARQUVOS EXTERNOS
//Impressão da árvore

void imprime_valor(int c, int b, FILE *arq) {
    int i;
    for (i = 0; i < b; i++) fprintf(arq, "-");
    fprintf(arq, "(%d)\n", c);
}

void imprime_arvore(no *x, int b, FILE *arq) {
    if (x == NULL) {
        return;
    }
    imprime_arvore(x->esq, b+1, arq);
    imprime_valor(x->valor, b, arq);
    imprime_arvore(x->dir, b+1, arq);
}
//Impressão dos números em ordem
void salva_valor(int c, int b, FILE *arq) {
    int i;
    for (i = 0; i < b; i++);
     fprintf(arq,"%d - ", c);
}

void salva_arvore(no *x, int b, FILE *arq) {
    if (x == NULL) {
        return;
    }
    salva_arvore(x->esq, b+1, arq);
    salva_valor(x->valor, b, arq);
    salva_arvore(x->dir, b+1, arq);
}
//carregando as informaçaões
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

    FILE *arq;
    arq = fopen("SaidaNumeros.txt","w");

    //Balanceia, cria e imprime a arvore inicial
    balanco(lista, avr, 0, tamLista-1);
    fprintf(arq, "- Árvore criada: -\n");
    imprime_arvore(avr->root, 1, arq);

    //Inserindo na Árvore binária
    insere(avr, 88);  
    fprintf(arq, "\n\n - Resultado Inserção do 88 -\n");
    imprime_arvore(avr->root, 1, arq);

    //Buscando na Árvore Binária
    fprintf (arq, "\n- Buscando o numero 10 na Arvore Binaria -\n");
    no * pai;
    no * pos = busca_pos(avr, 10, &pai);
    if(pos == NULL) fprintf (arq, "Elemento não encontrado");
    else if (pos->valor == avr->root->valor) fprintf(arq, "Encontrado: Pos->valor :%d É a raiz ", pos->valor);
    else fprintf(arq, "Encontrado -> valor :%d || pai:%d", pos->valor,pai->valor);

    //Removendo da Árvore Binária
    remove_elemento(avr, 40, arq);
    remove_elemento(avr, 20, arq);
    fprintf(arq, "\n\n - Resultado Remocao do 40 e do 20-\n");
    imprime_arvore(avr->root, 1, arq);

    //Rebalanceando a árvore
    int listaRebal[500];
    int b=0;
    int *numRebal = &b;
    coleta_arvore(avr->root, numRebal, listaRebal);
    avr->root = NULL;
    balanco(listaRebal, avr, 0, b-1);
    fprintf(arq, "\n\n- Árvore Rebalanceada: -\n");
    imprime_arvore(avr->root, 1, arq);

    //Salvando a Árvore binária em-ordem
    fprintf(arq, "\n\nPercurso Em-ordem da ABB rebalanceada\n");
    salva_arvore(avr->root, 1, arq);
    fclose(arq);

   return 0;
}