#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "archivoClientes.h"
#include "cuentas.h"
#include "archivoCuenta.h"
#include "conio.h"
#define ARCHI_CLIENTES "clientes.dat"
#define ARCHI_CUENTAS "cuentas.dat"
#define ESC 27

stCuenta cargaCuenta(char ArchivoCuentas[], char ArchivoClientes[]){
    stCuenta cuenta;
    stCliente Cliente;
    int EstadodeCuenta = 0;
    char OpcionConfirmarDatos = ' ';

    do{
    do{
    Cliente = BusquedaClienteInteraccionUsuario(ArchivoClientes);
    if(Cliente.id == - 1){
        printf("\nPresione cualquier tecla para volver a cargar el número de cliente. Presione ESC para salir.");
        OpcionConfirmarDatos = getch();
    }
    }while(OpcionConfirmarDatos != ESC && Cliente.id == - 1);

    if(Cliente.id == - 2){
        printf("El archivo de clientes se encuentra vacío. Por favor, complete primero su alta de cliente");
    }

    if(Cliente.id > 0){

        cuenta.idCliente = Cliente.id;
        cuenta.nroCuenta = NroDeCuenta (ARCHI_CUENTAS)+1;
        cuenta.id = IdCuenta(ARCHI_CUENTAS) + 1;
        cuenta.EstadodeCuenta = EstadodeCuenta;

        int flagTipoDeCuenta;
        do{
        printf("\nQue tipo de cuenta quiere abrir? (1 para caja de ahorro en pesos, 2 para caja de ahorro en dolares, 3 para cuenta corriente en pesos): ");
        scanf("%d", &cuenta.tipoDeCuenta);
        flagTipoDeCuenta = 0;
        if(cuenta.tipoDeCuenta < 1 || cuenta.tipoDeCuenta > 3){
            printf("\nNúmero inválido. Por favor, seleccione una cuenta válida para continuar.");
            flagTipoDeCuenta = 1;
        }
        else{
            if(CantidadDatosArchivo(ArchivoCuentas, sizeof(stCuenta)) > 0){
                if (cuenta.tipoDeCuenta == BusquedaCuentaParametro(ArchivoCuentas, Cliente.nroCliente, cuenta.tipoDeCuenta).tipoDeCuenta){
                    printf("\nEl cliente Nº %d ya tiene una cuenta de este tipo. Presione cualquier tecla para crear otro tipo de cuenta, o ESC para salir.", Cliente.nroCliente);
                    OpcionConfirmarDatos = getch();
                    flagTipoDeCuenta = 1;
                }
            }
        }
        }while(flagTipoDeCuenta == 1 && OpcionConfirmarDatos != ESC);

        if (flagTipoDeCuenta != 1){
            printf("\n================DATOS INGRESADOS================\n");
            muestraCuentas(cuenta, Cliente);
            printf("\n¿Estos datos son correctos? Presione cualquier tecla para continuar, o ESC para volver a cargar los datos.");
            OpcionConfirmarDatos = getch();
        }
        else{
            cuenta.id = - 1;
        }
    }
    else{
        if(Cliente.id == - 1){
            cuenta.id = - 1;
        }
        else{
            cuenta.id = - 2;
        }
    }
    }while(OpcionConfirmarDatos == ESC && cuenta.id > 0);

    return cuenta;
}

void muestraCuentas(stCuenta cuenta, stCliente Cliente){
    if(cuenta.id != - 1){
        printf("\n=====================================================");
        printf("\nNombre y Apellido: %s %s", Cliente.nombre, Cliente.apellido);
        printf("\nDNI: %s", Cliente.dni);
        printf("\nNumero de Cliente: %d", Cliente.nroCliente);
        printf("\nNumero de cuenta: %d", cuenta.nroCuenta);
        if(cuenta.tipoDeCuenta == 1){
            printf("\nTipo de Cuenta: Caja de Ahorro en AR$");
        }
        if(cuenta.tipoDeCuenta == 2){
            printf("\nTipo de Cuenta: Caja de Ahorro en US$");
            }
        if(cuenta.tipoDeCuenta == 3){
            printf("\nTipo de Cuenta: Cuenta Corriente en AR$");
        }
        if(cuenta.EstadodeCuenta == 0){
            printf("\nEstado de la cuenta: Activa");
        }
        else{
            printf("\nEstado de la cuenta: Inactiva");
        }
        printf("\n=====================================================");
    }
    else{
        printf("\nLa cuenta buscada no se encuentra en la base de datos.");
    }
}

int IdCuenta(char nombrearchivo[])
{
    stCuenta cuenta;
    FILE * archivoCuenta = fopen(nombrearchivo, "rb");
    int ultimoId = 0;

    if(archivoCuenta){
        if(CantidadDatosArchivo(nombrearchivo, sizeof(stCuenta)) > 0){
            fseek(archivoCuenta, -1*sizeof(stCuenta), SEEK_END);
            fread(&cuenta, sizeof(stCuenta), 1, archivoCuenta);
            ultimoId = cuenta.id;
        }
        fclose(archivoCuenta);
    }
    return ultimoId;
}

int NroDeCuenta (char nombrearchivo[])
{
    stCuenta cuenta;
    FILE * archivoCuenta = fopen(nombrearchivo, "rb");
    int ultimaCuenta = 10000000;

    if(archivoCuenta){
        if(CantidadDatosArchivo(nombrearchivo, sizeof(stCuenta)) > 0){
            fseek(archivoCuenta, -1*sizeof(stCuenta), SEEK_END);
            fread(&cuenta, sizeof(stCuenta), 1, archivoCuenta);
            ultimaCuenta = cuenta.nroCuenta;
        }
        fclose(archivoCuenta);
    }
    return ultimaCuenta;
}
