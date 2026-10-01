/* 
 * Arquivo: item.c
 * Descrição: Implementação das funções estritamente relacionadas ao Item[cite: 1].
 * Conteúdo planeado:
 * - Validações de consistência do item (ex: verificar se os espaços consumidos estão entre 1 e 50)[cite: 1].
 */

#include <stdio.h>
#include <string.h>
#include "item.h"

// valida os campos de um item de acordo com as regras do trabalho
int itemValido(Item item) {
    // id tem que ser positivo
    if (item.id <= 0)
        return 0;

    // o nome não pode ser vazio nem estourar o buffer que é de 1 a 49 caracteres uteis
    //strlen: calcula o numero de caracteres de uma string sem contar o caractere final(nulo), e retorna um numero inteiro
    if (strlen(item.nome) == 0 || strlen(item.nome) >= 50)
        return 0;

    // o tipo do item tem que ta dentro do intervalo válido do enum
    if (item.tipo < ELMO || item.tipo > ARMA_DUAS_MAOS)
        return 0;

    // o consumo de espaços tem que ta obrigatoriamente entre 1 e 50
    if (item.espacos < 1 || item.espacos > 50)
        return 0;

    // o poder do item nao pode ser negativo
    if (item.poder < 0)
        return 0;

    // se passou por todas as validações o item é válido
    return 1;
}

// retorna uma string correspondente ao tipo do item para facilitar a listagem
const char *nomeTipoItem(TipoItem tipo) {
    switch (tipo) {
        case ELMO: 
        return "Elmo";

        case PEITORAL: 
        return "Peitoral";

        case MANOPLAS: 
        return "Manoplas";

        case CALCA: 
        return "Calca";

        case BOTAS: 
        return "Botas";
        case ANEL: return "Anel";

        case COLAR: 
        return "Colar";

        case CINTO: 
        return "Cinto";

        case ARMA_UMA_MAO: 
        return "Arma (1 Mao)";

        case ARMA_DUAS_MAOS: 
        return "Arma (2 Maos)";
        
        default: return "Desconhecido";
    }
}