
#ifndef UNTITLED4_CLIENTE_H
#define UNTITLED4_CLIENTE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"

#define tempo_lavagem 30
#define tempo_manutencao 60
int VerificaLogin(CLIENTE_header *lista_Clientes, CLIENTE *C){
    CLIENTE *node = lista_Clientes -> start;
    while (node != NULL){
        if (strcmp(node -> nome, C -> nome) == 0 && strcmp(node -> telemovel, C -> telemovel) == 0 && strlen(C -> telemovel) == 9){
            printf("Login realizado com sucesso!!\n");
            return 1;
        }
        node = node -> prox;
    }
    printf("Nome ou numero de telemovel incorretos.\nSe nao tiver conta Registre-se\n");
    return 0;
}

int VerificaRegistro(CLIENTE_header *lista_Clientes,CLIENTE *C){
    CLIENTE *node = lista_Clientes -> start;
    while (node != NULL){
        if ((strcmp(node -> nome, C -> nome) == 0 || strcmp(node -> telemovel, C -> telemovel) == 0) && strlen(C -> telemovel) == 9){
            printf("Nome ou numero de telemovel ja existentes.\n");
            return 0;
        }
        node = node -> prox;
    }
    printf("Registo realizado com sucesso !\n");
    return 1;
}

int LogIn(CLIENTE_header *lista_Clientes,CLIENTE *C){
    printf("Introduza o seu nome?\n");
    getchar();
    fgets(C->nome, 50, stdin);
    printf("Introduza o seu numeoro de telemovel?\n");
    fgets(C->telemovel, 15, stdin);
    if (VerificaLogin(lista_Clientes,C)){
        return 1;
    }
    return 0;
}

int Registrar(CLIENTE_header *lista_Clientes,CLIENTE *C){
    printf("Introduza o seu nome?\n");
    getchar();
    fgets(C->nome, 50, stdin);
    printf("Introduza o seu numeoro de telemovel?\n");
    fgets(C->telemovel, 15, stdin);
    if (VerificaRegistro(lista_Clientes,C)){
        return 1;
    }
    return 0;
}
void Cliente(CLIENTE *C2){
    printf("Introduza o nome do cliente desejado?\n");
    getchar();
    fgets(C2->nome,50,stdin);
    printf("Introduza o seu numero de telemovel do cliente desejado?\n");
    fgets(C2->telemovel,15,stdin);
}

void Introduzir_CLIENTE_na_fila(CLIENTE_header *lista_Clientes, CLIENTE *C){
    CLIENTE *node = (CLIENTE *)malloc(sizeof(CLIENTE));
    CLIENTE *prev = NULL;
    CLIENTE *cur = lista_Clientes->start;
    if(node != NULL){
        strcpy(node -> telemovel, C->telemovel);
        strcpy(node -> nome, C->nome);
        if(prev == NULL){
            node->prox = cur;
            lista_Clientes->start = node;
        }
        else{
            node->prox = cur;
            prev->prox = node;
        }
        lista_Clientes->num_of_clientes++;
    }
}

void PreReservas_Cliente(CLIENTE *C2, PRE_RESERVA_header *lista_PreReserva){
    PRE_RESERVA *node = lista_PreReserva->start1;
    int count_PreReservas = 0;
    printf("Reservas: \n");

    while(node != NULL){
        if (strcmp(C2->telemovel,node->telemovel) == 0 && strcmp(C2->nome,node->nome) == 0) {
            printf("%s %s %d/%d/%d %d:%d %d\n", node->nome, node->telemovel, node->ano, node->mes, node->dia,node->hora, node->minuto, node->tipo);
            count_PreReservas++;
        }
        node = node->proxi;

    }
    printf("Numero de pre-reservas : %d", count_PreReservas);
}

void Reservas_Cliente(CLIENTE *C2, RESERVA_header *lista_Reservas){
    RESERVA *node = lista_Reservas->start;
    int count_Reservas = 0;
    printf("Reservas: \n");

    while(node != NULL){
        if (strcmp(C2->telemovel,node->telemovel) == 0 && strcmp(C2->nome,node->nome) == 0) {
            printf("%s %s %d/%d/%d %d:%d %d\n", node->nome, node->telemovel, node->ano, node->mes, node->dia,node->hora, node->minuto, node->tipo);
            count_Reservas++;
        }
        node = node->prox;

    }
    printf("Numero de reservas : %d", count_Reservas);

}

void upload_Cliente_ficheiroParaFila(CLIENTE_header *lista_Clientes){
    CLIENTE *node = (CLIENTE *)malloc(sizeof(CLIENTE));
    FILE *file = fopen("Clientes.txt","r+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de reservas.\n");
        return;
    }

    CLIENTE *prev = NULL;
    while (fscanf(file,"%s %s", node -> nome, node -> telemovel) == 2){
        node->prox = NULL;
        if (prev == NULL) {
            lista_Clientes->start = node;
        } else {
            prev->prox = node;
        }
        prev = node;
        lista_Clientes->num_of_clientes++;
        node = (CLIENTE *)malloc(sizeof(CLIENTE));
    }
    free(node);
    fclose(file);
}

void upload_ClienteParaficheiro(CLIENTE_header *lista_Clientes){
    FILE* file = fopen("Clientes.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    CLIENTE *node = lista_Clientes->start;
    while (node != NULL && node->prox != NULL) {
        node = node->prox;
    }
    if (node != NULL) {
        fprintf(file, "%s %s\n", node->nome, node->telemovel);
    }
    fclose(file);
}

#endif
