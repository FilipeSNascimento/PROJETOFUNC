#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include "funcionarios.h"

// Função declarada externamente
void to_uppercase(char *str);

#define MAX_USUARIOS 100
#define ARQUIVO_USUARIOS "usuarios.txt"

typedef struct {
    char usuario[20];
    char senha[20];
} Usuario;

Usuario usuarios[MAX_USUARIOS];
int total_usuarios = 0;

// Carrega os usuarios do arquivo
void carregar_usuarios() {
    FILE *file = fopen(ARQUIVO_USUARIOS, "r");
    if (file == NULL) {
        printf("Aviso: Arquivo '%s' nao encontrado. Sera criado ao salvar usuarios.\n", ARQUIVO_USUARIOS);
        return;
    }

    total_usuarios = 0;
    while (fscanf(file, "%s %s", usuarios[total_usuarios].usuario, usuarios[total_usuarios].senha) == 2) {
        total_usuarios++;
    }

    fclose(file);
}

// Salva os usuarios no arquivo
void salvar_usuarios() {
    FILE *file = fopen(ARQUIVO_USUARIOS, "w");
    if (file == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo '%s' para escrita.\n", ARQUIVO_USUARIOS);
        return;
    }

    for (int i = 0; i < total_usuarios; i++) {
        fprintf(file, "%s %s\n", usuarios[i].usuario, usuarios[i].senha);
    }

    fclose(file);
}

// Cadastra um novo usuario
void cadastrar_usuario() {
    if (total_usuarios >= MAX_USUARIOS) {
        printf("\nErro: Limite de usuarios atingido.\n");
        return;
    }

    char novo_usuario[20], nova_senha[20];
    printf("\n--- Cadastro de Novo Usuario ---\n");
    printf("Digite o nome do novo usuario: ");
    scanf(" %[^\n]s", novo_usuario);

    // Converte o nome do usuario para maiusculas
    to_uppercase(novo_usuario);

    printf("Digite a senha do novo usuario: ");
    scanf(" %[^\n]s", nova_senha);

    // Adiciona o novo usuario ao array
    strcpy(usuarios[total_usuarios].usuario, novo_usuario);
    strcpy(usuarios[total_usuarios].senha, nova_senha);
    total_usuarios++;

    salvar_usuarios(); // Salva os dados no arquivo
    printf("\nUsuario '%s' cadastrado com sucesso e salvo no arquivo!\n", novo_usuario);
}

// Valida o login
int validar_login(char *usuario, char *senha) {
    for (int i = 0; i < total_usuarios; i++) {
        if (strcmp(usuarios[i].usuario, usuario) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            return i; // Retorna o indice do usuario
        }
    }
    return -1; // Login invalido
}

// Função para redefinir a senha
void esqueci_senha() {
    char login[20], nova_senha[20];

    printf("\n--- Esqueci a Senha ---\n");
    printf("Digite seu login: ");
    scanf(" %[^\n]s", login);

    // Converte o login para maiúsculas
    to_uppercase(login);

    // Verifica se o login existe
    int encontrado = -1;
    for (int i = 0; i < total_usuarios; i++) {
        if (strcmp(usuarios[i].usuario, login) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        printf("Digite sua nova senha: ");
        scanf(" %[^\n]s", nova_senha);

        // Atualiza a senha no array de usuários
        strcpy(usuarios[encontrado].senha, nova_senha);
        salvar_usuarios(); // Salva os dados atualizados no arquivo

        printf("\nSenha redefinida com sucesso para o usuario '%s'.\n", login);
    } else {
        printf("\nErro: Usuario '%s' nao encontrado.\n", login);
    }
}

int main() {
    carregar_usuarios(); // Carrega os usuarios

    char usuario[20], senha[20];
    int continuar = 1;

    while (continuar) { // Loop do sistema
        printf("--- Sistema de Controle de Funcionarios ---\n");
        printf("Login (Escreva o login em maiusculas): ");
        scanf(" %[^\n]s", usuario);
        printf("Senha: ");
        scanf(" %[^\n]s", senha);

        int indice_usuario = validar_login(usuario, senha);

        if (indice_usuario != -1) {
            printf("Login bem-sucedido! Bem-vindo, %s.\n", usuario);

            // Verifica se e o administrador
            if (strcmp(usuario, "ADMIN") == 0) {
                int opcao;
                while (1) {
                    printf("\n--- Menu do Administrador ---\n");
                    printf("1. Cadastrar novo usuario\n");
                    printf("2. Voltar ao login\n");
                    printf("3. Sair\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcao);

                    if (opcao == 1) {
                        cadastrar_usuario();
                    } else if (opcao == 2) {
                        printf("Voltando ao login...\n");
                        break; // Sai para o loop principal e volta ao login
                    } else if (opcao == 3) {
                        printf("Saindo do sistema...\n");
                        continuar = 0; // Encerra o programa
                        break;
                    } else {
                        printf("\nOpcao invalida. Tente novamente.\n");
                    }
                }
            } else {
                menu_principal(usuario); // Chama o menu principal para outros usuarios
            }
        } else {
            printf("\nErro: Login ou senha incorretos.\n");

            // Menu de opções após erro no login
            int opcao;
            printf("\n--- Opcao de Recuperacao ---\n");
            printf("1. Tentar novamente\n");
            printf("2. Esqueci a senha\n");
            printf("3. Sair\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            if (opcao == 1) {continue;
                // Volta para o login
            } else if (opcao == 2) {
                esqueci_senha(); // Chama a função de redefinição de senha
            } else if (opcao == 3) {
                printf("Saindo do sistema...\n");
                continuar = 0; // Encerra o programa
            } else {
                printf("\nOpcao invalida. Voltando ao menu principal...\n");
            }
        }
    }

    return 0;
}
