#include <stdio.h>
#include <string.h>
#include "personagem.h"

void limparBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void cadastrar()
{
    printf("\n=== CADASTRO DE PERSONAGEM ===\n");
}

void menuPrincipal()
{
    printf("\n===============================\n");
    printf("       SISTEMA DE RPG\n");
    printf("===============================\n");
    printf("1 - Cadastrar personagem\n");
    printf("2 - Consultar personagem por ID\n");
    printf("3 - Alterar personagem\n");
    printf("4 - Remover personagem\n");
    printf("5 - Listar personagens\n");
    printf("6 - Administrar inventario\n");
    printf("7 - Consultar equipamentos\n");
    printf("8 - Equipar item\n");
    printf("9 - Desequipar item\n");
    printf("10 - Exibir atributos totais\n");
    printf("0 - Encerrar\n");
    printf("===============================\n");
    printf("Opcao: ");
}

int main()
{
    CadastroPersonagens cadastro;
    int opcao;

    inicializarCadastro(&cadastro);

    do
    {
        menuPrincipal();

        if (scanf("%d", &opcao) != 1)
        {
            printf("Opcao invalida.\n");
            limparBuffer();
            continue;
        }

        limparBuffer();

        switch (opcao)
        {
        case 1:
        {
            int opcaoRaca, opcaoClasse;
            Personagem novo;

            printf("\n=== CADASTRAR PERSONAGEM ===\n");

            printf("ID: ");
            scanf("%d", &novo.id);
            limparBuffer();

            printf("Nome: ");
            fgets(novo.nome, sizeof(novo.nome), stdin);
            novo.nome[strcspn(novo.nome, "\n")] = '\0';

            printf("\nRaca:\n");
            printf("0 - Humano\n");
            printf("1 - Elfo\n");
            printf("2 - Anao\n");
            printf("3 - Halfling\n");
            printf("4 - Orc\n");
            printf("Opcao: ");

            scanf("%d", &opcaoRaca);

            novo.raca = (Raca)(opcaoRaca);


            printf("\nClasse:\n");
            printf("0 - Guerreiro\n");
            printf("1 - Ladino\n");
            printf("2 - Mago\n");
            printf("3 - Clerigo\n");
            printf("4 - Bardo\n");
            printf("Opcao: ");

            scanf("%d", &opcaoClasse);

            novo.classe = (Classe)(opcaoClasse);


            printf("\nNivel: ");
            scanf("%d", &novo.nivel);

            printf("Pontos de vida maximos: ");
            scanf("%d", &novo.vidaMaxima);

            printf("Pontos de vida atuais: ");
            scanf("%d", &novo.hp);

            printf("Ataque: ");
            scanf("%d", &novo.ataque);

            printf("Defesa: ");
            scanf("%d", &novo.defesa);

            printf("Iniciativa: ");
            scanf("%d", &novo.iniciativa);

            printf("Poder: ");
            scanf("%d", &novo.poder);

            limparBuffer();

            Estado resultado = cadastrarPersonagem(&cadastro, novo);

            switch (resultado)
            {
            case SUCESSO:
                printf("\nPersonagem cadastrado com sucesso!\n");
                break;

            case CADASTRO_CHEIO:
                printf("\nErro: cadastro cheio.\n");
                break;

            case ID_DUPLICADO:
                printf("\nErro: este ID ja esta cadastrado.\n");
                break;

            case DADOS_INVALIDOS:
                printf("\nErro: dados invalidos.\n");
                break;

            default:
                printf("\nErro desconhecido.\n");
            }

            break;
        }

        case 2:
        {
            int id;

            printf("\n=== CONSULTAR PERSONAGEM ===\n");
            printf("ID: ");
            scanf("%d", &id);
            limparBuffer();

            Personagem *p = buscarPersonagem(&cadastro, id);

            if (p == NULL)
            {
                printf("Personagem nao encontrado.\n");
            }
            else
            {
                printf("\nID: %d\n", p->id);
                printf("Nome: %s\n", p->nome);
                printf("Raca: %s\n", nomeRaca(p->raca));
                printf("Classe: %s\n", nomeClasse(p->classe));
                printf("Nivel: %d\n", p->nivel);
                printf("PV: %d/%d\n", p->hp, p->vidaMaxima);
                printf("Ataque: %d\n", p->ataque);
                printf("Defesa: %d\n", p->defesa);
                printf("Iniciativa: %d\n", p->iniciativa);
                printf("Poder: %d\n", p->poder);
            }

            break;
        }

        case 3:
        {
            int id;

            printf("\n=== ALTERAR PERSONAGEM ===\n");
            printf("ID do personagem: ");
            scanf("%d", &id);
            limparBuffer();

            Personagem *existente = buscarPersonagem(&cadastro, id);

            if (existente == NULL)
            {
                printf("Personagem nao encontrado.\n");
                break;
            }

            Personagem novo = *existente;

            printf("Novo nome: ");
            fgets(novo.nome, sizeof(novo.nome), stdin);
            novo.nome[strcspn(novo.nome, "\n")] = '\0';

            printf("Nova raca (0-Humano, 1-Elfo, 2-Anao, 3-Halfling): ");
            scanf("%d", (int *)&novo.raca);

            printf("Nova classe (0-Guerreiro, 1-Ladino, 2-Mago, 3-Clerigo, 4-Bardo): ");
            scanf("%d", (int *)&novo.classe);

            printf("Novo nivel: ");
            scanf("%d", &novo.nivel);

            printf("Novos PV maximos: ");
            scanf("%d", &novo.vidaMaxima);

            printf("Novos PV atuais: ");
            scanf("%d", &novo.hp);

            printf("Novo ataque: ");
            scanf("%d", &novo.ataque);

            printf("Nova defesa: ");
            scanf("%d", &novo.defesa);

            printf("Nova iniciativa: ");
            scanf("%d", &novo.iniciativa);

            printf("Novo poder: ");
            scanf("%d", &novo.poder);

            limparBuffer();

            Estado resultado = alterarPersonagem(&cadastro, id, novo);

            if (resultado == SUCESSO)
                printf("Personagem alterado com sucesso!\n");
            else if (resultado == ID_DUPLICADO)
                printf("Erro: ID duplicado.\n");
            else if (resultado == DADOS_INVALIDOS)
                printf("Erro: dados invalidos.\n");
            else
                printf("Personagem nao encontrado.\n");

            break;
        }

        case 4:
        {
            int id;

            printf("\n=== REMOVER PERSONAGEM ===\n");
            printf("ID: ");
            scanf("%d", &id);
            limparBuffer();

            Estado resultado = removerPersonagem(&cadastro, id);

            if (resultado == SUCESSO)
                printf("Personagem removido com sucesso!\n");
            else
                printf("Personagem nao encontrado.\n");

            break;
        }

        case 5:
            printf("\n=== PERSONAGENS CADASTRADOS ===\n");
            listarPersonagens(&cadastro);
            break;

        case 6:
        {
            int idPers;
            printf("\n=== ADMINISTRAR INVENTARIO ===\n");
            printf("ID do personagem: ");
            scanf("%d", &idPers);
            limparBuffer();

            Personagem *p = buscarPersonagem(&cadastro, idPers);
            if (p == NULL)
            {
                printf("Erro: Personagem nao encontrado.\n");
                break;
            }

            int subOpcao;
            do
            {
                printf("\n--- MOCHILA DE %s (Ocupacao: %d/50) ---\n", p->nome, calcularOcupacaoInventario(&p->inv));
                printf("1 - Listar itens da mochila\n");
                printf("2 - Adicionar item\n");
                printf("3 - Remover item da mochila\n");
                printf("0 - Voltar ao menu principal\n");
                printf("Opcao: ");
                scanf("%d", &subOpcao);
                limparBuffer();

                if (subOpcao == 1)
                {
                    listarInventario(&p->inv);
                }
                else if (subOpcao == 2)
                {
                    Item novo;
                    printf("ID do item: ");
                    scanf("%d", &novo.id);
                    limparBuffer();

                    printf("Nome do item: ");
                    fgets(novo.nome, sizeof(novo.nome), stdin);
                    novo.nome[strcspn(novo.nome, "\n")] = '\0';

                    printf("Tipo (0-Elmo, 1-Peitoral, 2-Manoplas, 3-Calca, 4-Botas, 5-Anel, 6-Colar, 7-Cinto, 8-Arma 1 Mao, 9-Arma 2 Maos): ");
                    int tipoInt;
                    scanf("%d", &tipoInt);
                    novo.tipo = (TipoItem)tipoInt;

                    printf("Espacos consumidos (1 a 50): ");
                    scanf("%d", &novo.espacos);

                    printf("Bonus Ataque: ");
                    scanf("%d", &novo.bonusAtaque);
                    printf("Bonus Defesa: ");
                    scanf("%d", &novo.bonusDefesa);
                    printf("Bonus Vida: ");
                    scanf("%d", &novo.bonusVida);
                    printf("Bonus Iniciativa: ");
                    scanf("%d", &novo.bonusIniciativa);
                    printf("Poder: ");
                    scanf("%d", &novo.poder);
                    limparBuffer();

                    Estado res = adicionarItemInventario(&p->inv, novo);
                    if (res == SUCESSO)
                    {
                        printf("Item adicionado a mochila com sucesso!\n");
                    }
                    else if (res == DADOS_INVALIDOS)
                    {
                        printf("Erro: Dados invalidos (verifique se os espacos estao entre 1 e 50).\n");
                    }
                    else if (res == ID_DUPLICADO)
                    {
                        printf("Erro: Ja existe um item com este ID na mochila.\n");
                    }
                    else if (res == INVENTARIO_SEM_ESPACO)
                    {
                        printf("Erro: Inventario sem espaco suficiente (Ultrapassaria 50 espacos)!\n");
                    }
                    else
                    {
                        printf("Erro ao adicionar item.\n");
                    }
                }
                else if (subOpcao == 3)
                {
                    int idItemRem;
                    printf("ID do item a remover: ");
                    scanf("%d", &idItemRem);
                    limparBuffer();

                    Estado res = removerItemInventario(&p->inv, idItemRem);
                    if (res == SUCESSO)
                    {
                        printf("Item removido com sucesso!\n");
                    }
                    else
                    {
                        printf("Erro: Item nao encontrado na mochila.\n");
                    }
                }

            } while (subOpcao != 0);

            break;
        }

        case 7:
        {
            int id;
            printf("\n=== CONSULTAR EQUIPAMENTOS ===\n");
            printf("ID do personagem: ");
            scanf("%d", &id);
            limparBuffer();

            if (consultarEquipamentos(&cadastro, id) == NAO_ENCONTRADO)
            {
                printf("Personagem nao encontrado.\n");
            }
            break;
        }

        case 8:
        {
            int idPers, idItem;
            printf("\n=== EQUIPAR ITEM ===\n");
            printf("ID do personagem: ");
            scanf("%d", &idPers);
            printf("ID do item na mochila: ");
            scanf("%d", &idItem);
            limparBuffer();

            Estado res = equiparItem(&cadastro, idPers, idItem);

            if (res == SUCESSO)
                printf("Item equipado com sucesso!\n");
            else if (res == NAO_ENCONTRADO)
                printf("Erro: Personagem nao encontrado.\n");
            else if (res == ITEM_NAO_ENCONTRADO)
                printf("Erro: Item nao encontrado na mochila.\n");
            else if (res == CONFLITO_DUAS_MAOS)
                printf("Erro: Conflito com arma de duas maos (maos ocupadas)!\n");
            else if (res == INVENTARIO_SEM_ESPACO)
                printf("Erro: Sem espaco na mochila para guardar o item trocado!\n");
            else if (res == JA_EQUIPADO)
                printf("Erro: Posicao (ou ambas as maos) ja ocupada!\n");
            else
                printf("Erro: Item incompativel ou dados invalidos.\n");

            break;
        }

        case 9:
        {
            int idPers, idItem;
            printf("\n=== DESEQUIPAR ITEM ===\n");
            printf("ID do personagem: ");
            scanf("%d", &idPers);
            printf("ID do item equipado: ");
            scanf("%d", &idItem);
            limparBuffer();

            Estado res = desequiparItem(&cadastro, idPers, idItem);

            if (res == SUCESSO)
                printf("Item desequipado e devolvido a mochila!\n");
            else if (res == NAO_ENCONTRADO)
                printf("Erro: Personagem nao encontrado.\n");
            else if (res == ITEM_NAO_ENCONTRADO)
                printf("Erro: Este item nao esta equipado no personagem.\n");
            else if (res == INVENTARIO_SEM_ESPACO)
                printf("Erro: Inventario sem espaco livre suficiente para desequipar!\n");
            else
                printf("Erro ao desequipar item.\n");

            break;
        }

        case 10:
        {
            int id;
            printf("\n=== ATRIBUTOS TOTAIS ===\n");
            printf("ID do personagem: ");
            scanf("%d", &id);
            limparBuffer();

            if (exibirAtributosTotais(&cadastro, id) == NAO_ENCONTRADO)
            {
                printf("Personagem nao encontrado.\n");
            }
            break;
        }

        case 0:
            printf("\nEncerrando programa...\n");
            break;

        default:
            printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}