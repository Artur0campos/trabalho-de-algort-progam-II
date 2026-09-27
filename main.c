#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_PRODUTOS 200


typedef struct {
    int codigo;
    char nome[80];
    char categoria[80];
    float preco;
    int quantidade_em_estoque;
} Produto;

typedef struct {
    int codigo;
    char nome[50];
    char cpf[15];
    char telefone[20];
    char email[50];
    char cidade[50];
} Cliente;


Produto lista_produtos[MAX_PRODUTOS];
int total_produtos = 0;

Cliente lista_clientes[MAX_CLIENTES];
int total_clientes = 0;


int armazenar_cliente(Cliente c) {
    if (total_clientes >= MAX_CLIENTES) {
        printf("\nErro: Limite de clientes atingido!\n");
        return 0; 
    }

    lista_clientes[total_clientes] = c;
    total_clientes++;                   
    
    printf("\nCliente '%s' armazenado com sucesso!\n", c.nome);
    return 1;
}

int armazenar_produto(Produto p) {
    if (total_produtos >= MAX_PRODUTOS) {
        printf("\nErro: Limite de produtos atingido!\n");
        return 0; 
    }

    lista_produtos[total_produtos] = p;
    total_produtos++;                   
    
    printf("\nProduto '%s' armazenado com sucesso!\n", p.nome);
    return 1;
}


Produto cadastrar_produto() {
    
    Produto novo;

    printf("\n====== NOVO CADASTRO DE PRODUTO ======\n");
    printf("Código: ");
    scanf("%d", &novo.codigo);
    getchar(); 

    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; 

    printf("Categoria: ");
    fgets(novo.categoria, sizeof(novo.categoria), stdin);
    novo.categoria[strcspn(novo.categoria, "\n")] = '\0';

    printf("Preço: ");
    scanf("%f", &novo.preco);
    getchar(); 

    printf("Quantidade em estoque: ");
    scanf("%d", &novo.quantidade_em_estoque);
    getchar(); 


    return novo; 
}

Cliente cadastrar_cliente() {
    
    Cliente novo;

    printf("\n====== NOVO CADASTRO DE CLIENTE ======\n");
    printf("Código: ");
    scanf("%d", &novo.codigo);
    getchar(); 

    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; 

    printf("CPF: ");
    fgets(novo.cpf, sizeof(novo.cpf), stdin);
    novo.cpf[strcspn(novo.cpf, "\n")] = '\0';

    printf("Telefone: ");
    fgets(novo.telefone, sizeof(novo.telefone), stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = '\0';

    printf("E-mail: ");
    fgets(novo.email, sizeof(novo.email), stdin);
    novo.email[strcspn(novo.email, "\n")] = '\0';

    printf("Cidade: ");
    fgets(novo.cidade, sizeof(novo.cidade), stdin);
    novo.cidade[strcspn(novo.cidade, "\n")] = '\0';

    return novo; 
}


int buscar_indice_produto(int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscar_indice_cliente(int codigo) {
    for (int i = 0; i < total_clientes; i++) {
        if (lista_clientes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void listar_produtos() {
    if (total_produtos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n====== LISTA DE PRODUTOS ======\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("----------------------------------------\n");
        printf("Código: %d\n", lista_produtos[i].codigo);
        printf("Nome: %s\n", lista_produtos[i].nome);
        printf("Categoria: %s\n", lista_produtos[i].categoria);
        printf("Preço: %.2f\n", lista_produtos[i].preco);
        printf("Quantidade em estoque: %d\n", lista_produtos[i].quantidade_em_estoque);
    }
    printf("----------------------------------------\n");
}

void listar_clientes() {
    if (total_clientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }

    printf("\n====== LISTA DE CLIENTES ======\n");
    for (int i = 0; i < total_clientes; i++) {
        printf("----------------------------------------\n");
        printf("Código: %d\n", lista_clientes[i].codigo);
        printf("Nome: %s\n", lista_clientes[i].nome);
        printf("CPF: %s\n", lista_clientes[i].cpf);
        printf("Telefone: %s\n", lista_clientes[i].telefone);
        printf("E-mail: %s\n", lista_clientes[i].email);
        printf("Cidade: %s\n", lista_clientes[i].cidade);
    }
    printf("----------------------------------------\n");
}




void buscar_produto() {
    int codigo;

    printf("\nDigite o código do produto que deseja buscar: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_produto(codigo);

    if (indice == -1) {
        printf("\nProduto não encontrado!\n");
        return;
    }

    printf("\n====== PRODUTO ENCONTRADO ======\n");
    printf("Código: %d\n", lista_produtos[indice].codigo);
    printf("Nome: %s\n", lista_produtos[indice].nome);
    printf("Categoria: %s\n", lista_produtos[indice].categoria);
    printf("Preço: %.2f\n", lista_produtos[indice].preco);
    printf("Quantidade em estoque: %d\n", lista_produtos[indice].quantidade_em_estoque);
}

void buscar_cliente() {
    int codigo;

    printf("\nDigite o código do cliente que deseja buscar: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_cliente(codigo);

    if (indice == -1) {
        printf("\nCliente não encontrado!\n");
        return;
    }

    printf("\n====== CLIENTE ENCONTRADO ======\n");
    printf("Código: %d\n", lista_clientes[indice].codigo);
    printf("Nome: %s\n", lista_clientes[indice].nome);
    printf("CPF: %s\n", lista_clientes[indice].cpf);
    printf("Telefone: %s\n", lista_clientes[indice].telefone);
    printf("E-mail: %s\n", lista_clientes[indice].email);
    printf("Cidade: %s\n", lista_clientes[indice].cidade);
}



void alterar_produto() {
    int codigo;

    printf("\nDigite o código do produto que deseja alterar: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_produto(codigo);

    if (indice == -1) {
        printf("\nProduto não encontrado!\n");
        return;
    }

    printf("\n====== ALTERAR PRODUTO ======\n");
    printf("(Deixe em branco e pressione Enter para manter o valor atual)\n");

    char buffer[80];

    printf("Nome atual: %s\n", lista_produtos[indice].nome);
    printf("Novo nome: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(lista_produtos[indice].nome, buffer);
    }

    printf("Categoria atual: %s\n", lista_produtos[indice].categoria);
    printf("Nova categoria: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(lista_produtos[indice].categoria, buffer);
    }

    printf("Preço atual: %.2f\n", lista_produtos[indice].preco);
    printf("Novo preço (digite -1 para manter o atual): ");
    float novo_preco;
    scanf("%f", &novo_preco);
    getchar();
    if (novo_preco >= 0) {
        lista_produtos[indice].preco = novo_preco;
    }

    printf("Estoque atual: %d\n", lista_produtos[indice].quantidade_em_estoque);
    printf("Novo estoque (digite -1 para manter o atual): ");
    int novo_estoque;
    scanf("%d", &novo_estoque);
    getchar();
    if (novo_estoque >= 0) {
        lista_produtos[indice].quantidade_em_estoque = novo_estoque;
    }

    printf("\nProduto atualizado com sucesso!\n");
}

void alterar_cliente() {
    int codigo;

    printf("\nDigite o código do cliente que deseja alterar: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_cliente(codigo);

    if (indice == -1) {
        printf("\nCliente não encontrado!\n");
        return;
    }

    printf("\n====== ALTERAR CLIENTE ======\n");
    printf("(Deixe em branco e pressione Enter para manter o valor atual)\n");

    char buffer[50];

    printf("Nome atual: %s\n", lista_clientes[indice].nome);
    printf("Novo nome: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(lista_clientes[indice].nome, buffer);
    }

    printf("CPF atual: %s\n", lista_clientes[indice].cpf);
    printf("Novo CPF: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(lista_clientes[indice].cpf, buffer);
    }

    printf("Telefone atual: %s\n", lista_clientes[indice].telefone);
    printf("Novo telefone: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(lista_clientes[indice].telefone, buffer);
    }

    printf("E-mail atual: %s\n", lista_clientes[indice].email);
    printf("Novo e-mail: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(lista_clientes[indice].email, buffer);
    }

    printf("Cidade atual: %s\n", lista_clientes[indice].cidade);
    printf("Nova cidade: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(lista_clientes[indice].cidade, buffer);
    }

    printf("\nCliente atualizado com sucesso!\n");
}


void excluir_produto() {
    int codigo;

    printf("\nDigite o código do produto que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_produto(codigo);

    if (indice == -1) {
        printf("\nProduto não encontrado!\n");
        return;
    }

    for (int i = indice; i < total_produtos - 1; i++) {
        lista_produtos[i] = lista_produtos[i + 1];
    }
    total_produtos--;

    printf("\nProduto excluído com sucesso!\n");
}

void excluir_cliente() {
    int codigo;

    printf("\nDigite o código do cliente que deseja excluir: ");
    scanf("%d", &codigo);
    getchar();

    int indice = buscar_indice_cliente(codigo);

    if (indice == -1) {
        printf("\nCliente não encontrado!\n");
        return;
    }

    for (int i = indice; i < total_clientes - 1; i++) {
        lista_clientes[i] = lista_clientes[i + 1];
    }
    total_clientes--;

    printf("\nCliente excluído com sucesso!\n");
}


int menu_produto(){
    
    int option_produto;
    while(1){
        printf("========================================\n");
        printf("       GERENCIAMENTO DE PRODUTO\n");
        printf("========================================\n");
        
        printf("1. Cadastrar produtos\n 2. Listar produtos\n 3. Buscar produto\n 4. Alterar produto\n 5. Excluir produto\n ");
        
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
                break;
            default:
                printf("você não escolheu um número válido!, tente novamente!\n");
                break;
        }
        
    }
}


int menu_cliente(){
    
    int option_cliente;
    while(1){
        printf("========================================\n");
        printf("       GERENCIAMENTO DE CLIENTES\n");
        printf("========================================\n");
        
        printf("1. Cadastrar cliente\n 2. Listar clientes\n 3. Buscar cliente\n 4. Alterar cliente\n 5. Excluir cliente\n ");
        
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
                break;
            default:
                printf("você não escolheu um número válido!, tente novamente!\n");
                break;
        }
        
    }
}

int menu(){
   
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
                printf("você escolheu a opção %d", option);
                printf("Até a próxima!\n");
                return 0;
                break;
            default:
                printf("você não escolheu um número válido!, tente novamente!\n");
                break;
        }
    }

    
}

int main()
{
    menu();
}