#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "archivoClientes.h"
#include "eventuales.h"
#include "string.h"
#include "conio.h"
#define ARCHI_CLIENTES "clientes.dat"
#define ESC 27

void cargaArchivoCliente(char nombreArchivo[])
{
    char opcion = ' ';
    stCliente cliente;

    while(opcion != ESC){
    FILE* archiClientes = fopen(nombreArchivo, "ab");
        if(archiClientes)
        {
            cliente = cargaCliente();

            if(cliente.id != - 1){
                fwrite(&cliente, sizeof(stCliente), 1, archiClientes);
                printf("\nCliente registrado exitosamente.");
            }
            fclose(archiClientes);
            printf("\nPresione cualquier tecla para continuar agregando clientes. Presione ESC para salir.");
            opcion = getch();
        }
    }


}

void muestraArchivoDeClientes(char nombreArchivo[]){
    stCliente cliente;
    FILE* archiClientes = fopen(nombreArchivo, "rb");
    if(archiClientes)
    {
        while(fread(&cliente, sizeof(stCliente), 1, archiClientes) > 0)
        {
            muestraClientes(cliente);
        }
        if (CantidadDatosArchivo(nombreArchivo, sizeof(stCliente)) == 0){
            printf("El archivo se encuentra vacío.");
        }
        fclose(archiClientes);
    }
}


stCliente BusquedaClienteInteraccionUsuario(char nombreArchivo[]){ ///Para interacción con el usuario
    stCliente cliente;
    int nroCliente;
    int flag = 0;
    char opcion = ' ';
    FILE * archivoClientes = fopen(nombreArchivo, "rb");

    if(archivoClientes){
        if(CantidadDatosArchivo(nombreArchivo, sizeof(stCliente)) > 0){

            do{
                printf("\nIngrese su numero de cliente: ");
                scanf("%d", &nroCliente);
                fseek(archivoClientes, 0, SEEK_SET);
                while(flag == 0 && fread(&cliente, sizeof(stCliente), 1, archivoClientes) > 0){
                    if(nroCliente == cliente.nroCliente){
                        flag = 1;
                    }
                }
                if (flag == 0){
                    printf("\nEl número de cliente ingresado no corresponde a ningún cliente en nuestra base de datos. Presione cualquier tecla para ingresar otro valor, o ESC para salir.");
                    opcion = getch();
                    cliente.id = - 1;
                }
            }while(opcion != ESC && flag == 0);
        }
        else{
            cliente.id = - 1;
            printf("\nEl archivo se encuentra vacío.");
        }
        fclose(archivoClientes);
    }
    else{
        cliente.id = - 2;
    }
    return cliente;
}

stCliente BusquedaClienteParametro(char nombreArchivo[], int NumeroDeCliente){///Para búsquedas internas
    stCliente cliente;
    int flag = 0;
    FILE * archivoClientes = fopen(nombreArchivo, "rb");

    if(archivoClientes){
        if(CantidadDatosArchivo(nombreArchivo, sizeof(stCliente)) > 0){
            fseek(archivoClientes, 0, SEEK_SET);
            while(flag == 0 && fread(&cliente, sizeof(stCliente), 1, archivoClientes) > 0){
                if(NumeroDeCliente == cliente.nroCliente){
                    flag = 1;
                }
            }
        }
        else{
            printf("\nEl archivo se encuentra vacío.");
            cliente.id = - 1;
        }
            fclose(archivoClientes);
    }
    return cliente;
}

stCliente BusquedaClientePorID(char nombreArchivo[], int IDCliente){///Para búsquedas internas
    stCliente cliente;
    int flag = 0;
    FILE * archivoClientes = fopen(nombreArchivo, "rb");

    if(archivoClientes){
        if(CantidadDatosArchivo(nombreArchivo, sizeof(stCliente)) > 0){
            fseek(archivoClientes, 0, SEEK_SET);
            while(flag == 0 && fread(&cliente, sizeof(stCliente), 1, archivoClientes) > 0){
                if(IDCliente == cliente.id){
                    flag = 1;
                }
            }
        }
        else{
            printf("\nEl archivo se encuentra vacío.");
            cliente.id = - 1;
        }
            fclose(archivoClientes);
    }
    return cliente;
}

void DesactivarCliente(char ArchivoCliente[], char ArchivoCuenta[]){
    stCliente Cliente;
    int NumeroClienteAEliminar;
    int flag = 0;
    char Opcion = ' ';
    FILE *archivo = fopen(ArchivoCliente, "r + b");
    if(archivo){
        if(CantidadDatosArchivo(ArchivoCliente, sizeof(stCliente)) > 0){
            do{
                printf("\nIngrese el numero de cliente a eliminar: ");
                scanf("%d", &NumeroClienteAEliminar);
                while(flag == 0 && fread(&Cliente, sizeof(stCliente), 1, archivo) > 0){
                    if(NumeroClienteAEliminar == Cliente.nroCliente){
                        flag = 1;
                    }
                }
                if (flag == 1){
                Cliente = BusquedaClienteParametro(ArchivoCliente, NumeroClienteAEliminar);
                Cliente.EstadoDeCliente = - 1;
                fseek(archivo, -1*sizeof(stCliente), SEEK_CUR);
                fwrite(&Cliente, sizeof(stCliente), 1, archivo);
                DesactivarCuentaAutomatico(ArchivoCuenta, NumeroClienteAEliminar);
                Opcion = ESC;
                }
                else{
                    printf("\nEl cliente buscado no se encuentra en la base de datos. Presiona cualquier tecla para volver a ingresar el número de cliente. Presiona ESC para salir.");
                    Opcion = getch();
                }
            }while(Opcion != ESC);
        }
        else{
            printf("\nEl archivo se encuentra vacío.");
        }
    }
    else{
        printf("El archivo no puede abrirse.");
    }
}

/*void ModificarCliente (char ArchivoClientes){
    stCliente Cliente;
    int flag = 0;
    int NumeroClienteAModificar;
    FILE *archi = fopen(ArchivoClientes, "r + b");

    if(archivo){
        if(CantidadDatosArchivo(ArchivoClientes, sizeof(stCliente)) > 0){
            do{
                printf("\nIngrese el numero del cliente a modificar: ");
                scanf("%d", &NumeroClienteAModificar);
                while(flag == 0 && fread(&Cliente, sizeof(stCliente), 1, archi) > 0){
                if(NumeroClienteAModificar == Cliente.nroCliente){
                    flag = 1;
                }
                }
                if (flag == 1){
                Cliente = BusquedaClienteParametro(ArchivoCliente, NumeroClienteAModificar);

                do{
                printf("\nQue dato desea modificar?");
                fseek(archi, -1*sizeof(stCliente), SEEK_CUR);
                fwrite(&Cliente, sizeof(stCliente), 1, archi);
                }while();///INCOMPLETO
                Opcion = ESC;

                }
                else{
                    printf("\nEl cliente buscado no se encuentra en la base de datos. Presiona cualquier tecla para volver a ingresar el número de cliente. Presiona ESC para salir.");
                    Opcion = getch();
                }
            }while(Opcion != ESC);


        }
        else{
            printf("\nEl archivo se encuentra vacío.");
        }



        fclose(archi);
    }
    else{
        printf("\nEl archivo no puede abrirse.");
    }
}
*/
