#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "util.h"

#define ARQUIVO_PRODUTOS "produtos.dat"

static Produto lista_produtos[MAX_PRODUTOS];
static int total_produtos = 0;

/* Carrega os produtos do arquivo binário */
void carregar_produtos(void) {
    FILE *fp = fopen(ARQUIVO_PRODUTOS, "rb");
    if (fp == NULL) {
        total_produtos = 0;
        return;
    }

    total_produtos = (int)fread(lista_produtos, sizeof(Produto), MAX_PRODUTOS, fp);
    fclose(fp);
}

/* Salva os produtos no arquivo binário */
void salvar_produtos(void) {
    FILE *fp = fopen(ARQUIVO_PRODUTOS, "wb");
    if (fp == NULL) {
        printf("\nErro ao abrir o arquivo '%s' para gravação!\n", ARQUIVO_PRODUTOS);
        return;
    }

    fwrite(lista_produtos, sizeof(Produto), total_produtos, fp);
    fclose(fp);
}

/* Retorna a quantidade de produtos cadastrados */
int obter_total_produtos(void) {
    return total_produtos;
}

/* Retorna um ponteiro para o produto pelo índice */
Produto* obter_produto_por_indice(int indice) {
    if (indice >= 0 && indice < total_produtos) {
        return &lista_produtos[indice];
    }
    return NULL;
}

/* Busca o índice do produto a partir do código */
int buscar_indice_produto_por_codigo(int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

/* Retorna um ponteiro para o produto com base no código */
Produto* buscar_produto_por_codigo(int codigo) {
    int idx = buscar_indice_produto_por_codigo(codigo);
    if (idx != -1) {
        return &lista_produtos[idx];
    }
    return NULL;
}

/* Atualiza o estoque do produto decrementando a quantidade vendida */
int atualizar_estoque_produto(int codigo, int qtd_subtrair) {
    Produto *p = buscar_produto_por_codigo(codigo);
    if (p == NULL) {
        return 0;
    }
    if (p->quantidade_em_estoque < qtd_subtrair) {
        return 0;
    }
    p->quantidade_em_estoque -= qtd_subtrair;
    salvar_produtos();
    return 1;
}

/*
 * FUNCIONALIDADE RECURSIVA:
 * Calcula o valor total financeiro em estoque de forma recursiva.
 * Caso base: se n <= 0, retorna 0.0f.
 * Passo recursivo: calcula o valor do elemento (n-1) e soma com a chamada para os n-1 restantes.
 */
float calcular_valor_total_estoque_recursivo(const Produto *lista, int n) {
    if (n <= 0 || lista == NULL) {
        return 0.0f;
    }
    float valor_atual = lista[n - 1].preco * (float)lista[n - 1].quantidade_em_estoque;
    return valor_atual + calcular_valor_total_estoque_recursivo(lista, n - 1);
}

/* Wrapper que aciona o cálculo recursivo do estoque */
float obter_valor_total_estoque(void) {
    return calcular_valor_total_estoque_recursivo(lista_produtos, total_produtos);
}

/* Imprime as informações de um produto */
static void imprimir_produto(const Produto *p) {
    printf("----------------------------------------\n");
    printf("Código    : %d\n", p->codigo);
    printf("Nome      : %s\n", p->nome);
    printf("Categoria : %s\n", p->categoria);
    printf("Preço     : R$ %.2f\n", p->preco);
    printf("Estoque   : %d unidades\n", p->quantidade_em_estoque);
    printf("Total Est.: R$ %.2f\n", p->preco * (float)p->quantidade_em_estoque);
}

/* Cadastra um novo produto com todas as validações obrigatórias */
void cadastrar_produto_menu(void) {
    if (total_produtos >= MAX_PRODUTOS) {
        printf("\nErro: Limite máximo de produtos (%d) atingido!\n", MAX_PRODUTOS);
        return;
    }

    Produto novo;
    printf("\n========================================\n");
    printf("         NOVO CADASTRO DE PRODUTO       \n");
    printf("========================================\n");

    /* Validação do código: deve ser > 0 e único */
    while (1) {
        novo.codigo = ler_inteiro("Código do produto: ");
        if (novo.codigo <= 0) {
            printf("Erro: O código deve ser maior que zero.\n");
            continue;
        }
        if (buscar_indice_produto_por_codigo(novo.codigo) != -1) {
            printf("Erro: Já existe um produto cadastrado com o código %d! Digite outro código.\n", novo.codigo);
            continue;
        }
        break;
    }

    /* Validação do nome */
    while (1) {
        ler_string("Nome do produto: ", novo.nome, sizeof(novo.nome));
        if (strlen(novo.nome) == 0) {
            printf("Erro: O nome não pode ser vazio.\n");
            continue;
        }
        break;
    }

    /* Categoria */
    while (1) {
        ler_string("Categoria: ", novo.categoria, sizeof(novo.categoria));
        if (strlen(novo.categoria) == 0) {
            printf("Erro: A categoria não pode ser vazia.\n");
            continue;
        }
        break;
    }

    /* Validação de preço: não permitir preço negativo */
    while (1) {
        novo.preco = ler_float("Preço (R$): ");
        if (novo.preco < 0.0f) {
            printf("Erro: O preço não pode ser negativo.\n");
            continue;
        }
        break;
    }

    /* Validação de estoque: não permitir quantidade negativa */
    while (1) {
        novo.quantidade_em_estoque = ler_inteiro("Quantidade inicial em estoque: ");
        if (novo.quantidade_em_estoque < 0) {
            printf("Erro: A quantidade em estoque não pode ser negativa.\n");
            continue;
        }
        break;
    }

    lista_produtos[total_produtos] = novo;
    total_produtos++;

    salvar_produtos();
    printf("\nSucesso: Produto '%s' cadastrado e salvo com sucesso!\n", novo.nome);
}

/* Lista todos os produtos */
void listar_produtos(void) {
    if (total_produtos == 0) {
        printf("\nNenhum produto cadastrado no sistema.\n");
        return;
    }

    printf("\n=======================================================\n");
    printf("               LISTA DE PRODUTOS (%d)                  \n", total_produtos);
    printf("=======================================================\n");
    for (int i = 0; i < total_produtos; i++) {
        imprimir_produto(&lista_produtos[i]);
    }
    printf("-------------------------------------------------------\n");
}

/* Consulta estoque resumida */
void consultar_estoque(void) {
    if (total_produtos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n=======================================================================\n");
    printf("                       CONSULTA GERAL DE ESTOQUE                       \n");
    printf("=======================================================================\n");
    printf("%-8s | %-30s | %-12s | %-10s | %-12s\n", "Código", "Nome", "Preço (R$)", "Estoque", "Total (R$)");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < total_produtos; i++) {
        float subtotal = lista_produtos[i].preco * (float)lista_produtos[i].quantidade_em_estoque;
        printf("%-8d | %-30.30s | R$ %9.2f | %10d | R$ %9.2f\n",
               lista_produtos[i].codigo,
               lista_produtos[i].nome,
               lista_produtos[i].preco,
               lista_produtos[i].quantidade_em_estoque,
               subtotal);
    }
    printf("-----------------------------------------------------------------------\n");
    float valor_total = calcular_valor_total_estoque_recursivo(lista_produtos, total_produtos);
    printf("Valor Total Estimado do Estoque: R$ %.2f\n", valor_total);
    printf("-----------------------------------------------------------------------\n");
}

/* Identifica produtos com estoque baixo */
void identificar_estoque_baixo(void) {
    if (total_produtos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- IDENTIFICAR PRODUTOS COM ESTOQUE BAIXO ---\n");
    int limite = ler_inteiro("Defina o limite de estoque para alerta (padrão: 5): ");
    if (limite < 0) {
        limite = 5;
    }

    int encontrados = 0;
    printf("\n=======================================================================\n");
    printf("           PRODUTOS COM ESTOQUE BAIXO (Estoque <= %d)                  \n", limite);
    printf("=======================================================================\n");

    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].quantidade_em_estoque <= limite) {
            imprimir_produto(&lista_produtos[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum produto com estoque menor ou igual a %d unidades.\n", limite);
    } else {
        printf("----------------------------------------\n");
        printf("Total de itens em alerta: %d\n", encontrados);
    }
}

/* Menu de busca de produto */
void buscar_produto_menu(void) {
    if (total_produtos == 0) {
        printf("\nNenhum produto cadastrado para buscar.\n");
        return;
    }

    printf("\n--- BUSCAR PRODUTO ---\n");
    printf("1 - Buscar por Código\n");
    printf("2 - Buscar por Nome\n");
    printf("3 - Buscar por Categoria\n");
    printf("0 - Voltar\n");
    int op = ler_inteiro("Escolha uma opção: ");

    if (op == 1) {
        int cod = ler_inteiro("Digite o código do produto: ");
        Produto *p = buscar_produto_por_codigo(cod);
        if (p != NULL) {
            printf("\n--- PRODUTO ENCONTRADO ---\n");
            imprimir_produto(p);
            printf("----------------------------------------\n");
        } else {
            printf("\nNenhum produto encontrado com o código %d.\n", cod);
        }
    } else if (op == 2) {
        char termo[100];
        ler_string("Digite o nome (ou parte do nome): ", termo, sizeof(termo));
        int encontrados = 0;
        printf("\n--- RESULTADOS DA BUSCA POR NOME ---\n");
        for (int i = 0; i < total_produtos; i++) {
            if (contem_substring_insensivel(lista_produtos[i].nome, termo)) {
                imprimir_produto(&lista_produtos[i]);
                encontrados++;
            }
        }
        if (encontrados == 0) {
            printf("Nenhum produto encontrado com o nome contendo '%s'.\n", termo);
        } else {
            printf("----------------------------------------\n");
            printf("Total de produtos encontrados: %d\n", encontrados);
        }
    } else if (op == 3) {
        char cat[50];
        ler_string("Digite a categoria: ", cat, sizeof(cat));
        int encontrados = 0;
        printf("\n--- RESULTADOS DA BUSCA POR CATEGORIA ---\n");
        for (int i = 0; i < total_produtos; i++) {
            if (contem_substring_insensivel(lista_produtos[i].categoria, cat)) {
                imprimir_produto(&lista_produtos[i]);
                encontrados++;
            }
        }
        if (encontrados == 0) {
            printf("Nenhum produto encontrado na categoria '%s'.\n", cat);
        } else {
            printf("----------------------------------------\n");
            printf("Total de produtos encontrados: %d\n", encontrados);
        }
    }
}

/* Altera dados de um produto existente */
void alterar_produto(void) {
    if (total_produtos == 0) {
        printf("\nNenhum produto cadastrado para alterar.\n");
        return;
    }

    int cod = ler_inteiro("\nDigite o código do produto que deseja alterar: ");
    int indice = buscar_indice_produto_por_codigo(cod);

    if (indice == -1) {
        printf("\nProduto com o código %d não foi encontrado!\n", cod);
        return;
    }

    Produto *p = &lista_produtos[indice];
    printf("\n====== ALTERAR PRODUTO (Código %d) ======\n", p->codigo);
    printf("(Pressione Enter ou digite valor negativo para manter o atual)\n");

    char buffer[100];

    printf("Nome atual: %s\n", p->nome);
    ler_string("Novo nome: ", buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strncpy(p->nome, buffer, sizeof(p->nome) - 1);
        p->nome[sizeof(p->nome) - 1] = '\0';
    }

    printf("Categoria atual: %s\n", p->categoria);
    ler_string("Nova categoria: ", buffer, sizeof(buffer));
    if (strlen(buffer) > 0) {
        strncpy(p->categoria, buffer, sizeof(p->categoria) - 1);
        p->categoria[sizeof(p->categoria) - 1] = '\0';
    }

    printf("Preço atual: R$ %.2f\n", p->preco);
    float novo_preco = ler_float("Novo preço (digite -1 para manter o atual): ");
    if (novo_preco >= 0.0f) {
        p->preco = novo_preco;
    }

    printf("Estoque atual: %d unidades\n", p->quantidade_em_estoque);
    int novo_estoque = ler_inteiro("Novo estoque (digite -1 para manter o atual): ");
    if (novo_estoque >= 0) {
        p->quantidade_em_estoque = novo_estoque;
    }

    salvar_produtos();
    printf("\nSucesso: Produto atualizado e salvo!\n");
}

/* Exclui um produto */
void excluir_produto(void) {
    if (total_produtos == 0) {
        printf("\nNenhum produto cadastrado para excluir.\n");
        return;
    }

    int cod = ler_inteiro("\nDigite o código do produto que deseja excluir: ");
    int indice = buscar_indice_produto_por_codigo(cod);

    if (indice == -1) {
        printf("\nProduto com código %d não foi encontrado!\n", cod);
        return;
    }

    printf("\nProduto selecionado: %s (Estoque: %d, Preço: R$ %.2f)\n",
           lista_produtos[indice].nome,
           lista_produtos[indice].quantidade_em_estoque,
           lista_produtos[indice].preco);

    char conf[10];
    ler_string("Tem certeza de que deseja excluir este produto? (s/n): ", conf, sizeof(conf));
    if (conf[0] != 's' && conf[0] != 'S') {
        printf("Operação de exclusão cancelada.\n");
        return;
    }

    for (int i = indice; i < total_produtos - 1; i++) {
        lista_produtos[i] = lista_produtos[i + 1];
    }
    total_produtos--;

    salvar_produtos();
    printf("\nSucesso: Produto excluído com sucesso!\n");
}