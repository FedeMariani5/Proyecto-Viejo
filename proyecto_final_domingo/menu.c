#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "gotoxy.h"
#include "conio.h"

#define ARCHI_CLIENTES "clientes.dat"
#define ARCHI_CUENTAS "cuentas.dat"
#define ARCHI_MOVIMIENTOS "movimientos.dat"

void getNow(char date[])
{

    time_t tiempo = time(0);
    struct tm * tlocal = localtime(&tiempo);
    strftime(date, 128, "%d/%m/%y", tlocal);
}

void dibujarMenu()
{

    system("cls");
    system("color 9F");
    int x=20, y=3, i;
    char date[100];

    gotoxy(19, 3);
    printf("%c", 201);

    for(i=0; i<40; i++)
    {
        gotoxy(x,y);
        printf("%c", 205);
        x++;
    }

    x=19;
    y=4;

    for(i=0; i<25; i++)
    {
        gotoxy(x,y);
        printf("%c", 186);
        y++;
    }

    gotoxy(60, 3);
    printf("%c", 187);

    x=60;
    y=4;
    for(i=0; i<25; i++)
    {
        gotoxy(x,y);
        printf("%c", 186);
        y++;
    }
    x=20;
    y=29;
    for(i=0; i<40; i++)
    {
        gotoxy(x,y);
        printf("%c", 205);
        x++;
    }

    gotoxy(60, 29);
    printf("%c", 188);

    gotoxy(19, 29);
    printf("%c", 200);

    gotoxy(4,4);
    getNow(date);
    printf("%s", date);

    gotoxy(63, 4);
    printf("Alumnos:");
    gotoxy(63, 5);
    printf("- Rodriguez Mariani, Federico.");
    gotoxy(63, 6);
    printf("- Patuto, Federico.");
    gotoxy(63, 7);
    printf("- Molina, Lucas.");

    gotoxy(29, 1);
    printf("Trabajo Practico Final");
    gotoxy(29, 2);
    printf("----------------------");

}

void casos()
{
    gotoxy(23, 8);
    printf("1. Clientes.");

    gotoxy(23, 9);
    printf("2. Cuentas.");

    gotoxy(23, 10);
    printf("3. Movimientos.");

    gotoxy(23, 20);
    printf("ESC. Salir.");

    gotoxy(23, 29);
    printf("");
}

void casoClientes()
{
    char opcion = 0;

    do
    {
        system("cls");
        dibujarMenu();
        gotoxy(23, 8);
        printf("1. Cargar un cliente.");

        gotoxy(23, 9);
        printf("2. Eliminar un cliente.");

        gotoxy(23, 10);
        printf("3. Modificar un cliente.");

        gotoxy(23, 11);
        printf("4. Listado de clientes.");

        gotoxy(23, 20);
        printf("ESC. Salir.");

        opcion = getch();
        switch(opcion)
        {
        case 49:
            system("cls");
            cargaArchivoCliente(ARCHI_CLIENTES);
            break;

        case 50:
            system("cls");
            dibujarMenu();
            gotoxy(23, 8);
            printf("b");
            gotoxy(23, 20);
            printf("ESC. Salir.");
            break;

        case 51:
            system("cls");
            dibujarMenu();
            gotoxy(23, 8);
            printf("c");
            gotoxy(23, 20);
            printf("ESC. Salir.");
            break;

        case 52:
            system("cls");
            muestraArchivoDeClientes(ARCHI_CLIENTES);
            printf("\nESC. Salir.");
        }
        getch();
    }
    while(opcion != 27);
}

void casoCuentas()
{
    char opcion = 0;

    do
    {
        system("cls");
        dibujarMenu();
        gotoxy(23, 8);
        printf("1. Cargar una cuenta.");

        gotoxy(23, 9);
        printf("2. Eliminar una cuenta.");

        gotoxy(23, 10);
        printf("3. Modificar una cuenta.");

        gotoxy(23, 11);
        printf("4. Listado de cuentas.");

        gotoxy(23, 20);
        printf("ESC. Salir.");

        opcion = getch();
        switch(opcion)
        {
        case 49:
            system("cls");
            cargaArchivoCuenta(ARCHI_CUENTAS, ARCHI_CLIENTES);
            break;

        case 50:
            system("cls");
            dibujarMenu();
            gotoxy(23, 8);
            printf("b");
            gotoxy(23, 20);
            printf("ESC. Salir.");
            break;

        case 51:
            system("cls");
            dibujarMenu();
            gotoxy(23, 8);
            printf("c");
            gotoxy(23, 20);
            printf("ESC. Salir.");
            break;

        case 52:
            system("cls");
            MuestraArchivoDeCuentas(ARCHI_CUENTAS, ARCHI_CLIENTES);
            printf("\nESC. Salir.");
        }
        getch();
    }
    while(opcion != 27);
}

void casoMovimientos()
{
    char opcion = 0;

    do
    {
        system("cls");
        dibujarMenu();
        gotoxy(23, 8);
        printf("1. Cargar un movimiento.");

        gotoxy(23, 9);
        printf("2. Carga random de 1000 movimientos.");

        gotoxy(23, 10);
        printf("3. Eliminar un movimiento.");

        gotoxy(23, 11);
        printf("4. Modificar una movimiento.");

        gotoxy(23, 12);
        printf("5. Listado de movimientos.");

        gotoxy(23, 20);
        printf("ESC. Salir.");

        opcion = getch();
        switch(opcion)
        {
        case 49:
            system("cls");
            dibujarMenu();
            gotoxy(23, 8);
            printf("a");
            gotoxy(23, 20);
            printf("ESC. Salir.");
            break;

        case 50:
            system("cls");
            printf("\nCargando Movimientos...");
            CargaMasivaArchivoMovimientos(ARCHI_MOVIMIENTOS);
            system("cls");
            printf("1000 movimientos cargados correctamente");
            printf("\nESC. Salir.");
            break;

        case 51:
            system("cls");
            dibujarMenu();
            gotoxy(23, 8);
            printf("c");
            gotoxy(23, 20);
            printf("ESC. Salir.");
            break;

        case 52:
            system("cls");
            dibujarMenu();
            gotoxy(23, 8);
            printf("d");
            gotoxy(23, 20);
            printf("ESC. Salir.");
            break;

        case 53:
            system("cls");
            MuestraArchivoDeMovimientos(ARCHI_MOVIMIENTOS);
            printf("\nESC. Salir.");
        }
        getch();
    }
    while(opcion != 27);
}

void menu()
{
    char opcion = 0;

    do
    {
        dibujarMenu();
        casos();
        opcion = getch();
        switch(opcion)
        {
        case 49:
            casoClientes();
            break;

        case 50:
            casoCuentas();
            break;

        case 51:
            casoMovimientos();
        }

    }
    while(opcion != 27);
}




