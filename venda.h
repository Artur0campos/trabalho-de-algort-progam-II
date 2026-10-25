#ifndef VENDA_H
#define VENDA_H

#include "produto.h"
#include "cliente.h"

#define MAX_ITENS_VENDA 20
#define MAX_VENDAS 500

typedef struct {
    int cod_produto;
    char nome_produto[100];
    int quantidade;
    float preco_unitario;
    float subtotal;
} ItemVenda;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int cod_venda;
    int cod_cliente;
    Data data;
    ItemVenda itens[MAX_ITENS_VENDA];
    int total_itens;
    float valor_total;
} Venda;

/* Funções de persistência em arquivo */
void carregar_vendas(void);
void salvar_vendas(void);

/* Operações do módulo de vendas */
void registrar_venda(void);
void listar_vendas(void);
void buscar_venda(void);

/* Consultas e integração com relatórios (utilizando ponteiros) */
int obter_total_vendas(void);
Venda* obter_venda_por_indice(int indice);
Venda* buscar_venda_por_codigo(int cod_venda);

/*
 * FUNCIONALIDADE RECURSIVA:
 * Calcula a soma total dos itens de uma venda de forma recursiva.
 */
float calcular_total_venda_recursivo(const ItemVenda *itens, int n);

#endif
