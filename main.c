#include <stdio.h>
#include <string.h>
#include "funcionarios.h"

int main() {
    char usuario[20], senha[20];

    while (1) { //login
        printf("--- Sistema de Controle de Funcionarios ---\n");
        printf("Login(Escreva o login em maiusculo22): ");
        scanf(" %[^\n]s", usuario);
        printf("Senha: ");
        scanf(" %[^\n]s", senha);

        // Validação do login
        if ((strcmp(usuario, "SEGURANCA") == 0 && strcmp(senha, "1") == 0) ||
            (strcmp(usuario, "DESENVOLVIMENTO") == 0 && strcmp(senha, "1") == 0) ||
            (strcmp(usuario, "INFRAESTRUTURA") == 0 && strcmp(senha, "1") == 0)) {
            printf("Login bem-sucedido! Bem-vindo, %s.\n", usuario);
            menu_principal(usuario); // Chama o menu principal
            break; // Sai do loop caso o login seja bem-sucedido
            } else {
                printf("\nErro: Login ou senha incorretos. Tente novamente.\n\n");
            }
    }

    return 0;
}
