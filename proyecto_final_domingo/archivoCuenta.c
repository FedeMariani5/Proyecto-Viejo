#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "archivoClientes.h"
#include "cuentas.h"
#include "archivoCuenta.h"
#include "conio.h"
#define ARCHI_CLIENTES "clientes.dat"
#define ESC 27


void cargaArchivoCuenta(char ArchivoCuenta[], char ArchivoClientes[]){
    char opcion = ' ';
    stCuenta Cuenta;

    while(opcion != ESC){
        FILE* ArchivoCuentas = fopen(ArchivoCuenta, "ab");
        if(ArchivoCuentas){
            Cuenta = cargaCuenta(ArchivoCuenta,ArchivoClientes);
            if(Cuenta.id != - 1){
                fwrite(&Cuenta, sizeof(stCuenta), 1, ArchivoCuentas);
            }
            if(Cuenta.id != - 2){
                printf("\nPresione cualquier tecla para continuar agregando cuentas. Presione ESC para salir.");
                opcion = getch();
            }
            else{
                opcion = ESC;
            }
            fclose(ArchivoCuentas);
        }
    }


}

void MuestraArchivoDeCuentas(char ArchivoCuenta[], char ArchivoCliente[]){
    stCuenta Cuenta;
    stCliente Cliente;
    FILE* ArchivoCuentas = fopen(ArchivoCuenta, "rb");
    if(ArchivoCuentas)
    {
            while(fread(&Cuenta, sizeof(stCuenta), 1, ArchivoCuentas) > 0){
            Cliente = BusquedaClientePorID(ArchivoCliente, Cuenta.idCliente);
            muestraCuentas(Cuenta, Cliente);
        }
        if (CantidadDatosArchivo(ArchivoCuenta, sizeof(stCuenta)) == 0){
            printf("El archivo se encuentra vacío.");
        }
        fclose(ArchivoCuentas);
    }
}

void BusquedaCuentaInteraccionUsuario(char archivocuenta[]){
    FILE *archivo = fopen(archivocuenta, "rb");
    char OpcionSalida = ' ';
    int TipoDeCuenta;
    if(archivo){
        if(CantidadDatosArchivo(archivocuenta, sizeof(stCuenta)) > 0){
        }
        else{
            printf("El archivo se encuentra vacío");
        }
    fclose(archivo);
    }
}

stCuenta BusquedaCuentaParametro (char archivocuenta[], int NumeroDeCliente, int TipodeCuenta){
    stCuenta Cuenta;
    int flag = 0;
    int idCliente = BusquedaClienteParametro(ARCHI_CLIENTES, NumeroDeCliente).id;
    FILE * archi = fopen(archivocuenta, "rb");

    if(archi){
        if(CantidadDatosArchivo(archivocuenta, sizeof(stCuenta)) > 0){
            fseek(archi, 0, SEEK_SET);
            while(flag == 0 && fread(&Cuenta, sizeof(stCuenta), 1, archi) > 0){
                if(idCliente == Cuenta.idCliente && Cuenta.tipoDeCuenta == TipodeCuenta){
                    flag = 1;
                }
            }
            if (flag == 0){
                Cuenta.id = - 1;
                Cuenta.tipoDeCuenta = - 1;
            }
        }
        else{
            printf("\nEl archivo se encuentra vacío.");
            Cuenta.id = - 1;
            Cuenta.tipoDeCuenta = - 1;
        }
            fclose(archi);
    }
    return Cuenta;
}


stCuenta BusquedaCuentaPorID (char archivocuenta[], int IDCuentaBuscada){
    stCuenta Cuenta;
    int flag = 0;
    FILE * ArchivoCuenta = fopen(archivocuenta, "rb");

    if(ArchivoCuenta){
        if(CantidadDatosArchivo(ArchivoCuenta, sizeof(stCuenta)) > 0){

            while(flag == 0 && fread(&Cuenta, sizeof(stCuenta), 1, archivocuenta) > 0){
                if(IDCuentaBuscada == Cuenta.id){
                    flag = 1;
                }
            }
            if (flag == 0){
                Cuenta.id = - 1;
            }
        else{
            printf("\nEl archivo se encuentra vacío.");
            Cuenta.id = - 1;
        }
            fclose(ArchivoCuenta);
    }
    return Cuenta;
    }

}

stCuenta BusquedaCuentaPorNumero (char ArchivoCuenta[], int NumeroDeCuenta){
    stCuenta Cuenta;
    int flag = 0;
    FILE * archi = fopen(ArchivoCuenta, "rb");

    if(archi){
        if(CantidadDatosArchivo(ArchivoCuenta, sizeof(stCuenta)) > 0){
            fseek(archi, 0, SEEK_SET);
            while(flag == 0 && fread(&Cuenta, sizeof(stCuenta), 1, archi) > 0){
                if(NumeroDeCuenta == Cuenta.nroCuenta){
                    flag = 1;
                }
            }
            if (flag == 0){
                Cuenta.id = - 1;
            }
        }
        else{
            printf("\nEl archivo se encuentra vacío.");
            Cuenta.id = - 1;
        }
            fclose(archi);
    }
    return Cuenta;
}

void DesactivarCuentaInteraccionUsuario(char ArchivoCuenta[]){
    stCuenta Cuenta;
    int NumeroCuentaAEliminar;
    int flag = 0;
    char Opcion = ' ';
    FILE *archivo = fopen(ArchivoCuenta, "r + b");
    if(archivo){
        if(CantidadDatosArchivo(ArchivoCuenta, sizeof(stCuenta)) > 0){
            do{
            printf("\Ingrese el numero de cuenta a desactivar: ");
            scanf("%d", &NumeroCuentaAEliminar);
            while(flag == 0 && fread(&Cuenta, sizeof(stCuenta), 1, archivo) > 0){
                if(NumeroCuentaAEliminar == Cuenta.nroCuenta){
                    flag = 1;
                }
            }
            if (flag == 1){
            fseek(archivo, -1*sizeof(stCuenta), SEEK_CUR);
            Cuenta = BusquedaCuentaPorNumero(ArchivoCuenta, NumeroCuentaAEliminar);
            Cuenta.EstadodeCuenta = - 1;
            fwrite(&Cuenta, sizeof(stCuenta), 1, archivo);
            Opcion = ESC;
            }
            else{
                printf("\nLa cuenta buscada no se encuentra en la base de datos. Presiona cualquier tecla para volver a ingresar el número de cuenta. Presiona ESC para salir.");
                Opcion = getch();
            }
            }while(Opcion != ESC);
        }
        else{
            printf("\nEl archivo se encuentra vacío.");
        }
        fclose(archivo);
    }
    else{
        printf("El archivo no puede abrirse.");
    }
}

int DesactivarCuentaAutomatico (char ArchivoCuentas[], int NumeroCliente){
    int Estado = 0;
    stCuenta Cuenta;
    stCuenta ArregloCuenta[3];
    FILE *archivo = fopen(ArchivoCuentas, "r + b");

    if(archivo){
        for(int i = 0; i < 2; i++){
            ArregloCuenta[i] = BusquedaCuentaParametro(ArchivoCuentas, NumeroCliente, i + 1);
            i++;
        }
        while(fread(&Cuenta, sizeof(stCuenta), 1, archivo) > 0){
            if (Cuenta.nroCuenta == ArregloCuenta[0].nroCuenta || Cuenta.nroCuenta == ArregloCuenta[1].nroCuenta || Cuenta.nroCuenta == ArregloCuenta[2].nroCuenta){
                Cuenta.EstadodeCuenta = - 1;
                fseek(archivo, -1*sizeof(stCuenta), SEEK_CUR);
                fwrite(&Cuenta, sizeof(stCuenta), 1, archivo);
                fclose(archivo);
            }
        }
    }
        else{
            Estado = - 1;
        }
        return Estado;
}

