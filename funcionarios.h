#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

// Estrutura funcionário
typedef struct {
    int id;
    char nome[50];
    int idade;
    float salario;
    char funcao[50];
    char setor[20];
    char estado[3];
    char cidade[50];
    char bairro[50];
    char rua[100];
    int numero;
} Funcionario;

// Funções
void menu_principal(const char *setor_gerente);
void cadastrar_funcionario(const char *setor);
void editar_funcionario(const char *setor);
void pesquisar_funcionario();
void demitir_funcionario(const char *setor);
void salvar_dados(Funcionario funcionarios[], int tamanho);
int carregar_dados(Funcionario funcionarios[]);
int gerar_proximo_id(Funcionario funcionarios[], int tamanho);
void to_uppercase(char *str);

#endif
