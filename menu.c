#include <stdio.h>
#include "menu.h"
#include "cliente.h"
#include "produto.h"
#include "venda.h"
#include "relatorios.h"
#include "util.h"

/* Menu secundário para gerenciamento de clientes */
static void menu_cliente(void) {
    while (1) {
        printf("\n========================================\n");
        printf("         GERENCIAMENTO DE CLIENTES      \n");
        printf("========================================\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Listar clientes\n");
        printf("3 - Buscar cliente (Código, Nome, CPF)\n");
        printf("4 - Alterar cliente\n");
        printf("5 - Excluir cliente\n");
        printf("0 - Voltar ao menu principal\n");

        int op = ler_inteiro("Escolha uma opção: ");

        switch (op) {
            case 1:
                cadastrar_cliente_menu();
                break;
            case 2:
                listar_clientes();
                break;
            case 3:
                buscar_cliente_menu();
                break;
            case 4:
                alterar_cliente();
                break;
            case 5:
                excluir_cliente();
                break;
            case 0:
                return;
            default:
                printf("\nOpção inválida! Escolha uma opção entre 0 e 5.\n");
                break;
        }
    }
}

/* Menu secundário para gerenciamento de produtos */
static void menu_produto(void) {
    while (1) {
        printf("\n========================================\n");
        printf("         GERENCIAMENTO DE PRODUTOS      \n");
        printf("========================================\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Buscar produto (Código, Nome, Categoria)\n");
        printf("4 - Alterar produto\n");
        printf("5 - Excluir produto\n");
        printf("6 - Consultar estoque\n");
        printf("7 - Identificar produtos com estoque baixo\n");
        printf("0 - Voltar ao menu principal\n");

        int op = ler_inteiro("Escolha uma opção: ");

        switch (op) {
            case 1:
                cadastrar_produto_menu();
                break;
            case 2:
                listar_produtos();
                break;
            case 3:
                buscar_produto_menu();
                break;
            case 4:
                alterar_produto();
                break;
            case 5:
                excluir_produto();
                break;
            case 6:
                consultar_estoque();
                break;
            case 7:
                identificar_estoque_baixo();
                break;
            case 0:
                return;
            default:
                printf("\nOpção inválida! Escolha uma opção entre 0 e 7.\n");
                break;
        }
    }
}

/* Menu secundário para gerenciamento de vendas */
static void menu_venda(void) {
    while (1) {
        printf("\n========================================\n");
        printf("          GERENCIAMENTO DE VENDAS       \n");
        printf("========================================\n");
        printf("1 - Registrar nova venda\n");
        printf("2 - Listar vendas realizadas\n");
        printf("3 - Buscar venda (Código da venda ou cliente)\n");
        printf("0 - Voltar ao menu principal\n");

        int op = ler_inteiro("Escolha uma opção: ");

        switch (op) {
            case 1:
                registrar_venda();
                break;
            case 2:
                listar_vendas();
                break;
            case 3:
                buscar_venda();
                break;
            case 0:
                return;
            default:
                printf("\nOpção inválida! Escolha uma opção entre 0 e 3.\n");
                break;
        }
    }
}

/* Menu principal do sistema */
int menu(void) {
    /* Carrega os dados persistidos dos arquivos binários */
    carregar_clientes();
    carregar_produtos();
    carregar_vendas();

    while (1) {
        printf("\n========================================\n");
        printf("     SISTEMA DE GESTÃO EMPRESARIAL      \n");
        printf("========================================\n");
        printf("1 - Gerenciar Clientes\n");
        printf("2 - Gerenciar Produtos\n");
        printf("3 - Gerenciar Vendas\n");
        printf("4 - Consultas e Relatórios\n");
        printf("5 - Estatísticas\n");
        printf("0 - Sair\n");
        printf("========================================\n");

        int op = ler_inteiro("Escolha uma opção: ");

        switch (op) {
            case 1:
                menu_cliente();
                break;
            case 2:
                menu_produto();
                break;
            case 3:
                menu_venda();
                break;
            case 4:
                menu_consultas_relatorios();
                break;
            case 5:
                menu_estatisticas();
                break;
            case 0:
                salvar_clientes();
                salvar_produtos();
                salvar_vendas();
                printf("\nDados salvos com sucesso! Encerrando o sistema. Até logo!\n");
                return 0;
            default:
                printf("\nOpção inválida! Escolha um número entre 0 e 5.\n");
                break;
        }
    }
}