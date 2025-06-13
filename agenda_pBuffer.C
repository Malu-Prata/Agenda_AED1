#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME 50
#define EMAIL 50
#define AGE 10
#define SEARCH 50
#define PERSON (NAME + AGE + EMAIL)

// posições 
#define POS_TOTAL 0 // total de pessoas
#define POS_OPCAO 1 // opção do menu
#define POS_INDICE 2 // índice encontrado (remover)
#define POS_I 3 // índice para iteração
#define POS_FOUND 4 // contador de encontrados (busca)

#define QTD_INTS 5
#define FIXO (sizeof(int) * QTD_INTS + SEARCH)

void *pBuffer;

// Funções
void addPerson();
void remPerson();
void searchPerson();
void listPerson();

void addPerson() {
        int *totalPerson = (int *)pBuffer + POS_TOTAL;

        void *newBuffer = realloc(pBuffer, FIXO + (*totalPerson + 1) * PERSON);
            if (!newBuffer) {
            printf("Erro ao realocar memória!\n");
            exit(1);
            }

    pBuffer = newBuffer;
    totalPerson = (int *)pBuffer + POS_TOTAL;

    char *novaPessoa = (char *)pBuffer + FIXO + (*totalPerson) * PERSON;
    char *nome = novaPessoa;
    char *idade = nome + NAME;
    char *email = idade + AGE;

        printf("Digite o nome: ");
        fgets(nome, NAME, stdin);
        nome[strcspn(nome, "\n")] = 0;

        printf("Digite a idade: ");
        fgets(idade, AGE, stdin);
        idade[strcspn(idade, "\n")] = 0;

        printf("Digite o email: ");
        fgets(email, EMAIL, stdin);
        email[strcspn(email, "\n")] = 0;

        (*totalPerson)++;
        printf("Nova pessoa adicionada com sucesso!\n");
}

void remPerson() {
    int *totalPerson = (int *)pBuffer + POS_TOTAL;
    int *foundIndex = (int *)pBuffer + POS_INDICE;
    int *i = (int *)pBuffer + POS_I;
    char *inputBuffer = (char *)pBuffer + sizeof(int) * QTD_INTS;

        if (*totalPerson == 0) {
        printf("Não foi possível remover, pois a pessoa não está cadastrada.\n");
        return;
        }

    printf("Digite o nome da pessoa para ser removida: ");
    fgets(inputBuffer, SEARCH, stdin);
    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

    *foundIndex = -1;

        for (*i = 0; *i < *totalPerson; (*i)++) {
        char *currentPerson = (char *)pBuffer + FIXO + (*i) * PERSON;
        char *currentName = currentPerson;

            if (strcmp(currentName, inputBuffer) == 0) {
            *foundIndex = *i;
            break;
            }
        }

        if (*foundIndex == -1) {
        printf("'%s' não encontrada. Tente novamente\n", inputBuffer);
        return;
        }

    printf("'%s' removido com sucesso!\n", inputBuffer);

    char *removedPerson = (char *)pBuffer + FIXO + (*foundIndex) * PERSON;
    char *nextPerson = removedPerson + PERSON;

        memmove(removedPerson, nextPerson, (*totalPerson - *foundIndex - 1) * PERSON);
        (*totalPerson)--;

    void *newBuffer = realloc(pBuffer, FIXO + (*totalPerson) * PERSON);
            if (!newBuffer) {
            printf("Erro ao realocar memória\n");
            exit(1);
            }
    pBuffer = newBuffer;
}

void searchPerson() {
    int *totalPerson = (int *)pBuffer + POS_TOTAL;
        if (*totalPerson == 0) {
        printf("Nenhuma pessoa cadastrada para buscar.\n");
        return;
        }

    char *searchName = (char *)pBuffer + sizeof(int) * QTD_INTS;
    int *found = (int *)pBuffer + POS_FOUND;
    int *i = (int *)pBuffer + POS_I;

    printf("Digite o nome da pessoa a ser buscada: ");
    fgets(searchName, SEARCH, stdin);
    searchName[strcspn(searchName, "\n")] = 0;

        *found = 0;

            for (*i = 0; *i < *totalPerson; (*i)++) {
            char *pessoa = (char *)pBuffer + FIXO + (*i) * PERSON;
            char *nome = pessoa;
            char *idade = nome + NAME;
            char *email = idade + AGE;

                if (strcmp(nome, searchName) == 0) {
                printf("\nPessoa %d encontrada:\n", *i + 1);
                printf("Nome: %s\n", nome);
                printf("Idade: %s\n", idade);
                printf("Email: %s\n", email);
                (*found)++;
                }
            }

        if (*found == 0) {
        printf("Nenhuma pessoa com o nome '%s' encontrada.\n", searchName);
        }
}

void listPerson() {
    int *totalPerson = (int *)pBuffer + POS_TOTAL;
        if (*totalPerson == 0) {
        printf("Nenhuma pessoa cadastrada!\n");
        return;
        }

    int *i = (int *)pBuffer + POS_I;
    printf("\nLista de Pessoas Cadastradas:\n");

        for (*i = 0; *i < *totalPerson; (*i)++) {
        char *pessoa = (char *)pBuffer + FIXO + (*i) * PERSON;
        char *nome = pessoa;
        char *idade = nome + NAME;
        char *email = idade + AGE;

        printf("\nPessoa %d:\n", *i + 1);
        printf("Nome: %s\n", nome);
        printf("Idade: %s\n", idade);
        printf("Email: %s\n", email);
        }
}

int main() {
    pBuffer = malloc(FIXO);
        if (!pBuffer) {
        printf("Erro ao alocar memória inicial!\n");
        return 1;
        }

     *((int *)pBuffer + POS_TOTAL) = 0;

        do {
        int *opcao = (int *)pBuffer + POS_OPCAO;

        printf("\nMenu:\n");
        printf("1- Adicionar pessoa\n");
        printf("2- Remover pessoa\n");
        printf("3- Buscar pessoas\n");
        printf("4- Listar pessoas\n");
        printf("5- Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", opcao);
        getchar(); // limpa o \n

            switch (*opcao) {
            case 1: addPerson(); break;
            case 2: remPerson(); break;
            case 3: searchPerson(); break;
            case 4: listPerson(); break;
            case 5: printf("Encerrando o programa...\n"); break;
            default: printf("Opcao invalida!\n");
            }
        } while (*((int *)pBuffer + POS_OPCAO) != 5);

    free(pBuffer);
    return 0;
}