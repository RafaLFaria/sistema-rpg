/* 
 * Arquivo: personagem.c
 * Descrição: Implementação do núcleo funcional do sistema[cite: 1].
 * Conteúdo planeado:
 * - Funções do CRUD (cadastrar, alterar, buscar, remover, listar) operando sobre o endereço do cadastro[cite: 1].
 * - Lógica atómica para equipar (troca segura de itens, bloqueio de duas mãos, verificação de espaço na devolução) e desequipar[cite: 1].
 * - Função de cálculo dinâmico dos atributos totais (somando base + bônus de equipamentos ativos)[cite: 1].
 */

 #define CAPACIDADE_MAX 20

 typedef enum {
    HUMANO,
    ELFO,
    ANAO,
    HALFLING
    // Poderá acrescentar outras opções, caso a sua equipa decida implementar raças adicionais
} Raca;

typedef enum{
    GUERREIRO,
    LADINO,
    MAGO,
    CLERIGO,
    BARDO
}Classe;


typedef enum{
    SUCESSO,
    CADASTRO_CHEIO,
    ID_DUPLICADO,
    DADOS_INVALIDOS,
}Estado;


 typedef struct
 {
    int id; //usar static id para autoincrementar
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
 }Personagem;


 /* exemplo:
 #include <stdio.h>
#include <string.h>

// Definimos a estrutura que usará o ID
typedef struct {
    int id;
    char nome[50];
} Aluno;

// Função responsável por gerar o ID único e criar o aluno
Aluno criar_aluno(const char* nome_informado) {
    // O static int começa em 1 e NÃO é reiniciado nas próximas chamadas
    static int id_gerador = 1; 
    
    Aluno novo_aluno;
    novo_aluno.id = id_gerador; // Atribui o ID atual ao novo aluno
    strcpy(novo_aluno.nome, nome_informado);
    
    id_gerador++; // Incrementa o próximo ID para a próxima chamada
    
    return novo_aluno;
}

int main() {
    // Criando vários alunos sem precisar gerenciar o ID manualmente
    Aluno a1 = criar_aluno("Alice");
    Aluno a2 = criar_aluno("Bruno");
    Aluno a3 = criar_aluno("Carlos");

    // Exibindo os resultados
    printf("Aluno: %s | ID único: %d\n", a1.nome, a1.id);
    printf("Aluno: %s | ID único: %d\n", a2.nome, a2.id);
    printf("Aluno: %s | ID único: %d\n", a3.nome, a3.id);

    return 0;
}
*/


typedef struct 
{
    Personagem fichas[CAPACIDADE_MAX];
    int quantidade;
}CadastroPersonagens;

Estado cadastrarPersonagem(CadastroPersonagens *cadastro, Personagem novoPersonagem){
    if(cadastro->quantidade < CAPACIDADE_MAX){
        for (int i = 0; i < cadastro->quantidade; i++)
        {
            if(novoPersonagem.id==cadastro->fichas->id){
                return ID_DUPLICADO;
            }

            if (novoPersonagem.nivel <1 || novoPersonagem.nivel>20)
            {
                return DADOS_INVALIDOS;
            }
            /*
            resto de verificacoes de dados
            */


            return SUCESSO;
        }
        
    }
    else{
        return CADASTRO_CHEIO;
    }
}