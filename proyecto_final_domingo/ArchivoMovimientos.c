#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "archivoClientes.h"
#include "movimiento.h"
#include "eventuales.h"
#include "string.h"
#include "conio.h"
#define ARCHI_CLIENTES "clientes.dat"
#define ARCHI_MOVIMIENTOS "movimientos.dat"
#define ESC 27


void CargaMasivaArchivoMovimientos(char NombreArchivo[]){
    for(int i = 0; i < 1000; i++){
        FILE *ArchivoMovimientos = fopen(NombreArchivo, "ab");
        stMovimiento Movimiento;
        if(ArchivoMovimientos){
            Movimiento = cargaMovimientoAutomatico();
            if(Movimiento.id != - 1){
                fwrite(&Movimiento, sizeof(stMovimiento), 1, ArchivoMovimientos);
            }
            fclose(ArchivoMovimientos);
        }
    }
}

void MuestraArchivoDeMovimientos(char NombreArchivo[]){
    stMovimiento Movimiento;
    FILE* ArchivoMovimientos = fopen(NombreArchivo, "rb");
    if(ArchivoMovimientos){
        while(fread(&Movimiento, sizeof(stMovimiento), 1, ArchivoMovimientos) > 0)
        {
            MuestraMovimiento(Movimiento);
        }
        if (CantidadDatosArchivo(NombreArchivo, sizeof(stMovimiento)) == 0){
            printf("El archivo se encuentra vacío.");
        }
        fclose(ArchivoMovimientos);
    }
}





void busquedaPorFecha (char nombreArchivo[]){
int  dia;
int mes;
int anio;
char opcion=0;
stMovimiento movimiento;
    FILE * ArchiMovimientos=fopen(nombreArchivo, "rb");
     printf("Ingrese la fecha de los movimientos que desea ve, en formato d/m/aa: ");
    scanf("%d",&dia);
    scanf("%d",&mes);
    scanf("%d",&anio);

    if (ArchiMovimientos){
        while (fread(&movimiento,sizeof (stMovimiento), 1, ArchiMovimientos)>0 && opcion!=ESC){
            if (movimiento.dia==dia && movimiento.mes==mes && movimiento.anio==anio){
                MuestraMovimiento(movimiento);
            }
            else {
                printf("En la fecha ingresada no se han efectuado movimientos. Por favor ingrese otra fecha o presione ESC para salir");
                scanf("%d",&dia);
                scanf("%d",&mes);
                scanf("%d",&anio);
                opcion=getch();
            }


        }

        fclose(ArchiMovimientos);


    }






}
