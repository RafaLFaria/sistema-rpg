/*
 * Arquivo: personagem.c
 * Descrição: Implementação do núcleo funcional do sistema[cite: 1].
 * Conteúdo planeado:
 * - Funções do CRUD (cadastrar, alterar, buscar, remover, listar) operando sobre o endereço do cadastro[cite: 1].
 * - Lógica atómica para equipar (troca segura de itens, bloqueio de duas mãos, verificação de espaço na devolução) e desequipar[cite: 1].
 * - Função de cálculo dinâmico dos atributos totais (somando base + bônus de equipamentos ativos)[cite: 1].
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h> //contém null, ele é importante pra n dar bizil na busca de personagem
#include "personagem.h"

void inicializarCadastro(CadastroPersonagens *cadastro)
{
    cadastro->quantidade = 0;
}

int obterQuantidadePersonagens(const CadastroPersonagens *cadastro)
{
    return cadastro->quantidade;
}

// testar se o personagem é valido
static int personagemValido(Personagem personagem)
{
    if (personagem.id <= 0)
        return 0;

    if (strlen(personagem.nome) == 0 || strlen(personagem.nome) >= 50)
        return 0;

    if (personagem.raca < HUMANO || personagem.raca > ORC)
        return 0;

    if (personagem.classe < GUERREIRO || personagem.classe > BARDO)
        return 0;

    if (personagem.nivel < 1 || personagem.nivel > 20)
        return 0;

    if (personagem.vidaMaxima < 1 || personagem.vidaMaxima > 999)
        return 0;

    if (personagem.hp < 0 || personagem.hp > personagem.vidaMaxima)
        return 0;

    if (personagem.ataque < 0 || personagem.ataque > 30)
        return 0;

    if (personagem.defesa < 1 || personagem.defesa > 30)
        return 0;

    if (personagem.iniciativa < -5 || personagem.iniciativa > 20)
        return 0;

    if (personagem.poder < 1 || personagem.poder > 100)
        return 0;

    return 1;
}

// retorna o estado para ficar melhor o retorno de erro
Estado cadastrarPersonagem(CadastroPersonagens *cadastro, Personagem novoPersonagem)
{
    if (!personagemValido(novoPersonagem))
        return DADOS_INVALIDOS;

    if (cadastro->quantidade >= CAPACIDADE_MAX)
        return CADASTRO_CHEIO;

    for (int i = 0; i < cadastro->quantidade; i++)
    {
        if (cadastro->fichas[i].id == novoPersonagem.id)
            return ID_DUPLICADO;
    }

    inicializarInventario(&novoPersonagem.inv);

    for (int i = 0; i < 10; i++)
    {
        novoPersonagem.equipamento[i].id = 0;
    }

    cadastro->fichas[cadastro->quantidade] = novoPersonagem;
    cadastro->quantidade++;
    return SUCESSO;
}

// retorna o personagem inteiro
// é um ponteiro para ser útil
Personagem *buscarPersonagem(CadastroPersonagens *cadastro, int id)
{
    for (int i = 0; i < cadastro->quantidade; i++)
    {
        if (cadastro->fichas[i].id == id)
            return &cadastro->fichas[i];
    }

    return NULL;
}

Estado removerPersonagem(CadastroPersonagens *cadastro, int id)
{
    int posicao = -1;

    for (int i = 0; i < cadastro->quantidade; i++)
    {
        if (cadastro->fichas[i].id == id)
        {
            posicao = i;
            break;
        }
    }

    if (posicao == -1)
        return NAO_ENCONTRADO;

    for (int i = posicao; i < cadastro->quantidade - 1; i++)
    {
        cadastro->fichas[i] = cadastro->fichas[i + 1];
    }

    cadastro->quantidade--;

    return SUCESSO;
}

// ponteiro pra alterar msm
Estado alterarPersonagem(CadastroPersonagens *cadastro, int id, Personagem novoPersonagem)
{
    Personagem *personagem = buscarPersonagem(cadastro, id);

    if (personagem == NULL)
        return NAO_ENCONTRADO;

    if (!personagemValido(novoPersonagem))
        return DADOS_INVALIDOS;

    for (int i = 0; i < cadastro->quantidade; i++)
    {
        if (cadastro->fichas[i].id == novoPersonagem.id &&
            cadastro->fichas[i].id != id)
        {
            return ID_DUPLICADO;
        }
    }

    novoPersonagem.inv = personagem->inv;

    for (int i = 0; i < EQUIP_MAX; i++)
    {
        novoPersonagem.equipamento[i] = personagem->equipamento[i];
    }

    *personagem = novoPersonagem;

    return SUCESSO;
}

// traduz para usar no printf
const char *nomeRaca(Raca raca)
{
    switch (raca)
    {
    case HUMANO:
        return "Humano";
    case ELFO:
        return "Elfo";
    case ANAO:
        return "Anao";
    case HALFLING:
        return "Halfling";
    case ORC:
        return "Orc"; //traducao da nova raca (casos minimos de teste: usar classe ou raca adicional implementada)
    default:
        return "Desconhecida";
    }
}

const char *nomeClasse(Classe classe)
{
    switch (classe)
    {
    case GUERREIRO:
        return "Guerreiro";
    case LADINO:
        return "Ladino";
    case MAGO:
        return "Mago";
    case CLERIGO:
        return "Clerigo";
    case BARDO:
        return "Bardo";
    default:
        return "Desconhecida";
    }
}

const char *nomePosicaoEquipamento(int slot)
{
    switch (slot)
    {
    case POS_ELMO:
        return "elmo";
    case POS_PEITORAL:
        return "peitoral";
    case POS_MANOPLAS:
        return "manoplas";
    case POS_CALCA:
        return "calca";
    case POS_BOTAS:
        return "botas";
    case POS_ANEL:
        return "anel";
    case POS_CINTO:
        return "cinto";
    case POS_COLAR:
        return "colar";
    case POS_MAO_DIREITA:
        return "mao direita";
    case POS_MAO_ESQUERDA:
        return "mao esquerad";
    default:
        return "desconhecido";
        break;
    }
}

// olha que coisa linda, realmente lindo
void listarPersonagens(const CadastroPersonagens *cadastro)
{
    if (cadastro->quantidade == 0)
    {
        printf("Nenhum personagem cadastrado.\n");
        return;
    }

    for (int i = 0; i < cadastro->quantidade; i++)
    {
        Personagem p = cadastro->fichas[i];

        printf("\n-----------------------------\n");
        printf("ID: %d\n", p.id);
        printf("Nome: %s\n", p.nome);
        printf("Raca: %s\n", nomeRaca(p.raca));
        printf("Classe: %s\n", nomeClasse(p.classe));
        printf("Nivel: %d\n", p.nivel);
        printf("PV: %d/%d\n", p.hp, p.vidaMaxima);
        printf("Ataque: %d\n", p.ataque);
        printf("Defesa: %d\n", p.defesa);
        printf("Iniciativa: %d\n", p.iniciativa);
        printf("Poder: %d\n", p.poder);
    }

    printf("-----------------------------\n");
}

#define SLOT_MAO_DIREITA 8
#define SLOT_MAO_ESQUERDA 9

// EQUIPAMENTO AQUI ANA

Estado equiparItem(CadastroPersonagens *cadastro, int idPersonagem, int idItem)
{
    // Busca o rapaz
    Personagem *p = buscarPersonagem(cadastro, idPersonagem);
    if (p == NULL)
        return NAO_ENCONTRADO;

    // Busca o item na mochila
    Item *itemNaMochila = buscarItemInventario(&p->inv, idItem);
    if (itemNaMochila == NULL)
        return ITEM_NAO_ENCONTRADO;

    // Guarda a cópia antes de remover da mochila
    Item copiaItem = *itemNaMochila;

    // É uma roupa ou acessório (de ELMO=0 até CINTO=7)
    if (copiaItem.tipo >= ELMO && copiaItem.tipo <= CINTO)
    {
        int slot = copiaItem.tipo;

        // tem coisa já?
        if (p->equipamento[slot].id != 0)
        {
            Item itemAntigo = p->equipamento[slot];
            int ocupacaoAtual = calcularOcupacaoInventario(&p->inv);

            if (ocupacaoAtual - copiaItem.espacos + itemAntigo.espacos > CAPACIDADE_INVENTARIO)
            {
                return INVENTARIO_SEM_ESPACO;
            }
            removerItemInventario(&p->inv, idItem);
            adicionarItemInventario(&p->inv, itemAntigo);
            p->equipamento[slot] = copiaItem;
            return SUCESSO;
        }

        p->equipamento[slot] = copiaItem;
        removerItemInventario(&p->inv, idItem);
        return SUCESSO;
    }

    // sessao de armas

    // uma mao
    if (copiaItem.tipo == ARMA_UMA_MAO)
    {
        // maos ocupadas?
        if (p->equipamento[SLOT_MAO_DIREITA].id != 0 &&
            p->equipamento[SLOT_MAO_DIREITA].tipo == ARMA_DUAS_MAOS)
        {
            return CONFLITO_DUAS_MAOS;
        }

        // Tenta colocar na mão direita, se estiver ocupada, tenta na esquerda
        if (p->equipamento[SLOT_MAO_DIREITA].id == 0)
        {
            p->equipamento[SLOT_MAO_DIREITA] = copiaItem;
        }
        else if (p->equipamento[SLOT_MAO_ESQUERDA].id == 0)
        {
            p->equipamento[SLOT_MAO_ESQUERDA] = copiaItem;
        }
        else
        {
            return JA_EQUIPADO; // As duas mãos já estão ocupadas
        }

        removerItemInventario(&p->inv, idItem);
        return SUCESSO;
    }

    // É uma Arma de DUAS mãos
    if (copiaItem.tipo == ARMA_DUAS_MAOS)
    {
        if (p->equipamento[SLOT_MAO_DIREITA].id != 0 ||
            p->equipamento[SLOT_MAO_ESQUERDA].id != 0)
        {
            return CONFLITO_DUAS_MAOS;
        }

        // Equipa na mão direita (e ela passa a bloquear a esquerda também)
        p->equipamento[SLOT_MAO_DIREITA] = copiaItem;
        removerItemInventario(&p->inv, idItem);
        return SUCESSO;
    }

    return DADOS_INVALIDOS;
}

Estado desequiparItem(CadastroPersonagens *cadastro, int idPersonagem, int idItem){
    Personagem *p = buscarPersonagem(cadastro, idPersonagem);

    if(p == NULL){
        return NAO_ENCONTRADO;
    }
    int slotEncontrado = -1;

    for(int i = 0; i<EQUIP_MAX; i++){
        if(p->equipamento[i].id == idItem && idItem>0){
            slotEncontrado = i;
            break;
        }
    }

    if(slotEncontrado == -1){
        return ITEM_NAO_ENCONTRADO;
    }

    //tentar adicionar o item no inventario antes de desequipar
    Estado statusINV = adicionarItemInventario(&p->inv, p->equipamento[slotEncontrado]);
    if(statusINV!=SUCESSO){
        //n da pra desequipar;
        return statusINV;
    }

    //se adicionou, tira do corpo
    p->equipamento[slotEncontrado].id=0;
    return SUCESSO;
}

Estado consultarEquipamentos(const CadastroPersonagens *cadastro, int idPersonagem)
{
    // Busca sem alterar o cadastro
    const Personagem *p = NULL;
    for (int i = 0; i < cadastro->quantidade; i++)
    {
        if (cadastro->fichas[i].id == idPersonagem)
        {
            p = &cadastro->fichas[i];
            break;
        }
    }

    if (p == NULL)
        return NAO_ENCONTRADO;

    printf("\n=== EQUIPAMENTOS DE %s ===\n", p->nome);
    for (int i = 0; i < EQUIP_MAX; i++)
    {
        // Se for a mão esquerda e a direita tiver arma de 2 mãos, avisa que está bloqueada!
        if (i == SLOT_MAO_ESQUERDA &&
            p->equipamento[SLOT_MAO_DIREITA].id != 0 &&
            p->equipamento[SLOT_MAO_DIREITA].tipo == ARMA_DUAS_MAOS)
        {
            printf("%-14s: [Bloqueada por %s (2 Maos)]\n",
                   nomePosicaoEquipamento(i), p->equipamento[SLOT_MAO_DIREITA].nome);
            continue;
        }

        if (p->equipamento[i].id != 0)
        {
            Item it = p->equipamento[i];
            printf("%-14s: [ID: %d] %s (ATQ:%+d DEF:%+d PV:%+d INI:%+d POD:%+d)\n",
                   nomePosicaoEquipamento(i), it.id, it.nome,
                   it.bonusAtaque, it.bonusDefesa, it.bonusVida, it.bonusIniciativa, it.poder);
        }
        else
        {
            printf("%-14s: [Vazio]\n", nomePosicaoEquipamento(i));
        }
    }
    return SUCESSO;
}


//quebra o calculo de atributos em funcoes menores

int calcularVidaMaximaTotal(const Personagem *p)
{
    int total = p->vidaMaxima;
    for (int i = 0; i < EQUIP_MAX; i++)
    {
        if (p->equipamento[i].id != 0)
            total += p->equipamento[i].bonusVida;
    }
    return total;
}

int calcularAtaqueTotal(const Personagem *p)
{
    int total = p->ataque;
    for (int i = 0; i < EQUIP_MAX; i++)
    {
        if (p->equipamento[i].id != 0)
            total += p->equipamento[i].bonusAtaque;
    }
    return total;
}

int calcularDefesaTotal(const Personagem *p)
{
    int total = p->defesa;
    for (int i = 0; i < EQUIP_MAX; i++)
    {
        if (p->equipamento[i].id != 0)
            total += p->equipamento[i].bonusDefesa;
    }
    return total;
}

int calcularIniciativaTotal(const Personagem *p)
{
    int total = p->iniciativa;
    for (int i = 0; i < EQUIP_MAX; i++)
    {
        if (p->equipamento[i].id != 0)
            total += p->equipamento[i].bonusIniciativa;
    }
    return total;
}

int calcularPoderTotal(const Personagem *p)
{
    int total = p->poder;
    for (int i = 0; i < EQUIP_MAX; i++)
    {
        if (p->equipamento[i].id != 0)
            total += p->equipamento[i].poder;
    }
    return total;
}

Estado exibirAtributosTotais(const CadastroPersonagens *cadastro, int idPersonagem)
{
    const Personagem *p = NULL;
    for (int i = 0; i < cadastro->quantidade; i++)
    {
        if (cadastro->fichas[i].id == idPersonagem)
        {
            p = &cadastro->fichas[i];
            break;
        }
    }

    if (p == NULL)
        return NAO_ENCONTRADO;

    int pvMaxTotal = calcularVidaMaximaTotal(p);
    int atqTotal   = calcularAtaqueTotal(p);
    int defTotal   = calcularDefesaTotal(p);
    int iniTotal   = calcularIniciativaTotal(p);
    int podTotal   = calcularPoderTotal(p);

    printf("\n=== ATRIBUTOS TOTAIS: %s ===\n", p->nome);
    printf("PV Maximos : %d (Base: %d | Bonus Equip: %+d)\n", pvMaxTotal, p->vidaMaxima, pvMaxTotal - p->vidaMaxima);
    printf("PV Atuais  : %d\n", p->hp);
    printf("Ataque     : %d (Base: %d | Bonus Equip: %+d)\n", atqTotal, p->ataque, atqTotal - p->ataque);
    printf("Defesa     : %d (Base: %d | Bonus Equip: %+d)\n", defTotal, p->defesa, defTotal - p->defesa);
    printf("Iniciativa : %d (Base: %d | Bonus Equip: %+d)\n", iniTotal, p->iniciativa, iniTotal - p->iniciativa);
    printf("Poder      : %d (Base: %d | Bonus Equip: %+d)\n", podTotal, p->poder, podTotal - p->poder);

    return SUCESSO;
}