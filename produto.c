#include <stdio.h>
#include <string.h>
#include "produto.h"

/* static = visível apenas dentro deste arquivo (encapsulamento) */
static Produto lista_produtos[MAX_PRODUTOS];
static int total_produtos = 0;


static int buscar_indice_produto(int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int armazenar_produto(Produto p) {
    if (total_produtos >= MAX_PRODUTOS) {
        printf("\nErro: Limite de produtos atingido!\n");
        return 0;
    }

    lista_produtos[total_produtos] = p;
    total_produtos++;

    printf("\nProduto '%s' armazenado com sucesso!\n", p.nome);
    return 1;
}

Produto cadastrar_produto(void) {

    Produto novo;

    printf("\n====== NOVO CADASTRO DE PRODUTO ======\n");
    printf("Código: ");
    scanf("%d", &novo.codigo);
    getchar();

    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Categoria: ");
    fgets(novo.categoria, sizeof(novo.categoria), stdin);
    novo.categoria[strcspn(novo.categoria, "\n")] = '\0';

    printf("Preço: ");
    scanf("%f", &novo.preco);
    getchar();

    printf("Quantidade em estoque: ");
    scanf("%d", &novo.quantidade_em_estoque);
    getchar();

    return novo;
}

void listar_produtos(void) {
    if (total_produtos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n====== LISTA DE PRODUTOS ======\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("----------------------------------------\n");
        printf("Código: %d\n", lista_produtos[i].codigo);
        printf("Nome: %s\n", lista_produtos[i].nome);
        printf("Categoria: %s\n", lista_produtos[i].categoria);
        printf("Preço: %.2f\n", lista_produtos[i].preco);
        printf("Quantidade em estoque: %d\n", lista_produtos[i].quantidade_em_estoque);
    }
    printf("----------------------------------------\n");
}

void buscar_produto(void) {
    int codigo;

    printf("\nDigite o código do produto que deseja buscar: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_produto(codigo);

    if (indice == -1) {
        printf("\nProduto não encontrado!\n");
        return;
    }

    printf("\n====== PRODUTO ENCONTRADO ======\n");
    printf("Código: %d\n", lista_produtos[indice].codigo);
    printf("Nome: %s\n", lista_produtos[indice].nome);
    printf("Categoria: %s\n", lista_produtos[indice].categoria);
    printf("Preço: %.2f\n", lista_produtos[indice].preco);
    printf("Quantidade em estoque: %d\n", lista_produtos[indice].quantidade_em_estoque);
}

void alterar_produto(void) {
    int codigo;

    printf("\nDigite o código do produto que deseja alterar: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_produto(codigo);

    if (indice == -1) {
        printf("\nProduto não encontrado!\n");
        return;
    }

    printf("\n====== ALTERAR PRODUTO ======\n");
    printf("(Deixe em branco e pressione Enter para manter o valor atual)\n");

    char buffer[80];

    printf("Nome atual: %s\n", lista_produtos[indice].nome);
    printf("Novo nome: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        snprintf(lista_produtos[indice].nome, sizeof(lista_produtos[indice].nome), "%s", buffer);
    }

    printf("Categoria atual: %s\n", lista_produtos[indice].categoria);
    printf("Nova categoria: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        snprintf(lista_produtos[indice].categoria, sizeof(lista_produtos[indice].categoria), "%s", buffer);
    }

    printf("Preço atual: %.2f\n", lista_produtos[indice].preco);
    printf("Novo preço (digite -1 para manter o atual): ");
    float novo_preco;
    scanf("%f", &novo_preco);
    getchar();
    if (novo_preco >= 0) {
        lista_produtos[indice].preco = novo_preco;
    }

    printf("Estoque atual: %d\n", lista_produtos[indice].quantidade_em_estoque);
    printf("Novo estoque (digite -1 para manter o atual): ");
    int novo_estoque;
    scanf("%d", &novo_estoque);
    getchar();
    if (novo_estoque >= 0) {
        lista_produtos[indice].quantidade_em_estoque = novo_estoque;
    }

    printf("\nProduto atualizado com sucesso!\n");
}

void excluir_produto(void) {
    int codigo;

    printf("\nDigite o código do produto que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_produto(codigo);

    if (indice == -1) {
        printf("\nProduto não encontrado!\n");
        return;
    }

    for (int i = indice; i < total_produtos - 1; i++) {
        lista_produtos[i] = lista_produtos[i + 1];
    }
    total_produtos--;

    printf("\nProduto excluído com sucesso!\n");
}