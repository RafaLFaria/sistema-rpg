/* 
 * Arquivo: inventario.h
 * Descrição: Estruturas e interface pública para gerir a mochila do personagem[cite: 1].
 * Conteúdo planeado:
 * - struct do Inventário, contendo o vetor de 50 posições[cite: 1].
 * - Protótipos das funções: calcular ocupação, adicionar item, buscar item por ID, remover item e listar inventário[cite: 1].
 */

#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "item.h"

#define CAPACIDADE_INVENTARIO 50

// Caso não tenha colocado este enum no item.h, pode declará-lo aqui:
typedef enum {
    SUCESSO,
    CADASTRO_CHEIO,
    ID_DUPLICADO,
    NAO_ENCONTRADO,
    DADOS_INVALIDOS,
    JA_EQUIPADO,
    INVENTARIO_SEM_ESPACO,
    ITEM_INCOMPATIVEL,
    ITEM_NAO_ENCONTRADO,
    CONFLITO_DUAS_MAOS
} Estado;

typedef struct {
    Item itens[CAPACIDADE_INVENTARIO];
    int quantidade; 
} Inventario;


void inicializarInventario(Inventario *inv);
int calcularOcupacaoInventario(const Inventario *inv);
int buscarIndiceItem(const Inventario *inv, int idItem);
Estado buscarItemPorId(const Inventario *inv, int idItem, Item *itemEncontrado);
Estado adicionarItemInventario(Inventario *inv, Item novoItem);
Estado removerItemInventario(Inventario *inv, int idItem);
Item *buscarItemInventario(Inventario *inv, int idItem);

#endif