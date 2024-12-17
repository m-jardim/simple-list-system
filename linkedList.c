#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

//struct para os itens
typedef struct item{
    int codigo;
    float valor;
    int quantidade;
    char descricao[50];

    struct item* next;
}item;

//struct para o estoque
typedef struct stock{
    int codigo;
    float valor;
    int quantidade;
    char descricao[50];

    struct item* next;
}stock;

//head para a lista de itens e para o estoque
item* head = NULL;
stock* shead = NULL;

//estado de fluxo atual
int state_system = 0;

//prototype
void menu();
void display_items();
void add_item();
void remove_item();
void find_item();
void volume_stock();
void menu_back();

// funcao principal
int main(){
    // definindo a localidade pro BR
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // criando um pseudo laco infinito
    while(1){
        printf(" \033[40m");    // cor (fundo(preto))
        // switch controlando o fluxo do programa por meio dos estados de "state_system"
        switch(state_system){   
            case 0:
                menu();
            break;
            case 1:
                display_items();
            break;
            case 2:
                add_item();
            break;
            case 3:
                remove_item();
            break;
            case 4:
                find_item();
            break;
            case 5:
                volume_stock();
            break;
            case 6:
                exit(0);
            break;
        }
    }
    return 0;
}

// funcao do menu principal
void menu(){
    system("clear"); // limpando a tela (se estiver no windows trocar para cls)
    printf("\033[H\033[J"); // tambem de limpar a tela (so pra garantir :D)
    printf("\033[96m");    // cor

    // impressao de "menu"
    printf("\n--------------------------------------------------------------------------------");
    printf("\n--------------------------------------MENU--------------------------------------");
    printf("\n--------------------------------------------------------------------------------");

    printf("\033[35m");  // cor
    // opcoes para escolher
    printf("\n\n1->Consultar Produtos");
    printf("\n2->Cadastrar Produto");
    printf("\n3->Remover Produto");
    printf("\n4->Procurar Produto");
    printf("\n5->Volume em Estoque");
    printf("\n6->Sair\n");
    
    int verify = 0;
    while(verify != 1){ 
        printf("\n-->Digite a opcao desejada: ");
        scanf("%d", &state_system);
        if(state_system > 0 && state_system < 7){   // verificando se a opcao é válida
            verify = 1; // sai do while
        }
    }
    system("clear"); // limpando a tela (se estiver no windows trocar para cls)
}

// funcao para adicionar um item
void add_item(){
    system("clear"); // limpando a tela (se estiver no windows trocar para cls)

    //impressao de "adicionar item"
    printf("\033[96m");    // cor
    printf("\n--------------------------------------------------------------------------------");
    printf("\n---------------------------------ADICIONAR-ITEM---------------------------------");
    printf("\n--------------------------------------------------------------------------------");
    
    item* current_item = malloc(sizeof(item));  // alocando memoria para o item
    current_item->next = NULL;  // inicializando o campo next do item como NULL

    // obter os dados do item
    printf("\033[95m"); // cor
    printf("\n\n-->Digite o codigo do produto: ");
    scanf("%d", &current_item->codigo);
    printf("-->Digite o valor do produto: ");
    getchar();
    scanf("%f", &current_item->valor);
    printf("-->Digite a quantidade do produto: ");
    getchar();
    scanf("%d", &current_item->quantidade);
    printf("-->Digite a descricao do produto: ");
    getchar();
    fgets(current_item->descricao, sizeof(current_item->descricao), stdin);

    if(head == NULL){   // caso nao tenha nenhum item
        head = current_item;
    }else{  // caso tenha itens
        item* browse = head;

        while(browse->next != NULL){    // se percorre ate o ultimo item
            browse = browse->next;
        }
        browse->next = current_item;    // o ultimo item apontara para o item atual
    }
    state_system = 0;   // menu
}

// funcao para imprimir todos os itens
void display_items(){
    system("clear"); //limpando a tela (se estiver no windows trocar para cls)
    printf("\033[96m"); // cor

    // impressao de "menu"
    printf("\n--------------------------------------------------------------------------------");
    printf("\n--------------------------------------ITENS-------------------------------------");
    printf("\n--------------------------------------------------------------------------------");

    printf("\033[95m"); // cor

    if(head == NULL){   // caso nao tenha itens cadastrados
        printf("\n\n-->Nao existem produtos cadastrados!!!!!!\n");
        sleep(2);
        state_system = 0;   // menu
        return;
    }

    item* browse = head;
    while(browse != NULL){  // percorrer e printar os itens
        printf("\n\n-->Codigo: %d", browse->codigo);
        printf("\n-->Valor: %f", browse->valor);
        printf("\n-->Quantidade: %d", browse->quantidade);
        printf("\n-->Descricao: %s", browse->descricao);

        browse = browse->next;  // proximo item
    }
    menu_back();
}

// funcao para remover item
void remove_item(){
    system("clear"); //limpando a tela (se estiver no windows trocar para cls)
    printf("\033[96m");    // cor

    //impressao de "remover item"
    printf("\n--------------------------------------------------------------------------------");
    printf("\n----------------------------------REMOVER ITEM----------------------------------");
    printf("\n--------------------------------------------------------------------------------");

    printf("\033[95m"); // cor

    // caso nao exista nenhum item
    if(head == NULL){  
        printf("\n\n-->Nao existem produtos cadastrados!!!\n");
        state_system = 0;   // menu
        sleep(2);
        return;
    }

    int index;
    printf("\n\n-->Digite o indice do item a ser removido: ");
    scanf("%d", &index);

    // caso o indice seja negativo
    if(index < 0){  
        printf("-->Indice invalido!!!");
        return;
    }

    // Verificar se o índice está dentro do número de itens na lista
    item* temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    if (index >= count) {  // Índice maior que o número de itens
        printf("-->Indice fora do alcance!!!\n");
        return;
    }

    
    // caso queira remover o primeiro item
    if(index == 0){ 
        item* current = head;
        head = head->next;
        free(current);
        printf("\n\n-->Removido com sucesso!!!\n\n");
        sleep(2);
        state_system = 0;
        return;
    }

    item* browse = head;
    for (int i = 0; i < index - 1; i++) {   // percorrer ate o item anterior ao que desejamos remover
        browse = browse->next;
    }
    if(browse->next->next == NULL){
        free(browse->next);  
        browse->next = NULL;
    } else {
        item* temp = browse->next;
        browse->next = temp->next;
        free(temp);
    }
    printf("\n\n-->Removido com sucesso!!!\n\n");
    sleep(2);
    state_system = 0; 
}

// funcao para encontrar um item pelo seu codigo
void find_item(){
    system("clear"); // limpando a tela (se estiver no windows trocar para cls)
    printf("\033[96m"); // cor

    //impressao de "encontrar item"
    printf("\n--------------------------------------------------------------------------------");
    printf("\n---------------------------------ENCONTRAR-ITEM---------------------------------");
    printf("\n--------------------------------------------------------------------------------");

    printf("\033[95m");    // cor

    if(head == NULL){   // se nao houver itens
        printf("\n\n-->Nao existem produtos cadastrados!!!\n");
        sleep(2);
        state_system = 0;
        return;
    }

    int index = 0;
    int codigo;

    printf("\n\n-->Digite o codigo do produto: "); // obtendo o codigo do produto
    scanf("%d", &codigo);
    
    item* browse = head;
    while(browse != NULL){  // percorrendo os itens e verificando se os codigos batem
        if(codigo == browse->codigo){
            printf("-->Indice: %d\n", index);
            menu_back();
            return;
        }
        index++;
        browse = browse->next;
    }
    // caso chegue a este ponto, significa que o produto nao foi encontrado
    printf("\n-->Produto nao encontrado!!!\n");
    sleep(2);
    state_system = 0;   // menu
}

//funcao de estoque
void volume_stock(){  
    system("clear");

    //impressao de "estoque"
    printf("\033[96m"); // cor
    printf("\n--------------------------------------------------------------------------------");
    printf("\n-------------------------------------ESTOQUE------------------------------------");
    printf("\n--------------------------------------------------------------------------------");

    printf("\033[95m"); // cor
    if(head == NULL){   // caso nao exista nenhum item
        printf("\n\n-->Nao existem produtos cadastrados!!!\n");
        state_system = 0;   // menu
        sleep(2);
        return;
    }
    
    int number;
    printf("\n\n-->Digite a quantidade minima de estoque: ");
    scanf("%d", &number);

    item* copier = head;
    while(copier != NULL){
        if(copier->quantidade < number){
            // criacao de um novo no para a nova lista
            stock* current_item = malloc(sizeof(stock));
            current_item->codigo = copier->codigo;
            current_item->valor = copier->valor;
            current_item->quantidade = copier->quantidade;
            strcpy(current_item->descricao, copier->descricao); // Cópia da string
            current_item->next = NULL;

            if(shead == NULL){   // caso nao tenha nenhum item
                 shead = current_item;
             }else{  // caso tenha itens
                stock* browse = shead;
                while(browse->next != NULL){    // percorre ate o ultimo item
                    browse = browse->next;
                }
                browse->next = current_item;    // o ultimo item apontara para o item atual
            }

            printf("\n\n-->Codigo: %d", current_item->codigo);
            printf("\n-->Valor: %f", current_item->valor);
            printf("\n-->Quantidade: %d", current_item->quantidade);
            printf("\n-->Descricao: %s", current_item->descricao);
        }
        copier = copier->next;
    }
    menu_back();
    return;
}

//funcao para voltar ao menu principal
void menu_back(){
    int option;
    int verify = 0;

    while(verify == 0){
        printf("\n\n-->Digite 1 para voltar ao menu: ");
        scanf("%d", &option);

        if(option == 1){
            state_system = 0;
            verify = 1;
        }
    }
}
