#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "conio.h"
#define ARCHI_CLIENTES "clientes.dat"
#define ESC 27

stCliente cargaCliente(){
    srand(time(NULL));
    stCliente cliente;

    char opcionConfirmarDatos = ' ';
    do{
    int flagDNI;
    char opcionDNI = ' ';
    do{
        printf("\nIngrese su DNI: ");
        fflush(stdin);
        gets(cliente.dni);
        flagDNI = validarDni(cliente.dni, ARCHI_CLIENTES);
        if(flagDNI == 1){
            printf("\nEl DNI ingresado ya se encuentra registrado en la base de datos. Presione cualquier tecla para volver a ingresar un DNI, o presione ESC para salir.");
            opcionDNI = getch();
        }
    }while(opcionDNI != ESC && flagDNI == 1);

    if(flagDNI == 0){

    printf("\nIngrese su Nombre: ");
    fflush(stdin);
    gets(cliente.nombre);

    printf("\nIngrese su Apellido: ");
    fflush(stdin);
    gets(cliente.apellido);

    int flagEmail;
    do{
        printf("\nIngrese su Email: ");
        fflush(stdin);
        gets(cliente.email);
        flagEmail = validarEmail(cliente.email, ARCHI_CLIENTES);
        if(flagEmail == 1){
            printf("\nEl email ingresado ya se encuentra registrado en la base de datos. Por favor, vuelva a ingresar una dirección de email.");
        }
    }while(flagEmail == 1);

    printf("\nIngrese su Domicilio: ");
    fflush(stdin);
    gets(cliente.domicilio);

    int flagTelefono;
    do{
    printf("\nIngrese su Numero de telefono (sin espacios ni guiones): ");
    fflush(stdin);
    gets(cliente.telefono);
    flagTelefono = validarTelefono(cliente.telefono, ARCHI_CLIENTES);
    if(flagTelefono == 1){
        printf("\nEl teléfono ingresado ya se encuentra registrado en la base de datos. Por favor, vuelva a ingresar un teléfono.");
    }
    }while(flagTelefono == 1);

    cliente.nroCliente = rand()% 100000;

    cliente.id = Id(ARCHI_CLIENTES)+1;

    cliente.EstadoDeCliente = 0;

    printf("\n================DATOS INGRESADOS================\n");
    muestraClientes(cliente);
    printf("\n¿Estos datos son correctos? Presione cualquier tecla para continuar, o ESC para volver a cargar los datos.");
    opcionConfirmarDatos = getch();
    }
    else{
        cliente.id = - 1;
    }
    }while(cliente.id != - 1 && opcionConfirmarDatos == ESC);
    return cliente;
}

void muestraClientes(stCliente cliente){
    if(cliente.id != -1){
        printf("\n=====================================================");
        printf("\nNombre: %s", cliente.nombre);
        printf("\nApellido: %s", cliente.apellido);
        printf("\nDNI: %s", cliente.dni);
        printf("\nEmail: %s", cliente.email);
        printf("\nDomicilio: %s", cliente.domicilio);
        printf("\nTelefono: %s", cliente.telefono);
        printf("\nNumero de Cliente: %d", cliente.nroCliente);
        if(cliente.EstadoDeCliente == 0){
            printf("\nEstado del cliente: Activo");
        }
        else{
            printf("\nEstado del cliente: Inactivo");
        }
        /*printf("\nID de Cliente: %d", cliente.id);*/
        printf("\n=====================================================");
    }
    else{
        printf("\nEl cliente buscado no se encuentra en la base de datos.");
    }
}

int Id(char nombrearchivo[])
{
    stCliente cliente;
    FILE * archivoClientes = fopen(nombrearchivo, "rb");
    int ultimoId = 0;

    if(archivoClientes)
    {
        if(CantidadDatosArchivo(nombrearchivo, sizeof(stCliente)) > 0){
            fseek(archivoClientes, -1*sizeof(stCliente), SEEK_END);
            fread(&cliente, sizeof(stCliente), 1, archivoClientes);
            ultimoId = cliente.id;
        }
        fclose(archivoClientes);
    }
    return ultimoId;
}

int validarDni(char DNICliente[], char NombreArchivo[]){
    stCliente ClientesCargados;
    int flag = 0;
    FILE * ArchivoClientes = fopen(NombreArchivo, "rb");
    if(ArchivoClientes)
    {
        if (CantidadDatosArchivo(NombreArchivo, sizeof(stCliente)) > 0){
            while(flag == 0 && fread(&ClientesCargados, sizeof(stCliente), 1, ArchivoClientes) > 0)
            {
                if(strcmp(DNICliente, ClientesCargados.dni) == 0)
                {
                    flag = 1;
                }
            }
        }
    }
    fclose(ArchivoClientes);
    return flag;
}

int validarEmail(char EmailCliente[], char NombreArchivo[]){
    stCliente ClientesCargados;
    int flag = 0;
    FILE * ArchivoClientes = fopen(NombreArchivo, "rb");
    if(ArchivoClientes){
        if (CantidadDatosArchivo(NombreArchivo, sizeof(stCliente)) > 0){
            while(flag == 0 && fread(&ClientesCargados, sizeof(stCliente), 1, ArchivoClientes) > 0){
                if(strcmp(EmailCliente, ClientesCargados.email) == 0){
                    flag = 1;
                }
            }
        }
    }
    fclose(ArchivoClientes);
    return flag;
}

int validarTelefono(char TelefonoCliente[], char NombreArchivo[]){
    stCliente ClientesCargados;
    int flag = 0;
    FILE * ArchivoClientes = fopen(NombreArchivo, "rb");

    if(ArchivoClientes){
        if (CantidadDatosArchivo(NombreArchivo, sizeof(stCliente)) > 0){
            while(flag == 0 && fread(&ClientesCargados, sizeof(stCliente), 1, ArchivoClientes) > 0)
            {
                if(strcmp(TelefonoCliente, ClientesCargados.telefono) == 0)
                {
                    flag = 1;
                }
            }
        }
    }
    fclose(ArchivoClientes);
    return flag;
}

