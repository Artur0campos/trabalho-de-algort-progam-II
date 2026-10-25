#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorios.h"
#include "cliente.h"
#include "produto.h"
#include "venda.h"
#include "util.h"

/* Exibe o painel consolidado com todos os indicadores do negócio */
void relatorio_painel_geral(void) {
    int total_cli = obter_total_clientes();
    int total_prod = obter_total_produtos();
    int total_ven = obter_total_vendas();
    float valor_estoque = obter_valor_total_estoque();

    float faturamento_total = 0.0f;
    for (int i = 0; i < total_ven; i++) {
        Venda *v = obter_venda_por_indice(i);
        if (v != NULL) {
            faturamento_total += v->valor_total;
        }
    }

    printf("\n=======================================================================\n");
    printf("              PAINEL GERAL DE INDICADORES EMPRESARIAIS                 \n");
    printf("=======================================================================\n");
    printf(" 1. Total de Clientes Cadastrados : %d\n", total_cli);
    printf(" 2. Total de Produtos Cadastrados : %d\n", total_prod);
    printf(" 3. Valor Total em Estoque        : R$ %.2f\n", valor_estoque);
    printf(" 4. Total de Vendas Realizadas    : %d\n", total_ven);
    printf(" 5. Faturamento Total Vendido     : R$ %.2f\n", faturamento_total);
    if (total_ven > 0) {
        printf(" 6. Ticket Médio por Venda        : R$ %.2f\n", faturamento_total / (float)total_ven);
    }
    printf("=======================================================================\n");
}

/* Identifica e exibe o produto mais vendido em quantidade */
void relatorio_produto_mais_vendido(void) {
    int total_ven = obter_total_vendas();
    int total_prod = obter_total_produtos();

    if (total_ven == 0) {
        printf("\nNenhuma venda registrada ainda para calcular o produto mais vendido.\n");
        return;
    }

    if (total_prod == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    /* Estrutura auxiliar para acumular vendas por produto */
    typedef struct {
        int cod_produto;
        char nome[100];
        int total_quantidade;
        float total_faturado;
    } AcumuladorProduto;

    AcumuladorProduto acumuladores[MAX_PRODUTOS];
    int total_acumulados = 0;

    for (int v_idx = 0; v_idx < total_ven; v_idx++) {
        Venda *v = obter_venda_por_indice(v_idx);
        if (v == NULL) continue;

        for (int i = 0; i < v->total_itens; i++) {
            int cod = v->itens[i].cod_produto;
            int encontrado = -1;

            for (int k = 0; k < total_acumulados; k++) {
                if (acumuladores[k].cod_produto == cod) {
                    encontrado = k;
                    break;
                }
            }

            if (encontrado != -1) {
                acumuladores[encontrado].total_quantidade += v->itens[i].quantidade;
                acumuladores[encontrado].total_faturado += v->itens[i].subtotal;
            } else if (total_acumulados < MAX_PRODUTOS) {
                acumuladores[total_acumulados].cod_produto = cod;
                strncpy(acumuladores[total_acumulados].nome, v->itens[i].nome_produto, sizeof(acumuladores[total_acumulados].nome) - 1);
                acumuladores[total_acumulados].nome[sizeof(acumuladores[total_acumulados].nome) - 1] = '\0';
                acumuladores[total_acumulados].total_quantidade = v->itens[i].quantidade;
                acumuladores[total_acumulados].total_faturado = v->itens[i].subtotal;
                total_acumulados++;
            }
        }
    }

    if (total_acumulados == 0) {
        printf("\nNenhum item comercializado até o momento.\n");
        return;
    }

    /* Encontra o índice com maior quantidade */
    int maior_idx = 0;
    for (int i = 1; i < total_acumulados; i++) {
        if (acumuladores[i].total_quantidade > acumuladores[maior_idx].total_quantidade) {
            maior_idx = i;
        }
    }

    printf("\n=======================================================================\n");
    printf("                         PRODUTO MAIS VENDIDO                          \n");
    printf("=======================================================================\n");
    printf(" Código do Produto   : %d\n", acumuladores[maior_idx].cod_produto);
    printf(" Nome do Produto     : %s\n", acumuladores[maior_idx].nome);
    printf(" Quantidade Vendida  : %d unidades\n", acumuladores[maior_idx].total_quantidade);
    printf(" Faturamento Gerado  : R$ %.2f\n", acumuladores[maior_idx].total_faturado);
    printf("=======================================================================\n");
}

/* Identifica o cliente com o maior volume financeiro de compras */
void relatorio_cliente_maior_volume(void) {
    int total_ven = obter_total_vendas();
    int total_cli = obter_total_clientes();

    if (total_ven == 0) {
        printf("\nNenhuma venda registrada ainda para calcular o melhor cliente.\n");
        return;
    }

    if (total_cli == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }

    typedef struct {
        int cod_cliente;
        int qtd_compras;
        float total_gasto;
    } AcumuladorCliente;

    AcumuladorCliente acumuladores[MAX_CLIENTES];
    int total_acumulados = 0;

    for (int v_idx = 0; v_idx < total_ven; v_idx++) {
        Venda *v = obter_venda_por_indice(v_idx);
        if (v == NULL) continue;

        int cod = v->cod_cliente;
        int encontrado = -1;

        for (int k = 0; k < total_acumulados; k++) {
            if (acumuladores[k].cod_cliente == cod) {
                encontrado = k;
                break;
            }
        }

        if (encontrado != -1) {
            acumuladores[encontrado].qtd_compras++;
            acumuladores[encontrado].total_gasto += v->valor_total;
        } else if (total_acumulados < MAX_CLIENTES) {
            acumuladores[total_acumulados].cod_cliente = cod;
            acumuladores[total_acumulados].qtd_compras = 1;
            acumuladores[total_acumulados].total_gasto = v->valor_total;
            total_acumulados++;
        }
    }

    if (total_acumulados == 0) {
        printf("\nNenhuma compra identificada.\n");
        return;
    }

    /* Encontra o cliente com maior valor total de compras */
    int maior_idx = 0;
    for (int i = 1; i < total_acumulados; i++) {
        if (acumuladores[i].total_gasto > acumuladores[maior_idx].total_gasto) {
            maior_idx = i;
        }
    }

    Cliente *cli = buscar_cliente_por_codigo(acumuladores[maior_idx].cod_cliente);

    printf("\n=======================================================================\n");
    printf("                CLIENTE COM MAIOR VOLUME DE COMPRAS                    \n");
    printf("=======================================================================\n");
    printf(" Código do Cliente    : %d\n", acumuladores[maior_idx].cod_cliente);
    printf(" Nome do Cliente      : %s\n", cli != NULL ? cli->nome : "Não encontrado");
    printf(" CPF                  : %s\n", cli != NULL ? cli->cpf : "Não informado");
    printf(" Quantidade de Vendas : %d compras realizadas\n", acumuladores[maior_idx].qtd_compras);
    printf(" Valor Total Gasto    : R$ %.2f\n", acumuladores[maior_idx].total_gasto);
    printf("=======================================================================\n");
}

/* Menu de Consultas e Relatórios */
void menu_consultas_relatorios(void) {
    while (1) {
        printf("\n========================================\n");
        printf("         CONSULTAS E RELATÓRIOS         \n");
        printf("========================================\n");
        printf("1 - Relatório Geral de Estoque\n");
        printf("2 - Produtos com Estoque Baixo\n");
        printf("3 - Relatório Geral de Vendas\n");
        printf("4 - Histórico de Vendas por Cliente\n");
        printf("0 - Voltar ao Menu Principal\n");

        int op = ler_inteiro("Escolha uma opção: ");

        switch (op) {
            case 1:
                consultar_estoque();
                break;
            case 2:
                identificar_estoque_baixo();
                break;
            case 3:
                listar_vendas();
                break;
            case 4: {
                int cod = ler_inteiro("\nDigite o código do cliente: ");
                int total_ven = obter_total_vendas();
                int count = 0;
                float soma = 0.0f;
                Cliente *c = buscar_cliente_por_codigo(cod);
                if (c == NULL) {
                    printf("\nCliente com código %d não encontrado.\n", cod);
                    break;
                }
                printf("\n=======================================================================\n");
                printf(" HISTÓRICO DE COMPRAS DO CLIENTE: %s (CPF: %s)\n", c->nome, c->cpf);
                printf("=======================================================================\n");
                for (int i = 0; i < total_ven; i++) {
                    Venda *v = obter_venda_por_indice(i);
                    if (v != NULL && v->cod_cliente == cod) {
                        count++;
                        soma += v->valor_total;
                        printf("Venda #%d | Data: %02d/%02d/%04d | Itens: %d | Total: R$ %.2f\n",
                               v->cod_venda, v->data.dia, v->data.mes, v->data.ano, v->total_itens, v->valor_total);
                    }
                }
                if (count == 0) {
                    printf("Nenhuma compra registrada para este cliente.\n");
                } else {
                    printf("-----------------------------------------------------------------------\n");
                    printf("Total de Vendas: %d | Valor Acumulado: R$ %.2f\n", count, soma);
                }
                break;
            }
            case 0:
                return;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    }
}

/* Menu de Estatísticas */
void menu_estatisticas(void) {
    while (1) {
        printf("\n========================================\n");
        printf("              ESTATÍSTICAS              \n");
        printf("========================================\n");
        printf("1 - Painel Geral de Indicadores\n");
        printf("2 - Produto Mais Vendido\n");
        printf("3 - Cliente com Maior Volume de Compras\n");
        printf("0 - Voltar ao Menu Principal\n");

        int op = ler_inteiro("Escolha uma opção: ");

        switch (op) {
            case 1:
                relatorio_painel_geral();
                break;
            case 2:
                relatorio_produto_mais_vendido();
                break;
            case 3:
                relatorio_cliente_maior_volume();
                break;
            case 0:
                return;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    }
}
