
#ifndef UNTITLED4_LISTAS_H
#define UNTITLED4_LISTAS_H
#include <stdlib.h>

// funcoes da estrutura CLIENTES

typedef struct CLIENTE{
    char nome[50];
    char telemovel[15];
    struct CLIENTE *prox;
} CLIENTE;

typedef struct CLIENTE_header{
    int num_of_clientes;
    CLIENTE *start;
}CLIENTE_header;

void initC(CLIENTE_header *lista_CLIENTES){
    lista_CLIENTES->num_of_clientes = 0;
    lista_CLIENTES->start = NULL;
}

//funcoes da estrutura RESERVA

typedef struct RESERVA{
    char nome[50];
    char telemovel[15];
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int tipo; // 0 - lavagem, 1 - manutenção
    struct RESERVA *prox;
} RESERVA;

typedef struct RESERVA_header{
    int num_of_RESERVAS;
    RESERVA *start;
}RESERVA_header;

void initR(RESERVA_header *lista_RESERVAS){
    lista_RESERVAS->num_of_RESERVAS = 0;
    lista_RESERVAS->start = NULL;
}

//funcoes estrutura PRE_RESERVA

typedef struct PRE_RESERVA{
    char nome[50];
    char telemovel[15];
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int tipo; // 0 - lavagem, 1 - manutenção
    struct PRE_RESERVA *proxi;
}PRE_RESERVA;

typedef struct PRE_RESERVA_header{
    int num_of_PRE_RESERVAS;
    PRE_RESERVA *start1;
}PRE_RESERVA_header;

void initPR(PRE_RESERVA_header *lista_PreReserva){
    lista_PreReserva -> num_of_PRE_RESERVAS = 0;
    lista_PreReserva -> start1 = NULL;
}


#endif 
