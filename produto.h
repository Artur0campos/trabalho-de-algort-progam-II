#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_PRODUTOS 200

typedef struct {
    int codigo;
    char nome[80];
    char categoria[80];
    float preco;
    int quantidade_em_estoque;
} Produto;

Produto cadastrar_produto(void);
int armazenar_produto(Produto p);
void listar_produtos(void);
void buscar_produto(void);
void alterar_produto(void);
void excluir_produto(void);

#endif