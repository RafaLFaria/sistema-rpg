/* 
 * Arquivo: main.c
 * Descrição: Programa cliente de demonstração interativa[cite: 1].
 * Conteúdo planeado:
 * - Inclusão exclusiva de "personagem.h" (sem acessos diretos às structs internas)[cite: 1].
 * - Laço de repetição com o menu de opções (1 a 10, e 0 para sair)[cite: 1].
 * - Captura segura de entrada textual do utilizador (evitando gets para prevenir estouro de buffer) e tratamento das mensagens de retorno[cite: 1].
 */

 /*
 ESTRUTURA BASICA DO MAIN:

 #include <stdio.h>
#include "personagem.h"

int main() {
    CadastroPersonagens meuCadastro;
    // Função hipotética para garantir que a quantidade comece em 0
    inicializarCadastro(&meuCadastro); 

    int opcao;
    do {
        // Exibir menu de 1 a 10 e 0 para encerrar
        printf("1 - Cadastrar personagem\n");
        // ...
        printf("0 - Encerrar\n");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            Personagem novo;
            // Aqui você lê os dados digitados pelo utilizador para a variável 'novo'
            
            // Chama a função passando o endereço do cadastro
            Estado resultado = cadastrarPersonagem(&meuCadastro, novo);
            
            // O main apenas reage ao código de retorno
            if (resultado == SUCESSO) {
                printf("Aventureiro registado com sucesso!\n");
            } else if (resultado == CADASTRO_CHEIO) {
                printf("Erro: Limite de aventureiros atingido.\n");
            } else if (resultado == ID_DUPLICADO) {
                printf("Erro: Este ID já existe.\n");
            }
        }
        // ... outras opções
        
    } while (opcao != 0);

    return 0;
}
 
 
 */