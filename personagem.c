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
#include "inventario.h"



void inicializarCadastro(CadastroPersonagens *cadastro)
{
    cadastro->quantidade = 0;
}

//testar se o personagem é valido
static int personagemValido(Personagem personagem)
{
    if (personagem.id <= 0)
        return 0;

    if (strlen(personagem.nome) == 0 || strlen(personagem.nome) >= 50)
        return 0;

    if (personagem.raca < HUMANO || personagem.raca > HALFLING)
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


//retorna o estado para ficar melhor o retorno de erro
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

    cadastro->fichas[cadastro->quantidade] = novoPersonagem;
    cadastro->quantidade++;

    return SUCESSO;
}

//retorna o personagem inteiro
//é um ponteiro para ser útil
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

//ponteiro pra alterar msm
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

    *personagem = novoPersonagem;

    return SUCESSO;
}


//traduz para usar no printf
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


//olha que coisa linda
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