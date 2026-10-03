/* 
 * Arquivo: inventario.c
 * Descrição: Lógica de gestão da coleção de itens[cite: 1].
 * Conteúdo planeado:
 * - Cálculo iterativo de espaços ocupados (sem atualizar uma suposta carga total global)[cite: 1].
 * - Inserção de itens respeitando o limite de 50 espaços e unicidade de ID[cite: 1].
 * - Remoção de itens mantendo os registos contíguos no vetor (deslocamento)[cite: 1].
 */

#include <stddef.h>
#include "item.h"
#include "inventario.h"

#define CAPACIDADE_INVENTARIO 50



typedef struct {
    Item itens[CAPACIDADE_INVENTARIO];
    int quantidade;
} Inventario;


void inicializarInventario(Inventario *inv){
    if(inv!=NULL){
        inv->quantidade = 0;
    }
}


int calcularOcupacaoInventario(const Inventario *inv) {
    int somaEspacos = 0;
    for (int i = 0; i < inv->quantidade; i++) {
        somaEspacos += inv->itens[i].espacos; //somatorio do documento
    }
    return somaEspacos;
}


int buscarIndiceItem(const Inventario *inv, int idItem) {
    for (int i = 0; i < inv->quantidade; i++) {
        if (inv->itens[i].id == idItem) {
            return i; // Achou na posição i
        }
    }
    return -1; // Não achou
}

Item *buscarItemInventario(Inventario *inv, int idItem){
    int idx = buscarIndiceItem(inv, idItem);

    if(idx == -1) return NULL;
    
    return &inv->itens[idx];
}

Estado buscarItemPorId(const Inventario *inv, int idItem, Item *itemEncontrado) { //usa ponteiro para conseguir retornar o item e o estado
    int indice = buscarIndiceItem(inv, idItem);
    if (indice == -1) {
        return ITEM_NAO_ENCONTRADO;
    }
    if (itemEncontrado != NULL) {
        *itemEncontrado = inv->itens[indice];
    }
    return SUCESSO;
}


Estado adicionarItemInventario(Inventario *inv, Item novoItem) {
    
    if (!itemValido(novoItem)) {
        return DADOS_INVALIDOS;
    }

    //verificar se o ID já existe no inventário deste personagem
    if (buscarIndiceItem(inv, novoItem.id) != -1) {
        return ID_DUPLICADO;
    }

    //verificar se a soma dos espaços atuais + novo item ultrapassa 50
    int ocupacaoAtual = calcularOcupacaoInventario(inv);
    if (ocupacaoAtual + novoItem.espacos > CAPACIDADE_INVENTARIO) {
        return INVENTARIO_SEM_ESPACO;
    }

    // Se passou por tudo, insere no final do vetor (mantendo contíguo)
    inv->itens[inv->quantidade] = novoItem;
    inv->quantidade++;

    return SUCESSO;
}

// 6. Remover Item: exclui e puxa os elementos da frente para trás
Estado removerItemInventario(Inventario *inv, int idItem) {
    int indice = buscarIndiceItem(inv, idItem);
    
    if (indice == -1) {
        return ITEM_NAO_ENCONTRADO;
    }

    // Deslocamento para a esquerda (elimina o buraco no vetor)
    for (int i = indice; i < inv->quantidade - 1; i++) {
        inv->itens[i] = inv->itens[i + 1];
    }

    inv->quantidade--;
    return SUCESSO;
}

void listarInventario(const Inventario *inv){
    int ocupados = calcularOcupacaoInventario(inv);

    printf("\n--- inventario (Ocupacao: %d/%d)---\n", ocupados, CAPACIDADE_INVENTARIO);

    if(inv->quantidade == 0){
        printf("inventario vazio\n");
    return;
    }

    for (int i = 0; i < inv->quantidade; i++)
    {
        Item it = inv-> itens[i];
        printf("[ID: %d] %s (%s) | Espacos: %d | Bonus -> ATQ: %+d DEF:%+d PV:%+d INI:%+d POD:%+d\n",
        it.id, it.nome, nomeTipoItem(it.tipo), it.espacos, it.bonusAtaque, it.bonusDefesa, it.bonusVida, it.bonusIniciativa, it.poder);
    }
    

}