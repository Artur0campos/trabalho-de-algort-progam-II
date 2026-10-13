#include <stdio.h>
#include <string.h>
#include "cliente.h"

/* static = visível apenas dentro deste arquivo (encapsulamento) */
static Cliente lista_clientes[MAX_CLIENTES];
static int total_clientes = 0;


static int buscar_indice_cliente(int codigo) {
    for (int i = 0; i < total_clientes; i++) {
        if (lista_clientes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int armazenar_cliente(Cliente c) {
    if (total_clientes >= MAX_CLIENTES) {
        printf("\nErro: Limite de clientes atingido!\n");
        return 0;
    }

    lista_clientes[total_clientes] = c;
    total_clientes++;

    printf("\nCliente '%s' armazenado com sucesso!\n", c.nome);
    return 1;
}

Cliente cadastrar_cliente(void) {

    Cliente novo;

    printf("\n====== NOVO CADASTRO DE CLIENTE ======\n");
    printf("Código: ");
    scanf("%d", &novo.codigo);
    getchar();

    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("CPF: ");
    fgets(novo.cpf, sizeof(novo.cpf), stdin);
    novo.cpf[strcspn(novo.cpf, "\n")] = '\0';

    printf("Telefone: ");
    fgets(novo.telefone, sizeof(novo.telefone), stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = '\0';

    printf("E-mail: ");
    fgets(novo.email, sizeof(novo.email), stdin);
    novo.email[strcspn(novo.email, "\n")] = '\0';

    printf("Cidade: ");
    fgets(novo.cidade, sizeof(novo.cidade), stdin);
    novo.cidade[strcspn(novo.cidade, "\n")] = '\0';

    return novo;
}

void listar_clientes(void) {
    if (total_clientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }

    printf("\n====== LISTA DE CLIENTES ======\n");
    for (int i = 0; i < total_clientes; i++) {
        printf("----------------------------------------\n");
        printf("Código: %d\n", lista_clientes[i].codigo);
        printf("Nome: %s\n", lista_clientes[i].nome);
        printf("CPF: %s\n", lista_clientes[i].cpf);
        printf("Telefone: %s\n", lista_clientes[i].telefone);
        printf("E-mail: %s\n", lista_clientes[i].email);
        printf("Cidade: %s\n", lista_clientes[i].cidade);
    }
    printf("----------------------------------------\n");
}

void buscar_cliente(void) {
    int codigo;

    printf("\nDigite o código do cliente que deseja buscar: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_cliente(codigo);

    if (indice == -1) {
        printf("\nCliente não encontrado!\n");
        return;
    }

    printf("\n====== CLIENTE ENCONTRADO ======\n");
    printf("Código: %d\n", lista_clientes[indice].codigo);
    printf("Nome: %s\n", lista_clientes[indice].nome);
    printf("CPF: %s\n", lista_clientes[indice].cpf);
    printf("Telefone: %s\n", lista_clientes[indice].telefone);
    printf("E-mail: %s\n", lista_clientes[indice].email);
    printf("Cidade: %s\n", lista_clientes[indice].cidade);
}

void alterar_cliente(void) {
    int codigo;

    printf("\nDigite o código do cliente que deseja alterar: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_cliente(codigo);

    if (indice == -1) {
        printf("\nCliente não encontrado!\n");
        return;
    }

    printf("\n====== ALTERAR CLIENTE ======\n");
    printf("(Deixe em branco e pressione Enter para manter o valor atual)\n");

    char buffer[50];

    printf("Nome atual: %s\n", lista_clientes[indice].nome);
    printf("Novo nome: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        snprintf(lista_clientes[indice].nome, sizeof(lista_clientes[indice].nome), "%s", buffer);
    }

    printf("CPF atual: %s\n", lista_clientes[indice].cpf);
    printf("Novo CPF: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        snprintf(lista_clientes[indice].cpf, sizeof(lista_clientes[indice].cpf), "%.*s", (int)sizeof(lista_clientes[indice].cpf) - 1, buffer);
    }

    printf("Telefone atual: %s\n", lista_clientes[indice].telefone);
    printf("Novo telefone: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        snprintf(lista_clientes[indice].telefone, sizeof(lista_clientes[indice].telefone), "%.*s", (int)sizeof(lista_clientes[indice].telefone) - 1, buffer);
    }

    printf("E-mail atual: %s\n", lista_clientes[indice].email);
    printf("Novo e-mail: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        snprintf(lista_clientes[indice].email, sizeof(lista_clientes[indice].email), "%s", buffer);
    }

    printf("Cidade atual: %s\n", lista_clientes[indice].cidade);
    printf("Nova cidade: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        snprintf(lista_clientes[indice].cidade, sizeof(lista_clientes[indice].cidade), "%s", buffer);
    }

    printf("\nCliente atualizado com sucesso!\n");
}

void excluir_cliente(void) {
    int codigo;

    printf("\nDigite o código do cliente que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_cliente(codigo);

    if (indice == -1) {
        printf("\nCliente não encontrado!\n");
        return;
    }

    for (int i = indice; i < total_clientes - 1; i++) {
        lista_clientes[i] = lista_clientes[i + 1];
    }
    total_clientes--;

    printf("\nCliente excluído com sucesso!\n");
}