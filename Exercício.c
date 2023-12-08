#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* Implementar um sistema de controle de estoque com as funcionalidades de cadastrar produtos, consultar produtos, gerar relatórios de produtos e remover produtos do estoque.*/

typedef struct Produto{
    int id, quantidade;
    float valor;
    char descricao[100], nome[15];
    struct Produto *prox; //ponteiro que armazena o endereço do próximo produto.
}Produto;

Produto* criarListavazia(){
    return NULL;
}

//função para criar um novo registro.
Produto* criarProduto(){
    Produto *novoProduto = (Produto*)malloc(sizeof(Produto));
    if(novoProduto == NULL){
        printf("\n Erro de alocacao de memoria.");
        exit(EXIT_FAILURE);
    }
    novoProduto->prox = NULL;
    return novoProduto;
}

Produto* cadastrar(Produto *lista){
    Produto *novoProduto = criarProduto();
    printf("\n Digite o codigo (Id) do produto:");
    fflush(stdin);
    scanf("%d", &novoProduto->id);
    printf("\n Informe o nome do produto:");
    fflush(stdin);
    fgets(novoProduto->nome, sizeof(novoProduto->nome), stdin);
    printf("\n Descreva o produto:");
    fflush(stdin);
    fgets(novoProduto->descricao, sizeof(novoProduto->descricao), stdin);
    printf("\n Informe a quantidade do produto:");
    fflush(stdin);
    scanf("%d", &novoProduto->quantidade);
    printf("\n Digite o valor do produto:");
    scanf("%f", &novoProduto->valor);

    //verificar se a lista é nula.
    if(lista == NULL){
        return novoProduto;
    }else{
        Produto* atual = lista;
        while(atual->prox != NULL){
            atual = atual->prox;
            //sai da repetição quando encontrar o elemento que aponta para null.
        }
        atual->prox = novoProduto;
        return lista;
    }
}

void mostrarLista(Produto* lista){
    Produto *atual = lista;
    if(atual == NULL){
        printf("\n Lista vazia.");
        return;
    }else{
        while(atual != NULL){
            printf("\n\n");
            printf("Nome: %s \n", atual->nome);
            printf("ID: %d \n", atual->id);
            printf("Descricao: %s \n", atual->descricao);
            printf("Quantidade de produtos em estoque: %d \n", atual->quantidade);
            printf("Valor do produto: %f \n", atual->valor);
            atual = atual->prox;
        }
    }
}

Produto* buscar(Produto *lista, int idBusca){
    Produto *atual = lista;
    if(atual == NULL){
        printf("\n Lista vazia.");
        return;
    }else{
        while(lista != NULL){
            if(atual->id == idBusca){
                printf("\n\n");
                printf("Nome: %s \n", atual->nome);
                printf("ID: %d \n", atual->id);
                printf("Descricao: %s \n", atual->descricao);
                printf("Quantidade de produtos em estoque: %d \n", atual->quantidade);
                printf("Valor do produto: %f \n", atual->valor);
                return atual;
            }
            atual = atual->prox;
        }
        printf("\n Produto nao encontrado.");
        return NULL;
    }
}

Produto* excluir(Produto *lista, int idBusca){
    Produto *atual = lista;
    Produto* anterior = NULL;
    //percorrer a lista procurando quem excluir.
    while(atual != NULL && atual->id != idBusca){
        //A ordem é importante!!
        anterior = atual;
        atual = atual->prox;
    }
    if(atual != NULL){
        if(anterior != NULL){
            //Excluir alguém antes do primeiro da lista.
            anterior->prox = atual->prox;
        }else{
            //Excluir o primeiro da lista.
            lista = atual->prox;
        }
        free(atual);
        printf("\n Produto excluida com sucesso. \n");
    }else{
        printf("\n Produto nao encontrada. \n");
    }
    return lista;
}

void liberarlista(Produto *lista){
    Produto *atual = lista;
    Produto *proximoProduto;
    while(atual != NULL){
        proximoProduto = atual->prox;
        free(atual);
        atual = proximoProduto;
    }
}

main(){

   Produto *lista; // ponteiro que sempre será o primeiro da lista.
   lista = criarListavazia();
   Produto *encontrado; //armazena o produto encontrado para excluí-lo.
   int opcao, idBusca;

   do{
    printf("\n 0 - Finalizar programa;");
    printf("\n 1 - Cadastrar produto;");
    printf("\n 2 - Mostrar o estoque;");
    printf("\n 3 - Pesquisar produto;");
    printf("\n 4 - Remover produto.");
    printf("\n Informe a opcao escolhida:");
    scanf("%d", &opcao);

    switch(opcao){
        case 1:
        lista = cadastrar(lista);
        break;

        case 2:
        mostrarLista(lista);
        break;

        case 3:
        printf("\n Digite o id para buscar o produto:");
        scanf("%d", &idBusca);
        encontrado = buscar(lista, idBusca);
        break;

        case 4:
        printf("\n Digite o id para excluir um produto do estoque:");
        scanf("%d", &idBusca);
        lista = excluir(lista, idBusca);
        break;
    }
   }while(opcao != 0);

   liberarlista(lista);

}