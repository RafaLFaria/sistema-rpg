#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#define CAPACIDADE_MAX 20

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
    SUCESSO,
    CADASTRO_CHEIO,
    ID_DUPLICADO,
    DADOS_INVALIDOS,
    NAO_ENCONTRADO
} Estado;

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

const char *nomeRaca(Raca raca);
const char *nomeClasse(Classe classe);

#endif