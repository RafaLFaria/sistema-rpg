#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "inventario.h"

#define CAPACIDADE_MAX 20
#define EQUIP_MAX 10

typedef enum {
    HUMANO,
    ELFO,
    ANAO,
    HALFLING
} Raca;

typedef enum {
    GUERREIRO,
    LADINO,
    MAGO,
    CLERIGO,
    BARDO
} Classe;



typedef enum {
    POS_ELMO = 0,
    POS_PEITORAL,
    POS_MANOPLAS,
    POS_CALCA,
    POS_BOTAS,
    POS_ANEL,
    POS_COLAR,
    POS_CINTO,
    POS_MAO_DIREITA,
    POS_MAO_ESQUERDA,
    TOTAL_POSICOES_EQUIP 
} PosicaoEquipamento;

typedef struct {
    int id;
    char nome[50];
    Raca raca;
    Classe classe;
    int nivel;
    int vidaMaxima;
    int hp;
    int ataque;
    int defesa;
    int iniciativa;
    int poder;
    Inventario inv;
    Item equipamento[EQUIP_MAX];
} Personagem;

typedef struct {
    Personagem fichas[CAPACIDADE_MAX];
    int quantidade;
} CadastroPersonagens;

void inicializarCadastro(CadastroPersonagens *cadastro);
Estado cadastrarPersonagem(CadastroPersonagens *cadastro, Personagem novoPersonagem);
Personagem *buscarPersonagem(CadastroPersonagens *cadastro, int id);
Estado removerPersonagem(CadastroPersonagens *cadastro, int id);
Estado alterarPersonagem(CadastroPersonagens *cadastro, int id, Personagem novoPersonagem);
void listarPersonagens(const CadastroPersonagens *cadastro);
int obterQuantidadePErsonagens(const CadastroPersonagens *cadastro);


//equipamentos
Estado consultarEquipamentos(const CadastroPersonagens *cadastro, int idpersonagem);
Estado equiparItem(CadastroPersonagens *cadastro, int idPersonagem, int idItem);
Estado desequiparItem(CadastroPersonagens *cadastro, int idPersonagem, int idItem);

Estado ExibirAtributosTotais();



const char *nomeRaca(Raca raca);
const char *nomeClasse(Classe classe);
const char *nomePosicaoEquipamento(int slot);

#endif