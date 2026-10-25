#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_PRODUTOS 200

typedef struct {
    int codigo;
    char nome[100];
    char categoria[50];
    float preco;
    int quantidade_em_estoque;
} Produto;

/* Funções de persistência em arquivo */
void carregar_produtos(void);
void salvar_produtos(void);

/* Operações do módulo de produtos */
void cadastrar_produto_menu(void);
void listar_produtos(void);
void buscar_produto_menu(void);
void alterar_produto(void);
void excluir_produto(void);
void consultar_estoque(void);
void identificar_estoque_baixo(void);

/* Funções de consulta e integração (utilizando ponteiros) */
Produto* buscar_produto_por_codigo(int codigo);
int buscar_indice_produto_por_codigo(int codigo);
int atualizar_estoque_produto(int codigo, int qtd_subtrair);
int obter_total_produtos(void);
Produto* obter_produto_por_indice(int indice);

/* 
 * FUNCIONALIDADE RECURSIVA:
 * Calcula o valor total estimado do estoque acumulado de forma recursiva.
 */
float calcular_valor_total_estoque_recursivo(const Produto *lista, int n);
float obter_valor_total_estoque(void);

#endif