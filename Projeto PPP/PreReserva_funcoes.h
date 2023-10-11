
#ifndef UNTITLED4_PRERESERVA_FUNCOES_H
#define UNTITLED4_PRERESERVA_FUNCOES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"

#define tempo_lavagem 30
#define tempo_manutencao 60

void Fazer_Pre_Reserva(PRE_RESERVA *PR){
    printf("Que tipo de servico pretende pre reservar? (0-lavagem/1-Manutencao)\n");
    scanf("%d",&(PR->tipo));
    printf("Para que data quer a pre reserva (ano mes dia)?\n");
    scanf("%d %d %d",&(PR->ano),&(PR->mes),&(PR->dia));
    printf("Para que hora quer a pre reserva (Hora Minutos)?\n");
    scanf("%d %d",&(PR->hora),&(PR->minuto));
}

void PreReservaParaCancelar(PRE_RESERVA *PR){
    printf("Qual o tipo da pre-reserva a cancelar? (0-lavagem/1-Manutencao)\n");
    scanf("%d",&(PR->tipo));
    printf("Qual a data da pre-reserva a cancelar (ano mes dia)?\n");
    scanf("%d %d %d",&(PR->ano),&(PR->mes),&(PR->dia));
    printf("Qual a hora da pre-reserva a cancelar (Hora Minutos)?\n");
    scanf("%d %d",&(PR->hora),&(PR->minuto));
}

int procura_PreReserva(PRE_RESERVA_header *lista_PreReservas, PRE_RESERVA *PR, PRE_RESERVA **prev, PRE_RESERVA **cur){
    *prev = NULL;
    *cur = lista_PreReservas->start1;
    int verifica = 1;
    while((*cur) != NULL && ((*cur)->ano <= PR->ano ||((*cur)->ano == PR->ano && (*cur)->mes <= PR->mes) ||((*cur)->ano == PR->ano && (*cur)->mes == PR->mes && (*cur)->dia <= PR->dia))){
        *prev = *cur;
        *cur = (*cur)->proxi;
    }
    return verifica;
}

void Introduzir_pre_reserva_na_fila_de_espera(PRE_RESERVA_header *lista_PreReservas, PRE_RESERVA *R,CLIENTE *C){
    PRE_RESERVA *node = (PRE_RESERVA *)malloc(sizeof(PRE_RESERVA));
    PRE_RESERVA *previ = NULL;
    PRE_RESERVA *curi = lista_PreReservas->start1;
    if(node != NULL) {
        node->mes = R->mes;
        node->minuto = R->minuto;
        node->tipo = R->tipo;
        node->hora = R->hora;
        node->ano = R->ano;
        node->dia = R->dia;
        strcpy(node->telemovel, C->telemovel);
        strcpy(node->nome, C->nome);

        while (curi != NULL && (curi->ano < node->ano || (curi->ano == node->ano && (curi->mes < node->mes || (curi->mes == node->mes &&(curi->dia < node->dia ||(curi->dia == node->dia && (curi->hora < node->hora ||(curi->hora == node->hora && curi->minuto < node->minuto))))))))) {
            previ = curi;
            curi = curi->proxi;
        }

        if (previ == NULL) {
            node->proxi = curi;
            lista_PreReservas->start1 = node;
        } else {
            node->proxi = curi;
            previ->proxi = node;
        }
        lista_PreReservas->num_of_PRE_RESERVAS++;
    }
}

void cancelar_PreReserva(PRE_RESERVA_header *lista_PreReserva,PRE_RESERVA *PR){
    PRE_RESERVA *prev = NULL, *cur = lista_PreReserva->start1;
    procura_PreReserva(lista_PreReserva, PR, &prev, &cur);

    if(cur != NULL && cur -> ano == PR->ano && cur -> mes == PR->mes && cur -> dia == PR->dia && cur -> hora == PR->hora && cur -> minuto == PR->minuto){
        if(prev == NULL){
            lista_PreReserva->start1 = cur->proxi;
        }
        else{
            prev->proxi = cur->proxi;
        }

        free(cur);
        lista_PreReserva->num_of_PRE_RESERVAS--;
    }
}

void upload_PreReservas_ficheiroParaFila(PRE_RESERVA_header *lista_PreReservas){
    PRE_RESERVA *node = (PRE_RESERVA *)malloc(sizeof(PRE_RESERVA));
    FILE *file2 = fopen("PreReservas.txt","r+");
    if (file2 == NULL) {
        printf("Erro ao abrir o arquivo de pre-reservas.\n");
        return;
    }

    PRE_RESERVA *prev = NULL;
    while (fscanf(file2,"%s %s %d %d %d %d %d %d", node -> nome, node -> telemovel,&(node -> ano),&(node -> mes),&(node -> dia), &(node -> hora),&(node -> minuto),&(node -> tipo)) == 8){
        node->proxi = NULL;
        if (prev == NULL) {
            lista_PreReservas->start1 = node;
        } else {
            prev->proxi = node;
        }

        prev = node;
        lista_PreReservas->num_of_PRE_RESERVAS++;
    }
    free(node);
    fclose(file2);
}

void print_PreReservas(PRE_RESERVA_header *lista_PreReservas){
    PRE_RESERVA *node = lista_PreReservas->start1;

    printf("Numero de reservas: %d\n", lista_PreReservas->num_of_PRE_RESERVAS);
    printf("Reservas: \n");

    while(node != NULL){
        printf("%s %s %d/%d/%d %d:%d %d\n", node->nome,node->telemovel,node->ano,node->mes,node->dia,node->hora,node->minuto,node->tipo);
        node = node->proxi;
    }
}

void upload_PreReservaParaficheiro(PRE_RESERVA_header *lista_PreReservas){
    FILE* file2 = fopen("PreReservas.txt", "w");
    if (file2 == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    PRE_RESERVA* node = lista_PreReservas->start1;
    while (node != NULL && node->proxi != NULL) {
        node = node->proxi;
    }
    if (node != NULL) {
        fprintf(file2, "%s %s %d/%d/%d %d:%d %d\n", node->nome, node->telemovel, node->ano, node->mes, node->dia, node->hora, node->minuto, node->tipo);
    }
    fclose(file2);
}

int VerificaSeExistePreReservaCompativel(PRE_RESERVA_header *lista_PreReservas, RESERVA *R){
    PRE_RESERVA *node = lista_PreReservas->start1;
    char NomePreReserva[50];
    char TelefonePreReserva[15];
    while(node != NULL){
        if (node->ano == R->ano && node->mes == R->mes && node->dia == R->dia && node->hora == R->hora && node->minuto == R->minuto){
            strcpy(NomePreReserva,node->nome);
            strcpy(TelefonePreReserva,node->telemovel);
            return 1;
        }
        node = node->proxi;
    }
    return 0;
}

#endif
