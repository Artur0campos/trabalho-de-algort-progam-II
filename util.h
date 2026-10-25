#ifndef UTIL_H
#define UTIL_H

/* Funções utilitárias para entrada de dados segura e manipulação de strings */
void limpar_buffer(void);
void ler_string(const char *mensagem, char *destino, int tamanho);
int ler_inteiro(const char *mensagem);
float ler_float(const char *mensagem);
void string_para_minusculo(char *destino, const char *origem);
int contem_substring_insensivel(const char *texto, const char *busca);
int validar_data(int dia, int mes, int ano);

#endif
