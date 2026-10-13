#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX_CLIENTES 100

typedef struct {
    int codigo;
    char nome[50];
    char cpf[20];
    char telefone[20];
    char email[50];
    char cidade[50];
} Cliente;

Cliente cadastrar_cliente(void);
int armazenar_cliente(Cliente c);
void listar_clientes(void);
void buscar_cliente(void);
void alterar_cliente(void);
void excluir_cliente(void);

#endif