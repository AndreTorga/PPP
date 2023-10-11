#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.h"
#include "Reserva_funcoes.h"
#include "PreReserva_funcoes.h"
#include "Cliente.h"

#define tempo_lavagem 30
#define tempo_manutencao 60
void EntrarSite(CLIENTE_header *lista_Clientes, CLIENTE *C){
    int opcao2;
    int vali;
    do{
        printf("1. Fazer Login\n");
        printf("2. Registrar\n");
        printf("Escolha uma opcao: \n");
        scanf("%d",&opcao2);
        switch (opcao2) {
            case 1:
                printf("-------------------Login---------------------\n");
                vali = LogIn(lista_Clientes,C);
                break;
            case 2:
                printf("-------------------Registre-se---------------------\n");
                if (Registrar(lista_Clientes,C)){
                    upload_ClienteParaficheiro(lista_Clientes);
                    Introduzir_CLIENTE_na_fila(lista_Clientes,C);
                    printf("Agora que já se registou, pode fazer login!!!!\n\n");
                    printf("-------------------Login---------------------\n");
                    vali = LogIn(lista_Clientes,C);
                    break;
                }
                break;
            default:
                printf("Opcao invalida...\n");
                break;
        }

    } while(vali == 0);
}
void menu(CLIENTE C2, CLIENTE C,RESERVA R,PRE_RESERVA PR, RESERVA_header *lista_Reservas,PRE_RESERVA_header *lista_PreReservas) {
    int opcao;
    char NomePreReserva;
    char TelefonePreReserva;
    do {
        printf("\nMenu:\n");
        printf("1. Fazer reserva\n");
        printf("2. Fazer pre-reserva\n");
        printf("3. Cancelar reserva\n");
        printf("4. Cancelar pre-reserva\n");
        printf("5. Listar reservas\n");
        printf("6. Listar pre-reservas\n");
        printf("7. Listar reservas de um cliente\n");
        printf("8. Listar pre-reservas de um cliente\n");
        printf("9. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                Fazer_Reserva(&R);
                Introduzir_reserva_na_fila(lista_Reservas, &R, &C);
                upload_ReservaParaficheiro(lista_Reservas);
                break;
            case 2:
                Fazer_Pre_Reserva(&PR);
                Introduzir_pre_reserva_na_fila_de_espera(lista_PreReservas, &PR, &C);
                upload_PreReservaParaficheiro(lista_PreReservas);
                break;
            case 3:
                ReservaParaCancelar(&R);
                cancelar_Reserva(lista_Reservas,&R,lista_PreReservas, &NomePreReserva, &TelefonePreReserva); // dentro desta funcao tambem verifico se existe alguma pre reserva disponivel para a data e horario da reserva a cancelar
                break;
            case 4:
                PreReservaParaCancelar(&PR);
                cancelar_PreReserva(lista_PreReservas,&PR);
                break;
            case 5:
                printf("\nListar Reservas\n");
                print_Reservas(lista_Reservas);
                break;
            case 6:
                printf("\nListar Pré-Reservas\n");
                print_PreReservas(lista_PreReservas);
                break;
            case 7:
                printf("\nListar Reservas de um cliente\n");
                Cliente(&C2);
                Reservas_Cliente(&C2,lista_Reservas);
                break;
            case 8:
                printf("\nListar Pre-Reservas de um cliente\n");
                Cliente(&C2);
                PreReservas_Cliente(&C2,lista_PreReservas);
                break;
            case 9:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 9);
}
int main(void) {
    RESERVA_header *lista_RESERVA = (RESERVA_header *)malloc(sizeof(RESERVA_header));
    PRE_RESERVA_header *lista_PreReserva = (PRE_RESERVA_header *)malloc(sizeof(PRE_RESERVA_header));
    CLIENTE_header *lista_CLIENTES = (CLIENTE_header *)malloc(sizeof(CLIENTE_header));

    RESERVA R;
    PRE_RESERVA PR;
    CLIENTE C;
    CLIENTE C2;

    initR(lista_RESERVA);
    initPR(lista_PreReserva);
    initC(lista_CLIENTES);

    upload_Cliente_ficheiroParaFila(lista_CLIENTES);
    upload_Reservas_ficheiroParaFila(lista_RESERVA);
    upload_PreReservas_ficheiroParaFila(lista_PreReserva);

    EntrarSite(lista_CLIENTES, &C);
    menu(C2,C,R,PR, lista_RESERVA,lista_PreReserva);

    free(lista_RESERVA);
    free(lista_PreReserva);
    free(lista_CLIENTES);
}
