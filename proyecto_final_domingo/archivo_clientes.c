#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "archivo_clientes.h"
#include "conio.h"
#define ARCHI_CLIENTES "clientes.dat"

#define ESC 27

void cargaArchivoCliente(char nombreArchivo[])
{
    char opcion = 0;
    stCliente cliente;
    int flagDni = 0;

    FILE* archiClientes = fopen(nombreArchivo, "ab");
    if(archiClientes)
    {
        cliente = cargaCliente();
        fwrite(&cliente, sizeof(stCliente), 1, archiClientes);
        fclose(archiClientes);
    }
    printf("\nESC para salir o cualquier tecla para continuar");
    opcion=getch();

    if(opcion != 27)
    {
        FILE* archiClientes = fopen(nombreArchivo, "ab");
        if(archiClientes)
        {
            while(opcion!=27)
            {
                cliente = cargaCliente();
                fwrite(&cliente, sizeof(stCliente), 1, archiClientes);
                printf("\nESC para salir o cualquier tecla para continuar");
                opcion=getch();
            }

            fclose(archiClientes);
        }
    }
}

void muestraArchivoDeClientes(char nombreArchivo[])
{
    stCliente cliente;
    FILE* archiClientes = fopen(nombreArchivo, "rb");
    if(archiClientes)
    {
        while(fread(&cliente, sizeof(stCliente), 1, archiClientes)>0)
        {
            muestraClientes(cliente);
        }
        fclose(archiClientes);
    }
}


int Id(char nombrearchivo[])
{
    stCliente cliente;
    FILE * archivoClientes = fopen(nombrearchivo, "rb");
    int ultimoId = 0;

    if(archivoClientes)
    {
        fseek(archivoClientes, 0, SEEK_END);
        if(ftell(archivoClientes)/sizeof(stCliente) == 0)
        {
            ultimoId = 0;
        }
        else
        {
            fseek(archivoClientes, -1*sizeof(stCliente), SEEK_END);
            fread(&cliente, sizeof(stCliente), 1, archivoClientes);
            ultimoId = cliente.id;
        }
        fclose(archivoClientes);
    }
    return ultimoId;
}

int validarDni(stCliente cliente, char nombrearchivo[])
{
    stCliente cargado;
    int flag = 0;
    FILE * archivoClientes = fopen(nombrearchivo, "rb");
    if(archivoClientes)
    {
        while(flag == 0 && fread(&cargado, sizeof(stCliente), 1, archivoClientes))
        {
            if(strcmp(cliente.dni, cargado.dni)==0)
            {
                flag = 1;
            }
        }
    }
    fclose(archivoClientes);
    return flag;
}
