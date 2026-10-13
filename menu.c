#include <stdio.h>
#include "menu.h"
#include "produto.h"
#include "cliente.h"

/* static = só o menu principal é visível para fora deste arquivo */
static int menu_produto(void){

    int option_produto;
    while(1){
        printf("========================================\n");
        printf("       GERENCIAMENTO DE PRODUTO\n");
        printf("========================================\n");

        printf("1. Cadastrar produtos\n 2. Listar produtos\n 3. Buscar produto\n 4. Alterar produto\n 5. Excluir produto\n 0. Voltar\n ");

        if (scanf("%d", &option_produto) != 1) {
            printf("\nEntrada inválida! Digite apenas números.\n");

            while (getchar() != '\n');
            continue;

        }
        getchar();

        switch(option_produto){
            case 1:
                printf("você escolheu a opção %d produto \n", option_produto);
                Produto novo_produto = cadastrar_produto();
                armazenar_produto(novo_produto);
                break;
            case 2:
                printf("você escolheu a opção %d produto \n", option_produto);
                listar_produtos();
                break;
            case 3:
                printf("você escolheu a opção %d produto \n", option_produto);
                buscar_produto();
                break;
            case 4:
                printf("você escolheu a opção %d produto \n", option_produto);
                alterar_produto();
                break;
            case 5:
                printf("você escolheu a opção %d produto \n", option_produto);
                excluir_produto();
                break;
            case 0:
                printf("você escolheu a opção %d produto \n", option_produto);
                printf("Até a próxima!\n");
                return 0;
            default:
                printf("você não escolheu um número válido!, tente novamente!\n");
                break;
        }

    }
}


static int menu_cliente(void){

    int option_cliente;
    while(1){
        printf("========================================\n");
        printf("       GERENCIAMENTO DE CLIENTES\n");
        printf("========================================\n");

        printf("1. Cadastrar cliente\n 2. Listar clientes\n 3. Buscar cliente\n 4. Alterar cliente\n 5. Excluir cliente\n 0. Voltar\n ");

        if (scanf("%d", &option_cliente) != 1) {
            printf("\nEntrada inválida! Digite apenas números.\n");

            while (getchar() != '\n');
            continue;

        }
        getchar();

        switch(option_cliente){
            case 1:
                printf("você escolheu a opção %d cliente \n", option_cliente);
                Cliente novo_cliente = cadastrar_cliente();
                armazenar_cliente(novo_cliente);
                break;
            case 2:
                printf("você escolheu a opção %d cliente \n", option_cliente);
                listar_clientes();
                break;
            case 3:
                printf("você escolheu a opção %d cliente \n", option_cliente);
                buscar_cliente();
                break;
            case 4:
                printf("você escolheu a opção %d cliente \n", option_cliente);
                alterar_cliente();
                break;
            case 5:
                printf("você escolheu a opção %d cliente \n", option_cliente);
                excluir_cliente();
                break;
            case 0:
                printf("você escolheu a opção %d cliente \n", option_cliente);
                printf("Até a próxima!\n");
                return 0;
            default:
                printf("você não escolheu um número válido!, tente novamente!\n");
                break;
        }

    }
}

int menu(void){

    while (1){
        int option;
        printf("========================================\n");
        printf("SISTEMA DE GERENCIAMENTO EMPRESARIAL\n");
        printf("========================================\n");

        printf(" 1 - Gerenciar Clientes\n 2 - Gerenciar Produtos\n 3 - Gerenciar Vendas\n 4 - Consultas e Relatórios\n 5 - Estatísticas\n 0 - Sair\n ");

        if (scanf("%d", &option) != 1) {
            printf("\nEntrada inválida! Digite apenas números.\n\n");

            while (getchar() != '\n');
            continue;

        }

        switch(option){
            case 1:
                printf("você escolheu a opção %d \n", option);
                menu_cliente();
                break;
            case 2:
                printf("você escolheu a opção %d \n", option);
                menu_produto();
                break;
            case 3:
                printf("você escolheu a opção %d \n", option);
                break;
            case 4:
                printf("você escolheu a opção %d \n", option);
                break;
            case 5:
                printf("você escolheu a opção %d \n", option);
                break;
            case 0:
                printf("você escolheu a opção %d\n", option);
                printf("Até a próxima!\n");
                return 0;
            default:
                printf("você não escolheu um número válido!, tente novamente!\n");
                break;
        }
    }
}