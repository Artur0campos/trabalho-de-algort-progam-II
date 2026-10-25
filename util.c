#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

/* Limpa caracteres restantes no buffer do teclado */
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Lê uma string com segurança utilizando fgets e remove o '\n' final */
void ler_string(const char *mensagem, char *destino, int tamanho) {
    if (mensagem != NULL && strlen(mensagem) > 0) {
        printf("%s", mensagem);
    }
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        } else {
            /* Se a linha for maior que o buffer, descarta o restante */
            limpar_buffer();
        }
    } else {
        destino[0] = '\0';
    }
}

/* Lê um número inteiro com validação para impedir travamento ou looping infinito */
int ler_inteiro(const char *mensagem) {
    int valor;
    char buffer[64];
    while (1) {
        if (mensagem != NULL && strlen(mensagem) > 0) {
            printf("%s", mensagem);
        }
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char *fim;
            valor = (int)strtol(buffer, &fim, 10);
            /* Verifica se foi lido algum dígito e se o restante é apenas espaço ou quebra de linha */
            if (fim != buffer) {
                while (isspace((unsigned char)*fim)) fim++;
                if (*fim == '\0') {
                    return valor;
                }
            }
        }
        printf("Entrada inválida! Por favor, digite um número inteiro válido.\n");
    }
}

/* Lê um número float com validação */
float ler_float(const char *mensagem) {
    float valor;
    char buffer[64];
    while (1) {
        if (mensagem != NULL && strlen(mensagem) > 0) {
            printf("%s", mensagem);
        }
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            /* Converte possível vírgula para ponto */
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] == ',') {
                    buffer[i] = '.';
                }
            }
            char *fim;
            valor = strtof(buffer, &fim);
            if (fim != buffer) {
                while (isspace((unsigned char)*fim)) fim++;
                if (*fim == '\0') {
                    return valor;
                }
            }
        }
        printf("Entrada inválida! Por favor, digite um número decimal válido (ex: 15.50).\n");
    }
}

/* Converte uma string para minúsculas usando ponteiros e caracteres */
void string_para_minusculo(char *destino, const char *origem) {
    while (*origem) {
        *destino = (char)tolower((unsigned char)*origem);
        destino++;
        origem++;
    }
    *destino = '\0';
}

/* Verifica se a substring está contida no texto ignorando maiúsculas/minúsculas */
int contem_substring_insensivel(const char *texto, const char *busca) {
    char texto_min[256];
    char busca_min[256];

    string_para_minusculo(texto_min, texto);
    string_para_minusculo(busca_min, busca);

    return (strstr(texto_min, busca_min) != NULL);
}

/* Valida se uma data é válida no calendário gregoriano básico */
int validar_data(int dia, int mes, int ano) {
    if (ano < 1900 || ano > 2100) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1) return 0;

    int dias_no_mes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    /* Ano bissexto */
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        dias_no_mes[2] = 29;
    }

    if (dia > dias_no_mes[mes]) return 0;
    return 1;
}
