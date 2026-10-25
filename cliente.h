#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX_CLIENTES 200

typedef struct {
    int codigo;
    char nome[100];
    char cpf[20];
    char telefone[20];
    char email[80];
    char cidade[50];
} Cliente;

/* Funções de persistência em arquivo */
void carregar_clientes(void);
void salvar_clientes(void);

/* Operações do módulo de clientes */
void cadastrar_cliente_menu(void);
void listar_clientes(void);
void buscar_cliente_menu(void);
void alterar_cliente(void);
void excluir_cliente(void);

/* Funções de consulta e integração com outros módulos (utilizando ponteiros) */
Cliente* buscar_cliente_por_codigo(int codigo);
int buscar_indice_cliente_por_codigo(int codigo);
int obter_total_clientes(void);
Cliente* obter_cliente_por_indice(int indice);

/* Função recursiva para busca de cliente por código */
Cliente* buscar_cliente_recursivo(Cliente *lista, int n, int codigo);

#endif