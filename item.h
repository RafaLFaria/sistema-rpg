/* 
 * Arquivo: item.h
 * Descrição: Definição da estrutura base dos equipamentos e suas categorias[cite: 1].
 * Conteúdo planeado:
 * - struct do Item (ID, Nome, Tipo, Espaços consumidos, e Bônus de atributos)[cite: 1].
 * - enum para as categorias de itens (ELMO, PEITORAL, MANOPLAS, CALCA, BOTAS, ANEL, COLAR, CINTO, ARMA_UMA_MAO, ARMA_DUAS_MAOS)[cite: 1].
 */

#ifndef ITEM_H
#define ITEM_H

// Tipos de itens/equipamentos obrigatórios exigidos pelo enunciado
typedef enum {
    ELMO,
    PEITORAL,
    MANOPLAS,
    CALCA,
    BOTAS,
    ANEL,
    COLAR,
    CINTO,
    ARMA_UMA_MAO,
    ARMA_DUAS_MAOS
} TipoItem;

// Estrutura que representa um item individual na mochila ou equipado
typedef struct {
    int id;                
    char nome[50];         
    TipoItem tipo;           
    int espacos;              
    int bonusAtaque;          
    int bonusDefesa;          
    int bonusVida;            
    int bonusIniciativa;      
    int poder;                
} Item;

// Função auxiliar para validar se os dados de um item respeitam as regras
int itemValido(Item item);

// Função auxiliar para converter o tipo do item em string legível para exibição
const char *nomeTipoItem(TipoItem tipo);

#endif