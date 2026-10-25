# Sistema de Gerenciamento Empresarial
**Universidade Federal do Recôncavo da Bahia (UFRB)**  
**Centro de Ciência e Tecnologia em Energia e Sustentabilidade (CETENS)**  
**Bacharelado em Sistemas de Informação - EaD**  
**Disciplina:** Algoritmos e Programação II  
**Professor:** Alex Ferreira dos Santos  

---

## 🚀 Como compilar e executar

No terminal, execute:
```bash
gcc -Wall -Wextra *.c -o main && ./main
```

---

## 📌 Estrutura do Projeto

- [main.c](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/main.c): Ponto de entrada do programa que chama o menu principal.
- [menu.h](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/menu.h) / [menu.c](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/menu.c): Interface de navegação com submenus organizados por módulo.
- [cliente.h](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/cliente.h) / [cliente.c](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/cliente.c): Módulo de gerenciamento de clientes, busca por múltiplos campos (código, nome, CPF) e persistência binária.
- [produto.h](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/produto.h) / [produto.c](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/produto.c): Módulo de produtos com controle de estoque, cálculo recursivo de valor total de inventário e alerta de estoque baixo.
- [venda.h](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/venda.h) / [venda.c](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/venda.c): Módulo de vendas com múltiplos produtos por venda, validação de estoque, decremento automático de estoque e cálculo de total recursivo.
- [relatorios.h](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/relatorios.h) / [relatorios.c](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/relatorios.c): Painel consolidado com indicadores, identificação do produto mais vendido e do cliente com maior volume de compras.
- [util.h](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/util.h) / [util.c](file:///Users/arturcampos/Developer/Projeto%20UFRB%20Algoritmos%20II/util.c): Funções auxiliares para leitura segura com tratamento de buffer e manipulação de strings insensíveis a maiúsculas/minúsculas.

---

## 📋 Checklist de Requisitos Atendidos

- [x] O sistema compila sem erros com `-Wall -Wextra`.
- [x] O menu principal e os submenus funcionam conforme o roteiro.
- [x] Clientes: cadastrar, listar, buscar (código, nome, CPF), alterar e excluir.
- [x] Produtos: cadastrar, listar, buscar (código, nome, categoria), alterar, excluir, consultar estoque e alerta de estoque baixo.
- [x] Vendas: registrar com múltiplos produtos, impedir venda acima do estoque, atualizar estoque e persistir.
- [x] Persistência em arquivos binários (`clientes.dat`, `produtos.dat`, `vendas.dat`).
- [x] Uso de `struct` heterogêneas (`Cliente`, `Produto`, `ItemVenda`, `Data`, `Venda`).
- [x] Uso de ponteiros e passagem por referência.
- [x] Manipulação de strings e caracteres (`fgets`, `strcspn`, `tolower`, `strstr`).
- [x] Funcionalidades recursivas implementadas com caso base e passo recursivo identificados.
- [x] Validações de entrada completas (códigos únicos, preços não negativos, estoque > 0).
- [x] Relatórios e estatísticas completas.
