#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "util.h"

#define ARQUIVO_CLIENTES "clientes.dat"

static Cliente lista_clientes[MAX_CLIENTES];
static int total_clientes = 0;

/* Carrega os clientes do arquivo binário */
void carregar_clientes(void) {
    FILE *fp = fopen(ARQUIVO_CLIENTES, "rb");
    if (fp == NULL) {
        total_clientes = 0;
        return;
    }

    total_clientes = (int)fread(lista_clientes, sizeof(Cliente), MAX_CLIENTES, fp);
    fclose(fp);
}

/* Salva os clientes no arquivo binário */
void salvar_clientes(void) {
    FILE *fp = fopen(ARQUIVO_CLIENTES, "wb");
    if (fp == NULL) {
        printf("\nErro ao abrir o arquivo '%s' para gravação!\n", ARQUIVO_CLIENTES);
        return;
    }

    fwrite(lista_clientes, sizeof(Cliente), total_clientes, fp);
    fclose(fp);
}

/* Retorna a quantidade de clientes cadastrados */
int obter_total_clientes(void) {
    return total_clientes;
}

/* Retorna um ponteiro para o cliente pelo índice */
Cliente* obter_cliente_por_indice(int indice) {
    if (indice >= 0 && indice < total_clientes) {
        return &lista_clientes[indice];
    }
    return NULL;
}

/* Busca o índice do cliente a partir do código */
int buscar_indice_cliente_por_codigo(int codigo) {
    for (int i = 0; i < total_clientes; i++) {
        if (lista_clientes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

/* 
 * FUNCIONALIDADE RECURSIVA:
 * Busca de cliente por código utilizando recursão e ponteiros.
 * Caso base 1: n <= 0 -> cliente não encontrado (retorna NULL).
 * Caso base 2: elemento no índice n-1 possui o código desejado -> retorna &lista[n-1].
 * Passo recursivo: chama buscar_cliente_recursivo com n - 1.
 */
Cliente* buscar_cliente_recursivo(Cliente *lista, int n, int codigo) {
    if (n <= 0 || lista == NULL) {
        return NULL;
    }
    if (lista[n - 1].codigo == codigo) {
        return &lista[n - 1];
    }
    return buscar_cliente_recursivo(lista, n - 1, codigo);
}

/* Busca cliente por código e retorna um ponteiro para ele */
Cliente* buscar_cliente_por_codigo(int codigo) {
    return buscar_cliente_recursivo(lista_clientes, total_clientes, codigo);
}

/* Cadastra um novo cliente com validação de código único */
void cadastrar_cliente_menu(void) {
    if (total_clientes >= MAX_CLIENTES) {
        printf("\nErro: Limite máximo de clientes (%d) atingido!\n", MAX_CLIENTES);
        return;
    }

    Cliente novo;
    printf("\n========================================\n");
    printf("         NOVO CADASTRO DE CLIENTE       \n");
    printf("========================================\n");

    while (1) {
        novo.codigo = ler_inteiro("Código do cliente: ");
        if (novo.codigo <= 0) {
            printf("Erro: O código deve ser maior que zero.\n");
            continue;
        }
        if (buscar_indice_cliente_por_codigo(novo.codigo) != -1) {
            printf("Erro: Já existe um cliente com o código %d! Digite outro código.\n", novo.codigo);
            continue;
        }
        break;
    }

    while (1) {
        ler_string("Nome: ", novo.nome, sizeof(novo.nome));
        if (strlen(novo.nome) == 0) {
            printf("Erro: O nome não pode ser vazio.\n");
            continue;
        }
        break;
    }

    while (1) {
        ler_string("CPF (apenas dígitos ou formatado): ", novo.cpf, sizeof(novo.cpf));
        if (strlen(novo.cpf) == 0) {
            printf("Erro: O CPF não pode ser vazio.\n");
            continue;
        }
        break;
    }

    ler_string("Telefone: ", novo.telefone, sizeof(novo.telefone));
    ler_string("E-mail: ", novo.email, sizeof(novo.email));
    ler_string("Cidade: ", novo.cidade, sizeof(novo.cidade));

    lista_clientes[total_clientes] = novo;
    total_clientes++;

    salvar_clientes();
    printf("\nSucesso: Cliente '%s' cadastrado e salvo com sucesso!\n", novo.nome);
}

/* Exibe os dados formatados de um cliente */
static void imprimir_cliente(const Cliente *c) {
    printf("----------------------------------------\n");
    printf("Código  : %d\n", c->codigo);
    printf("Nome    : %s\n", c->nome);
    printf("CPF     : %s\n", c->cpf);
    printf("Telefone: %s\n", c->telefone[0] ? c->telefone : "Não informado");
    printf("E-mail  : %s\n", c->email[0] ? c->email : "Não informado");
    printf("Cidade  : %s\n", c->cidade[0] ? c->cidade : "Não informada");
}

/* Lista todos os clientes cadastrados */
void listar_clientes(void) {
    if (total_clientes == 0) {
        printf("\nNenhum cliente cadastrado no sistema.\n");
        return;
    }

    printf("\n========================================\n");
    printf("          LISTA DE CLIENTES (%d)        \n", total_clientes);
    printf("========================================\n");
    for (int i = 0; i < total_clientes; i++) {
        imprimir_cliente(&lista_clientes[i]);
    }
    printf("----------------------------------------\n");
}

/* Busca clientes por código, nome ou CPF */
void buscar_cliente_menu(void) {
    if (total_clientes == 0) {
        printf("\nNenhum cliente cadastrado para buscar.\n");
        return;
    }

    printf("\n--- BUSCAR CLIENTE ---\n");
    printf("1 - Buscar por Código\n");
    printf("2 - Buscar por Nome\n");
    printf("3 - Buscar por CPF\n");
    printf("0 - Voltar\n");
    int op = ler_inteiro("Escolha uma opção: ");

    if (op == 1) {
        int cod = ler_inteiro("Digite o código do cliente: ");
        Cliente *c = buscar_cliente_por_codigo(cod);
        if (c != NULL) {
            printf("\n--- CLIENTE ENCONTRADO ---\n");
            imprimir_cliente(c);
            printf("----------------------------------------\n");
        } else {
            printf("\nNenhum cliente encontrado com o código %d.\n", cod);
        }
    } else if (op == 2) {
        char termo[100];
        ler_string("Digite o nome (ou parte do nome): ", termo, sizeof(termo));
        int encontrados = 0;
        printf("\n--- RESULTADOS DA BUSCA POR NOME ---\n");
        for (int i = 0; i < total_clientes; i++) {
            if (contem_substring_insensivel(lista_clientes[i].nome, termo)) {
                imprimir_cliente(&lista_clientes[i]);
                encontrados++;
            }
        }
        if (encontrados == 0) {
            printf("Nenhum cliente encontrado contendo '%s'.\n", termo);
        } else {
            printf("----------------------------------------\n");
            printf("Total de clientes encontrados: %d\n", encontrados);
        }
    } else if (op == 3) {
        char cpf_busca[30];
        ler_string("Digite o CPF (ou parte do CPF): ", cpf_busca, sizeof(cpf_busca));
        int encontrados = 0;
        printf("\n--- RESULTADOS DA BUSCA POR CPF ---\n");
        for (int i = 0; i < total_clientes; i++) {
            if (contem_substring_insensivel(lista_clientes[i].cpf, cpf_busca)) {
                imprimir_cliente(&lista_clientes[i]);
                encontrados++;
            }
        }
        if (encontrados == 0) {
            printf("Nenhum cliente encontrado contendo CPF '%s'.\n", cpf_busca);
        } else {
            printf("----------------------------------------\n");
            printf("Total de clientes encontrados: %d\n", encontrados);
        }
    }
}

/* Altera dados de um cliente existente */
void alterar_cliente(void) {
    if (total_clientes == 0) {
        printf("\nNenhum cliente cadastrado para alterar.\n");
        return;
    }

    int cod = ler_inteiro("\nDigite o código do cliente que deseja alterar: ");
    int indice = buscar_indice_cliente_por_codigo(cod);

    if (indice == -1) {
        printf("\nCliente com código %d não foi encontrado!\n", cod);
        return;
    }

    Cliente *c = &lista_clientes[indice];
    printf("\n====== ALTERAR CLIENTE (Código %d) ======\n", c->codigo);
    printf("(Pressione Enter para manter o valor atual)\n");

    char buffer[100];

    printf("Nome atual: %s\n", c->nome);
    ler_string("Novo nome: ", buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strncpy(c->nome, buffer, sizeof(c->nome) - 1);
        c->nome[sizeof(c->nome) - 1] = '\0';
    }

    printf("CPF atual: %s\n", c->cpf);
    ler_string("Novo CPF: ", buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strncpy(c->cpf, buffer, sizeof(c->cpf) - 1);
        c->cpf[sizeof(c->cpf) - 1] = '\0';
    }

    printf("Telefone atual: %s\n", c->telefone);
    ler_string("Novo telefone: ", buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strncpy(c->telefone, buffer, sizeof(c->telefone) - 1);
        c->telefone[sizeof(c->telefone) - 1] = '\0';
    }

    printf("E-mail atual: %s\n", c->email);
    ler_string("Novo e-mail: ", buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strncpy(c->email, buffer, sizeof(c->email) - 1);
        c->email[sizeof(c->email) - 1] = '\0';
    }

    printf("Cidade atual: %s\n", c->cidade);
    ler_string("Nova cidade: ", buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strncpy(c->cidade, buffer, sizeof(c->cidade) - 1);
        c->cidade[sizeof(c->cidade) - 1] = '\0';
    }

    salvar_clientes();
    printf("\nSucesso: Cadastro do cliente atualizado e salvo!\n");
}

/* Exclui um cliente da base */
void excluir_cliente(void) {
    if (total_clientes == 0) {
        printf("\nNenhum cliente cadastrado para excluir.\n");
        return;
    }

    int cod = ler_inteiro("\nDigite o código do cliente que deseja excluir: ");
    int indice = buscar_indice_cliente_por_codigo(cod);

    if (indice == -1) {
        printf("\nCliente com código %d não foi encontrado!\n", cod);
        return;
    }

    printf("\nCliente selecionado: %s (CPF: %s)\n", lista_clientes[indice].nome, lista_clientes[indice].cpf);
    char conf[10];
    ler_string("Tem certeza de que deseja excluir este cliente? (s/n): ", conf, sizeof(conf));
    if (conf[0] != 's' && conf[0] != 'S') {
        printf("Operação de exclusão cancelada.\n");
        return;
    }

    for (int i = indice; i < total_clientes - 1; i++) {
        lista_clientes[i] = lista_clientes[i + 1];
    }
    total_clientes--;

    salvar_clientes();
    printf("\nSucesso: Cliente excluído com sucesso!\n");
}