
#ifndef UNTITLED4_RESERVA_FUNCOES_H
#define UNTITLED4_RESERVA_FUNCOES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"
#include "PreReserva_funcoes.h"
#define tempo_lavagem 30
#define tempo_manutencao 60

void Fazer_Reserva(RESERVA *R){
    printf("Que tipo de servico pretende reservar? (0-lavagem/1-Manutencao)\n");
    scanf("%d",&(R->tipo));
    printf("Para que data quer a reserva (ano mes dia)?\n");
    scanf("%d %d %d",&(R->ano),&(R->mes),&(R->dia));
    printf("Para que hora quer a reserva (Hora Minutos)?\n");
    scanf("%d %d",&(R->hora),&(R->minuto));
}

void ReservaParaCancelar(RESERVA *R){
    printf("Qual o tipo da reserva a cancelar? (0-lavagem/1-Manutencao)\n");
    scanf("%d",&(R->tipo));
    printf("Qual a data da reserva a cancelar (ano mes dia)?\n");
    scanf("%d %d %d",&(R->ano),&(R->mes),&(R->dia));
    printf("Qual a hora da reserva a cancelar (Hora Minutos)?\n");
    scanf("%d %d",&(R->hora),&(R->minuto));
}

int procura_RESERVA(RESERVA_header *lista_RESERVAS, RESERVA *R, RESERVA **prev, RESERVA **cur){
    *prev = NULL;
    *cur = lista_RESERVAS->start;
    int verifica = 0;
    while((*cur) != NULL && ((*cur)->ano <= R->ano ||((*cur)->ano == R->ano && (*cur)->mes <= R->mes) ||((*cur)->ano == R->ano && (*cur)->mes == R->mes && (*cur)->dia <= R->dia)) && verifica == 0){
        if ((((*cur)-> ano == R->ano) || (*cur)-> mes == R->mes || (*cur)-> dia == R->dia)) {
            int hora_reserva_Acomparar = ((((*cur)->hora) * 60) + ((*cur)->minuto));
            int hora_reserva_nova = ((R->hora) * 60 + R->minuto);
            if (R->tipo == 0) {
                if (hora_reserva_Acomparar - tempo_lavagem >= hora_reserva_nova) {
                    verifica = 1;
                }
            } else {
                if (hora_reserva_Acomparar - tempo_manutencao >= hora_reserva_nova) {
                    verifica = 1;
                }
            }
        }
        if ((*cur) == NULL){
            printf("Hora nao disponivel. Tente fazer uma nova reserva para outra hora ou faça uma pre reserva.");
            return 0;
        }
        *prev = *cur;
        *cur = (*cur)->prox;
    }
    return 1;
}

void Introduzir_reserva_na_fila(RESERVA_header *lista_Reservas, RESERVA *R, CLIENTE *C){
    RESERVA *node = (RESERVA *)malloc(sizeof(RESERVA));
    RESERVA *prev, *cur;
    if(node != NULL) {
        node->mes = R->mes;
        node->minuto = R->minuto;
        node->tipo = R->tipo;
        node->hora = R->hora;
        node->ano = R->ano;
        node->dia = R->dia;
        strcpy(node->telemovel, C->telemovel);
        strcpy(node->nome, C->nome);
        if (procura_RESERVA(lista_Reservas, R, &prev, &cur)) {
            if (prev == NULL) {
                node->prox = cur;
                lista_Reservas->start = node;
            } else {
                node->prox = cur;
                prev->prox = node;
            }
            lista_Reservas->num_of_RESERVAS++;
        }
    }
}

void cancelar_Reserva(RESERVA_header *lista_Reserva,RESERVA *R,PRE_RESERVA_header *lista_PreReservas, const char *NomePreReserva,const char *TelefonePreReserva){
    RESERVA *prev, *cur;
    procura_RESERVA(lista_Reserva,R, &prev, &cur);

    if(cur != NULL && cur -> ano == R->ano && cur -> mes == R->mes && cur -> dia == R->dia && cur -> hora == R->hora && cur -> minuto == R->minuto){
        if(prev == NULL){
            lista_Reserva->start = cur->prox;
        }
        else{
            prev->prox = cur->prox;
        }
        if (VerificaSeExistePreReservaCompativel(lista_PreReservas, R)){
            strcpy(cur -> nome ,NomePreReserva);
            strcpy(cur -> telemovel,TelefonePreReserva);
        }
        else{
            free(cur);
        }
        lista_Reserva->num_of_RESERVAS--;
    }
}

void upload_Reservas_ficheiroParaFila(RESERVA_header *lista_RESERVAS){
    RESERVA *node = (RESERVA *)malloc(sizeof(RESERVA));
    FILE *file = fopen("Reservas.txt","r+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de reservas.\n");
        return;
    }

    RESERVA *prev = NULL;
    while (fscanf(file,"%s %s %d %d %d %d %d %d", node -> nome, node -> telemovel,&node -> ano,&node -> mes,&node -> dia, &node -> hora,&node -> minuto,&node -> tipo) == 8){
        node->prox = NULL;
        if (prev == NULL) {
            lista_RESERVAS->start = node;
        } else {
            prev->prox = node;
        }
        prev = node;
        lista_RESERVAS->num_of_RESERVAS++;
        node = (RESERVA *)malloc(sizeof(RESERVA));
    }
    free(node);
    fclose(file);
}

void print_Reservas(RESERVA_header *lista_RESERVAS){
    RESERVA *node = lista_RESERVAS->start;

    printf("Numero de reservas: %d\n", lista_RESERVAS->num_of_RESERVAS);
    printf("Reservas: \n");

    while(node != NULL ){
        printf("%s %s %d/%d/%d %d:%d %d\n", node->nome,node->telemovel,node->ano,node->mes,node->dia,node->hora,node->minuto,node->tipo);
        node = node->prox;
    }
}

void upload_ReservaParaficheiro(RESERVA_header *lista_RESERVAS){
    FILE* file = fopen("Reservas.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    RESERVA* node = lista_RESERVAS->start;
    while (node != NULL && node->prox != NULL) {
        node = node->prox;
    }
    if (node != NULL) {
        fprintf(file, "%s %s %d/%d/%d %d:%d %d\n", node->nome, node->telemovel, node->ano, node->mes, node->dia, node->hora, node->minuto, node->tipo);
    }
    fclose(file);
}

#endif
