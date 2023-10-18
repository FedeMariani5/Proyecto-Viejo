#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "archivoClientes.h"
#include "cuentas.h"
#include "archivoCuenta.h"
#include "conio.h"
#include "eventuales.h"

#define ARCHI_CLIENTES "clientes.dat"

#define ESC 27

int randomRango(int minimorandom, int maximorandom){
    return rand()%(maximorandom-minimorandom)+minimorandom;
}

int CantidadDatosArchivo(char archivo[], int PesoTipodeDato){
    FILE *archi = fopen(archivo, "rb");
    int CantidadDatos;

    if(archi){
        fseek(archi, 0, SEEK_END);
        CantidadDatos = ftell(archi) / PesoTipodeDato;
        fclose(archi);
    }

    else{
        printf("\nEl archivo no puede abrirse correctamente.");
        CantidadDatos = - 1;
    }
    return CantidadDatos;
}

int Archivo2ArregloCuenta (char Archivo[],stCuenta Arreglo[], int dimension){
    int Validos = 0;
    int i = 0;
    FILE *archivo = fopen(Archivo, "rb");

    if(archivo){
        while(i < dimension && fread(&Arreglo[i], sizeof(stCuenta), 1, archivo) > 0){
            i++;
        }
        Validos = i;
    }
    else{
        Validos = - 1;
    }
    return Validos;
}
