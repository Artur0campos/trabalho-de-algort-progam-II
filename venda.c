#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "venda.h"
#include "util.h"

#define ARQUIVO_VENDAS "vendas.dat"

static Venda lista_vendas[MAX_VENDAS];
static int total_vendas = 0;

/* Carrega as vendas do arquivo binário */
void carregar_vendas(void) {
    FILE *fp = fopen(ARQUIVO_VENDAS, "rb");
    if (fp == NULL) {
        total_vendas = 0;
        return;
    }

    total_vendas = (int)fread(lista_vendas, sizeof(Venda), MAX_VENDAS, fp);
    fclose(fp);
}

/* Salva as vendas no arquivo binário */
void salvar_vendas(void) {
    FILE *fp = fopen(ARQUIVO_VENDAS, "wb");
    if (fp == NULL) {
        printf("\nErro ao abrir o arquivo '%s' para gravação!\n", ARQUIVO_VENDAS);
        return;
    }

    fwrite(lista_vendas, sizeof(Venda), total_vendas, fp);
    fclose(fp);
}

/* Retorna a quantidade total de vendas realizadas */
int obter_total_vendas(void) {
    return total_vendas;
}

/* Retorna um ponteiro para a venda pelo índice */
Venda* obter_venda_por_indice(int indice) {
    if (indice >= 0 && indice < total_vendas) {
        return &lista_vendas[indice];
    }
    return NULL;
}

/* Busca venda por código e retorna ponteiro */
Venda* buscar_venda_por_codigo(int cod_venda) {
    for (int i = 0; i < total_vendas; i++) {
        if (lista_vendas[i].cod_venda == cod_venda) {
            return &lista_vendas[i];
        }
    }
    return NULL;
}

/*
 * FUNCIONALIDADE RECURSIVA:
 * Calcula o valor total dos itens de uma venda recursivamente.
 * Caso base: se n <= 0, o somatório é 0.0f.
 * Passo recursivo: soma o subtotal do item (n-1) com a chamada recursiva para n-1 itens.
 */
float calcular_total_venda_recursivo(const ItemVenda *itens, int n) {
    if (n <= 0 || itens == NULL) {
        return 0.0f;
    }
    return itens[n - 1].subtotal + calcular_total_venda_recursivo(itens, n - 1);
}

/* Imprime os detalhes completos de uma venda */
static void imprimir_venda(const Venda *v) {
    Cliente *c = buscar_cliente_por_codigo(v->cod_cliente);

    printf("=======================================================================\n");
    printf(" VENDA #%d | Data: %02d/%02d/%04d\n", v->cod_venda, v->data.dia, v->data.mes, v->data.ano);
    printf(" Cliente: Código %d - %s\n", v->cod_cliente, c != NULL ? c->nome : "Não encontrado");
    printf("-----------------------------------------------------------------------\n");
    printf("%-6s | %-28s | %-6s | %-12s | %-12s\n", "Item", "Produto", "Qtd", "Preço Unit.", "Subtotal");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < v->total_itens; i++) {
        printf("%-6d | %-28.28s | %-6d | R$ %9.2f | R$ %9.2f\n",
               i + 1,
               v->itens[i].nome_produto,
               v->itens[i].quantidade,
               v->itens[i].preco_unitario,
               v->itens[i].subtotal);
    }
    printf("-----------------------------------------------------------------------\n");
    printf(" VALOR TOTAL DA VENDA: R$ %.2f\n", v->valor_total);
    printf("=======================================================================\n");
}

/* Registra uma nova venda no sistema */
void registrar_venda(void) {
    if (total_vendas >= MAX_VENDAS) {
        printf("\nErro: Limite máximo de vendas (%d) atingido!\n", MAX_VENDAS);
        return;
    }

    if (obter_total_clientes() == 0) {
        printf("\nErro: Nenhum cliente cadastrado! Cadastre clientes antes de realizar uma venda.\n");
        return;
    }

    if (obter_total_produtos() == 0) {
        printf("\nErro: Nenhum produto cadastrado! Cadastre produtos antes de realizar uma venda.\n");
        return;
    }

    Venda nova_venda;
    nova_venda.total_itens = 0;
    nova_venda.valor_total = 0.0f;

    printf("\n========================================\n");
    printf("            REGISTRAR NOVA VENDA        \n");
    printf("========================================\n");

    /* 1. Código da Venda (único) */
    while (1) {
        nova_venda.cod_venda = ler_inteiro("Código da venda: ");
        if (nova_venda.cod_venda <= 0) {
            printf("Erro: O código da venda deve ser maior que zero.\n");
            continue;
        }
        if (buscar_venda_por_codigo(nova_venda.cod_venda) != NULL) {
            printf("Erro: Já existe uma venda registrada com o código %d! Digite outro código.\n", nova_venda.cod_venda);
            continue;
        }
        break;
    }

    /* 2. Código do Cliente com validação de existência */
    Cliente *cliente_selecionado = NULL;
    while (1) {
        nova_venda.cod_cliente = ler_inteiro("Código do cliente: ");
        cliente_selecionado = buscar_cliente_por_codigo(nova_venda.cod_cliente);
        if (cliente_selecionado == NULL) {
            printf("Erro: Cliente com código %d não foi encontrado! Verifique os clientes cadastrados.\n", nova_venda.cod_cliente);
            char tentar[10];
            ler_string("Deseja tentar outro código? (s/n): ", tentar, sizeof(tentar));
            if (tentar[0] != 's' && tentar[0] != 'S') {
                printf("Operação de venda cancelada.\n");
                return;
            }
            continue;
        }
        printf("Cliente selecionado: %s (CPF: %s)\n", cliente_selecionado->nome, cliente_selecionado->cpf);
        break;
    }

    /* 3. Data da Venda */
    while (1) {
        printf("Data da venda:\n");
        nova_venda.data.dia = ler_inteiro("  Dia (1-31): ");
        nova_venda.data.mes = ler_inteiro("  Mês (1-12): ");
        nova_venda.data.ano = ler_inteiro("  Ano (ex: 2026): ");

        if (!validar_data(nova_venda.data.dia, nova_venda.data.mes, nova_venda.data.ano)) {
            printf("Erro: Data inválida! Por favor, insira uma data real.\n");
            continue;
        }
        break;
    }

    /* 4. Inclusão dos itens da venda */
    printf("\n--- Adicionar Produtos à Venda ---\n");
    while (nova_venda.total_itens < MAX_ITENS_VENDA) {
        int cod_prod = ler_inteiro("\nCódigo do produto a adicionar (ou 0 para finalizar produtos): ");
        if (cod_prod == 0) {
            if (nova_venda.total_itens == 0) {
                printf("Atenção: A venda precisa conter pelo menos um produto!\n");
                continue;
            }
            break;
        }

        Produto *p = buscar_produto_por_codigo(cod_prod);
        if (p == NULL) {
            printf("Erro: Produto com código %d não encontrado!\n", cod_prod);
            continue;
        }

        /* Quantidade já adicionada deste mesmo produto nesta venda */
        int qtd_ja_adicionada = 0;
        int item_existente_idx = -1;
        for (int i = 0; i < nova_venda.total_itens; i++) {
            if (nova_venda.itens[i].cod_produto == cod_prod) {
                qtd_ja_adicionada += nova_venda.itens[i].quantidade;
                item_existente_idx = i;
            }
        }

        int estoque_disponivel = p->quantidade_em_estoque - qtd_ja_adicionada;
        printf("Produto: %s | Categoria: %s | Preço: R$ %.2f | Estoque disponível: %d\n",
               p->nome, p->categoria, p->preco, estoque_disponivel);

        if (estoque_disponivel <= 0) {
            printf("Erro: Este produto está sem estoque disponível para venda!\n");
            continue;
        }

        int qtd;
        while (1) {
            qtd = ler_inteiro("Quantidade a comprar: ");
            if (qtd <= 0) {
                printf("Erro: A quantidade deve ser maior que zero.\n");
                continue;
            }
            if (qtd > estoque_disponivel) {
                printf("Erro: Quantidade solicitada (%d) maior que o estoque disponível (%d)!\n", qtd, estoque_disponivel);
                continue;
            }
            break;
        }

        if (item_existente_idx != -1) {
            nova_venda.itens[item_existente_idx].quantidade += qtd;
            nova_venda.itens[item_existente_idx].subtotal = nova_venda.itens[item_existente_idx].quantidade * p->preco;
            printf("Item atualizado na venda! Subtotal do item: R$ %.2f\n", nova_venda.itens[item_existente_idx].subtotal);
        } else {
            ItemVenda item;
            item.cod_produto = p->codigo;
            strncpy(item.nome_produto, p->nome, sizeof(item.nome_produto) - 1);
            item.nome_produto[sizeof(item.nome_produto) - 1] = '\0';
            item.quantidade = qtd;
            item.preco_unitario = p->preco;
            item.subtotal = (float)qtd * p->preco;

            nova_venda.itens[nova_venda.total_itens] = item;
            nova_venda.total_itens++;
            printf("Item adicionado! Subtotal: R$ %.2f\n", item.subtotal);
        }

        char mais[10];
        ler_string("Deseja adicionar mais algum produto? (s/n): ", mais, sizeof(mais));
        if (mais[0] != 's' && mais[0] != 'S') {
            break;
        }
    }

    /* 5. Cálculo do total recursivamente (requisito obrigatório) */
    nova_venda.valor_total = calcular_total_venda_recursivo(nova_venda.itens, nova_venda.total_itens);

    /* 6. Atualização do estoque de cada produto */
    for (int i = 0; i < nova_venda.total_itens; i++) {
        atualizar_estoque_produto(nova_venda.itens[i].cod_produto, nova_venda.itens[i].quantidade);
    }

    /* 7. Registro e persistência da venda */
    lista_vendas[total_vendas] = nova_venda;
    total_vendas++;
    salvar_vendas();

    printf("\n>>> VENDA REGISTRADA COM SUCESSO! <<<\n");
    imprimir_venda(&nova_venda);
}

/* Lista todas as vendas registradas */
void listar_vendas(void) {
    if (total_vendas == 0) {
        printf("\nNenhuma venda registrada no sistema.\n");
        return;
    }

    printf("\n=======================================================================\n");
    printf("                     LISTA DE VENDAS REGISTRADAS (%d)                   \n", total_vendas);
    printf("=======================================================================\n");
    for (int i = 0; i < total_vendas; i++) {
        imprimir_venda(&lista_vendas[i]);
    }
}

/* Busca venda por código ou por cliente */
void buscar_venda(void) {
    if (total_vendas == 0) {
        printf("\nNenhuma venda registrada para consultar.\n");
        return;
    }

    printf("\n--- BUSCAR VENDA ---\n");
    printf("1 - Buscar por Código da Venda\n");
    printf("2 - Buscar Vendas por Código do Cliente\n");
    printf("0 - Voltar\n");
    int op = ler_inteiro("Escolha uma opção: ");

    if (op == 1) {
        int cod = ler_inteiro("Digite o código da venda: ");
        Venda *v = buscar_venda_por_codigo(cod);
        if (v != NULL) {
            imprimir_venda(v);
        } else {
            printf("\nVenda com código %d não foi encontrada.\n", cod);
        }
    } else if (op == 2) {
        int cod_cli = ler_inteiro("Digite o código do cliente: ");
        int encontradas = 0;
        float total_cliente = 0.0f;

        printf("\n=======================================================================\n");
        printf("                  VENDAS DO CLIENTE CÓDIGO %d                          \n", cod_cli);
        printf("=======================================================================\n");
        for (int i = 0; i < total_vendas; i++) {
            if (lista_vendas[i].cod_cliente == cod_cli) {
                imprimir_venda(&lista_vendas[i]);
                encontradas++;
                total_cliente += lista_vendas[i].valor_total;
            }
        }
        if (encontradas == 0) {
            printf("Nenhuma venda registrada para o cliente com código %d.\n", cod_cli);
        } else {
            printf("\nResumo: %d venda(s) encontrada(s) | Total acumulado: R$ %.2f\n", encontradas, total_cliente);
        }
    }
}