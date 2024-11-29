#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionarios.h"

#define ARQUIVO_DADOS "funcionarios.txt"
#define MAX_FUNCIONARIOS 100

// Função maiúsculas
void to_uppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32; // Converte para maiúscula
        }
    }
}

// Função carregar
int carregar_dados(Funcionario funcionarios[]) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "rb");

    if (arquivo == NULL) {
        arquivo = fopen(ARQUIVO_DADOS, "wb");
        if (arquivo == NULL) {
            perror("Erro ao criar arquivo");
            exit(1);
        }
        fclose(arquivo);
        return 0;
    }

    int tamanho = fread(funcionarios, sizeof(Funcionario), MAX_FUNCIONARIOS, arquivo);
    fclose(arquivo);
    return tamanho;
}

// Função salvar dados
void salvar_dados(Funcionario funcionarios[], int tamanho) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }
    fwrite(funcionarios, sizeof(Funcionario), tamanho, arquivo);
    fclose(arquivo);
}

// Função próximo ID
int gerar_proximo_id(Funcionario funcionarios[], int tamanho) {
    int maior_id = 0;
    for (int i = 0; i < tamanho; i++) {
        if (funcionarios[i].id > maior_id) {
            maior_id = funcionarios[i].id;
        }
    }
    return maior_id + 1;
}

// Menu
void menu_principal(const char *setor_gerente) {
    int opcao;

    do {
        printf("\n--- Menu Principal (%s) ---\n", setor_gerente);
        printf("1. Cadastrar Novo Funcionario\n");
        printf("2. Editar Funcionario\n");
        printf("3. Pesquisar Funcionario\n");
        printf("4. Demitir Funcionario\n");
        printf("5. Promover Funcionario\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_funcionario(setor_gerente);
            break;
            case 2:
                editar_funcionario(setor_gerente);
            break;
            case 3:
                pesquisar_funcionario();
            break;
            case 4:
                demitir_funcionario(setor_gerente);
            break;
            case 5:
                promover_funcionario(setor_gerente);
            break;
            case 6:
                printf("Saindo...\n");
            break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 6);
}
// Função cadastrar novo funcionário
void cadastrar_funcionario(const char *setor) {
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    int tamanho = carregar_dados(funcionarios);

    Funcionario novo;
    novo.id = gerar_proximo_id(funcionarios, tamanho);

    printf("Digite o nome do funcionario: ");
    scanf(" %[^\n]s", novo.nome);
    to_uppercase(novo.nome);

    printf("Digite a idade do funcionario: ");
    scanf("%d", &novo.idade);

    printf("Digite o salario do funcionario: ");
    scanf("%f", &novo.salario);

    printf("Digite a funcao do funcionario: ");
    scanf(" %[^\n]s", novo.funcao);
    to_uppercase(novo.funcao);

    printf("Digite o estado (UF): ");
    scanf(" %[^\n]s", novo.estado);
    to_uppercase(novo.estado);

    printf("Digite a cidade: ");
    scanf(" %[^\n]s", novo.cidade);
    to_uppercase(novo.cidade);

    printf("Digite o bairro: ");
    scanf(" %[^\n]s", novo.bairro);
    to_uppercase(novo.bairro);

    printf("Digite a rua: ");
    scanf(" %[^\n]s", novo.rua);
    to_uppercase(novo.rua);

    printf("Digite o numero da casa ou apartamento: ");
    scanf("%d", &novo.numero);

    strcpy(novo.setor, setor);
    to_uppercase(novo.setor);

    funcionarios[tamanho] = novo;
    tamanho++;

    salvar_dados(funcionarios, tamanho);
    printf("Funcionario cadastrado com sucesso! ID: %d\n", novo.id);
}

// Função editar funcionário
void editar_funcionario(const char *setor) {
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    int tamanho = carregar_dados(funcionarios);
    int id, encontrado = 0;

    printf("Digite o ID do funcionario para editar: ");
    scanf("%d", &id);

    for (int i = 0; i < tamanho; i++) {
        if (funcionarios[i].id == id && strcmp(funcionarios[i].setor, setor) == 0) {
            encontrado = 1;
            printf("\nFuncionario encontrado: %s (Setor: %s)\n", funcionarios[i].nome, funcionarios[i].setor);

            int opcao;
            do {
                printf("\n--- Menu de Edicao ---\n");
                printf("1. Editar Nome\n");
                printf("2. Editar Idade\n");
                printf("3. Editar Salario\n");
                printf("4. Editar Funcao\n");
                printf("5. Editar Estado\n");
                printf("6. Editar Cidade\n");
                printf("7. Editar Bairro\n");
                printf("8. Editar Rua\n");
                printf("9. Editar Numero da Casa\n");
                printf("10. Sair da Edicao\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        printf("Digite o novo nome: ");
                        scanf(" %[^\n]s", funcionarios[i].nome);
                        to_uppercase(funcionarios[i].nome);
                        break;
                    case 2:
                        printf("Digite a nova idade: ");
                        scanf("%d", &funcionarios[i].idade);
                        break;
                    case 3:
                        printf("Digite o novo salario: ");
                        scanf("%f", &funcionarios[i].salario);
                        break;
                    case 4:
                        printf("Digite a nova funcao: ");
                        scanf(" %[^\n]s", funcionarios[i].funcao);
                        to_uppercase(funcionarios[i].funcao);
                        break;
                    case 5:
                        printf("Digite o novo estado (UF): ");
                        scanf(" %[^\n]s", funcionarios[i].estado);
                        to_uppercase(funcionarios[i].estado);
                        break;
                    case 6:
                        printf("Digite a nova cidade: ");
                        scanf(" %[^\n]s", funcionarios[i].cidade);
                        to_uppercase(funcionarios[i].cidade);
                        break;
                    case 7:
                        printf("Digite o novo bairro: ");
                        scanf(" %[^\n]s", funcionarios[i].bairro);
                        to_uppercase(funcionarios[i].bairro);
                        break;
                    case 8:
                        printf("Digite a nova rua: ");
                        scanf(" %[^\n]s", funcionarios[i].rua);
                        to_uppercase(funcionarios[i].rua);
                        break;
                    case 9:
                        printf("Digite o novo numero da casa ou apartamento: ");
                        scanf("%d", &funcionarios[i].numero);
                        break;
                    case 10:
                        printf("Saindo da edicao...\n");
                        break;
                    default:
                        printf("Opcao invalida! Tente novamente.\n");
                }
            } while (opcao != 10);

            salvar_dados(funcionarios, tamanho);
            printf("Alteracoes salvas com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionario nao encontrado ou fora do setor permitido.\n");
    }
}

// Função pesquisa
void pesquisar_funcionario() {
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    int tamanho = carregar_dados(funcionarios);
    int opcao;

    printf("\n--- Pesquisa de Funcionarios ---\n");
    printf("1. Pesquisar por ID\n");
    printf("2. Pesquisar por Setor\n");
    printf("3. Listar Todos\n");
    printf("4. Pesquisar por Nome\n");
    printf("5. Pesquisar por Rua\n");
    printf("6. Pesquisar por Bairro\n");
    printf("7. Pesquisar por Estado (UF)\n");
    printf("8. Pesquisar por Cidade\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        int id;
        printf("Digite o ID: ");
        scanf("%d", &id);

        for (int i = 0; i < tamanho; i++) {
            if (funcionarios[i].id == id) {
                printf("\n--- Funcionario Encontrado ---\n");
                printf("ID: %d\n", funcionarios[i].id);
                printf("Nome: %s\n", funcionarios[i].nome);
                printf("Idade: %d\n", funcionarios[i].idade);
                printf("Salario: %.2f\n", funcionarios[i].salario);
                printf("Funcao: %s\n", funcionarios[i].funcao);
                printf("Setor: %s\n", funcionarios[i].setor);
                printf("Endereco: Rua %s, Numero %d, Bairro %s, Cidade %s, Estado %s\n",
                       funcionarios[i].rua, funcionarios[i].numero, funcionarios[i].bairro,
                       funcionarios[i].cidade, funcionarios[i].estado);
                return;
            }
        }
        printf("Funcionario com ID %d nao encontrado.\n", id);

    } else if (opcao == 2) {
        char setor[20];
        printf("Digite o setor: ");
        scanf(" %[^\n]s", setor);
        to_uppercase(setor);

        printf("\n--- Funcionarios do Setor %s ---\n", setor);
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(funcionarios[i].setor, setor) == 0) {
                printf("ID: %d, Nome: %s, Funcao: %s, Salario: %.2f\n",
                       funcionarios[i].id, funcionarios[i].nome,
                       funcionarios[i].funcao, funcionarios[i].salario);
            }
        }

    } else if (opcao == 3) {
        printf("\n--- Todos os Funcionarios ---\n");
        for (int i = 0; i < tamanho; i++) {
            printf("ID: %d\n", funcionarios[i].id);
            printf("Nome: %s\n", funcionarios[i].nome);
            printf("Idade: %d\n", funcionarios[i].idade);
            printf("Salario: %.2f\n", funcionarios[i].salario);
            printf("Funcao: %s\n", funcionarios[i].funcao);
            printf("Setor: %s\n", funcionarios[i].setor);
            printf("Endereco: Rua %s, Numero %d, Bairro %s, Cidade %s, Estado %s\n\n",
                   funcionarios[i].rua, funcionarios[i].numero, funcionarios[i].bairro,
                   funcionarios[i].cidade, funcionarios[i].estado);
        }

    } else if (opcao == 4) {  // Pesquisar Nome
        char nome[50];
        printf("Digite parte ou o primeiro nome do funcionario: ");
        scanf(" %[^\n]s", nome);
        to_uppercase(nome);

        printf("\n--- Funcionarios Encontrados com Nome '%s' ---\n", nome);
        for (int i = 0; i < tamanho; i++) {
            if (strstr(funcionarios[i].nome, nome) != NULL) {
                printf("ID: %d, Nome: %s, Funcao: %s, Salario: %.2f\n",
                       funcionarios[i].id, funcionarios[i].nome,
                       funcionarios[i].funcao, funcionarios[i].salario);
            }
        }

    } else if (opcao == 5) {  // Pesquisar Rua
        char rua[100];
        printf("Digite o nome da rua: ");
        scanf(" %[^\n]s", rua);
        to_uppercase(rua);

        printf("\n--- Funcionarios Encontrados na Rua '%s' ---\n", rua);
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(funcionarios[i].rua, rua) == 0) {
                printf("ID: %d, Nome: %s, Funcao: %s, Salario: %.2f\n",
                       funcionarios[i].id, funcionarios[i].nome,
                       funcionarios[i].funcao, funcionarios[i].salario);
            }
        }

    } else if (opcao == 6) {  // Pesquisar Bairro
        char bairro[50];
        printf("Digite o nome do bairro: ");
        scanf(" %[^\n]s", bairro);
        to_uppercase(bairro);

        printf("\n--- Funcionarios Encontrados no Bairro '%s' ---\n", bairro);
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(funcionarios[i].bairro, bairro) == 0) {
                printf("ID: %d, Nome: %s, Funcao: %s, Salario: %.2f\n",
                       funcionarios[i].id, funcionarios[i].nome,
                       funcionarios[i].funcao, funcionarios[i].salario);
            }
        }

    } else if (opcao == 7) {  // Pesquisar Estado
        char estado[3];
        printf("Digite o estado (UF): ");
        scanf(" %[^\n]s", estado);
        to_uppercase(estado);

        printf("\n--- Funcionarios Encontrados no Estado '%s' ---\n", estado);
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(funcionarios[i].estado, estado) == 0) {
                printf("ID: %d, Nome: %s, Funcao: %s, Salario: %.2f\n",
                       funcionarios[i].id, funcionarios[i].nome,
                       funcionarios[i].funcao, funcionarios[i].salario);
            }
        }

    } else if (opcao == 8) {  // Pesquisar Cidade
        char cidade[50];
        printf("Digite o nome da cidade: ");
        scanf(" %[^\n]s", cidade);
        to_uppercase(cidade);

        printf("\n--- Funcionarios Encontrados na Cidade '%s' ---\n", cidade);
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(funcionarios[i].cidade, cidade) == 0) {
                printf("ID: %d, Nome: %s, Funcao: %s, Salario: %.2f\n",
                       funcionarios[i].id, funcionarios[i].nome,
                       funcionarios[i].funcao, funcionarios[i].salario);
            }
        }

    } else {
        printf("Opcao invalida! Tente novamente.\n");
    }
}

// Função demitir (Excluir)
void demitir_funcionario(const char *setor) {
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    int tamanho = carregar_dados(funcionarios);
    int id, encontrado = 0;

    printf("Digite o ID do funcionario para demitir: ");
    scanf("%d", &id);

    for (int i = 0; i < tamanho; i++) {
        if (funcionarios[i].id == id && strcmp(funcionarios[i].setor, setor) == 0) {
            encontrado = 1;
            printf("Funcionario encontrado: %s (Setor: %s)\n", funcionarios[i].nome, funcionarios[i].setor);

            char motivo[100];
            printf("Digite o motivo da demissao: ");
            scanf(" %[^\n]s", motivo);

            printf("Confirmar demissao? (1-Sim, 0-Nao): ");
            int confirmar;
            scanf("%d", &confirmar);

            if (confirmar == 1) {
                for (int j = i; j < tamanho - 1; j++) {
                    funcionarios[j] = funcionarios[j + 1];
                }
                tamanho--;
                salvar_dados(funcionarios, tamanho);
                printf("Funcionario demitido com sucesso pelo motivo: %s\n", motivo);
            } else {
                printf("Operacao cancelada.\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionario nao encontrado ou fora do setor permitido.\n");
    }
}
void promover_funcionario(const char *setor) {
    Funcionario funcionarios[MAX_FUNCIONARIOS];
    int tamanho = carregar_dados(funcionarios);
    int id, encontrado = 0;

    printf("Digite o ID do funcionario a ser promovido: ");
    scanf("%d", &id);

    for (int i = 0; i < tamanho; i++) {
        if (funcionarios[i].id == id && strcmp(funcionarios[i].setor, setor) == 0) {
            encontrado = 1;
            printf("\nFuncionario encontrado: %s\n", funcionarios[i].nome);

            // Alterar função
            printf("Digite a nova funcao: ");
            scanf(" %[^\n]s", funcionarios[i].funcao);
            to_uppercase(funcionarios[i].funcao);

            // Alterar salário
            printf("Digite o novo salario: ");
            scanf("%f", &funcionarios[i].salario);

            salvar_dados(funcionarios, tamanho);
            printf("Funcionario promovido com sucesso!\n");
            printf("Novo cargo: %s, Novo salario: %.2f\n", funcionarios[i].funcao, funcionarios[i].salario);
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionario nao encontrado ou fora do setor permitido.\n");
    }
}