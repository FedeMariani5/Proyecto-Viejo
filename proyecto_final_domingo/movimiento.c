#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clientes.h"
#include "archivoClientes.h"
#include "cuentas.h"
#include "conio.h"
#include "movimiento.h"
#include "eventuales.h"
#define ARCHI_CLIENTES "clientes.dat"
#define ARCHI_CUENTAS "cuentas.dat"
#define ARCHI_MOVIMIENTOS "movimientos.dat"
#define ESC 27
#define MINIMO -10000
#define MAXIMO 100000
#define DIM 100

stMovimiento cargaMovimientoAutomatico(){
    stMovimiento movimiento;

    movimiento.Cuenta = CuentaRandom(ARCHI_CUENTAS);
    if (movimiento.Cuenta.id != - 1){
    movimiento.id = IdMovimiento(ARCHI_MOVIMIENTOS) + 1;
    movimiento.mes = randomRango(1, getNowMes());
    movimiento.dia = randomRango(1, maximodia(movimiento.mes));
    movimiento.anio = getNowAnio();
    movimiento.hora = randomRango(0, maximohora(movimiento.dia));
    movimiento.minuto = randomRango(0, maximominuto(movimiento.hora));
    movimiento.segundo = randomRango(0, maximosegundo(movimiento.minuto));
    movimiento.importe = randomRango(MINIMO, MAXIMO);

    if(movimiento.importe < 0){
        getDetalleNegativo(movimiento.detalle);
    }
    else{
        getDetallePositivo(movimiento.detalle);
    }
    }
    else{
        movimiento.id = - 1;
    }

    return movimiento;

}



void getDetalleNegativo(char name[]){
    char names[][100]= {"Transferencia hacia terceros", "Pago", "Gastos Generales", "Alquiler", "Transferencia a cuenta propia", "Pago de tarjeta de credito", "Pago de tarjeta de debito"};
    strcpy(name, names[randomRango(0,sizeof(names)/(sizeof(char)*100))]);
}

void getDetallePositivo(char name[]){
    char names[][100]= {"Transferencia de terceros", "Credito de haberes", "Acreditacion de plazo fijo", "Acreditacion de alquiler", "Transferencia desde cuenta propia", "Devolucion de pago tarjeta de credito", "Devolucion de pago tarjeta de debito"};
    strcpy(name, names[randomRango(0,sizeof(names)/(sizeof(char)*100))]);
}

int getNowMes(){

    char date[100];
    time_t tiempo = time(0);
    struct tm * tlocal = localtime(&tiempo);
    strftime(date, 128, "%m", tlocal);
    int mesactual = (int)strtol(date, NULL, 10);

    return mesactual;
}

int getNowAnio(){

    char date[100];
    time_t tiempo = time(0);
    struct tm * tlocal = localtime(&tiempo);
    strftime(date, 128, "%y", tlocal);
    int anioactual = (int)strtol(date, NULL, 10);

    return anioactual;
}

int getNowDia(){

    char date[100];
    time_t tiempo = time(0);
    struct tm * tlocal = localtime(&tiempo);
    strftime(date, 128, "%d", tlocal);
    int diaactual = (int)strtol(date, NULL, 10);

    return diaactual;
}


int maximodia (int MovimientoMes){
    int cantidaddias;
    if(MovimientoMes != getNowMes()){
        if((MovimientoMes%2 != 0 && MovimientoMes <= 7) || (MovimientoMes%2 == 0 && MovimientoMes >= 8)){
            cantidaddias = 31;
        }
        else{
            if(MovimientoMes != 2){
                cantidaddias = 30;
            }
            else{
                cantidaddias = 28;
            }
        }
    }
    else{
        cantidaddias = getNowDia();
    }
    return cantidaddias;
}

int getNowHora(){

    char date[100];
    time_t tiempo = time(0);
    struct tm * tlocal = localtime(&tiempo);
    strftime(date, 128, "%d", tlocal);
    int diaactual = (int)strtol(date, NULL, 10);

    return diaactual;
}

int maximohora(int MovimientoDia){
    int maximohoras;
    if(MovimientoDia == getNowDia()){
        maximohoras = getNowHora();
    }
    else{
        maximohoras = 23;
    }
    return maximohoras;
}

int getNowMinuto(){

    char date[100];
    time_t tiempo = time(0);
    struct tm * tlocal = localtime(&tiempo);
    strftime(date, 128, "%M", tlocal);
    int minutoactual = (int)strtol(date, NULL, 10);

    return minutoactual;
}

int maximominuto(int MovimientoHora){
    int maximominutos;
    if(MovimientoHora == getNowHora()){
        maximominutos = getNowMinuto();
    }
    else{
        maximominutos = 59;
    }
    return maximominutos;
}

int getNowSegundo(){

    char date[100];
    time_t tiempo = time(0);
    struct tm * tlocal = localtime(&tiempo);
    strftime(date, 128, "%S", tlocal);
    int segundoactual = (int)strtol(date, NULL, 10);

    return segundoactual;
}

int maximosegundo(int MovimientoMinuto){
    int maximosegundos;
    if(MovimientoMinuto == getNowMinuto()){
        maximosegundos = getNowSegundo();
    }
    else{
        maximosegundos = 59;
    }
    return maximosegundos;
}

int IdMovimiento(char NombreArchivo[]){
    stMovimiento Movimiento;
    FILE * ArchivoMovimiento = fopen(NombreArchivo, "rb");
    int ultimoIdMovimiento = 0;

    if(ArchivoMovimiento)
    {
        if(CantidadDatosArchivo(NombreArchivo, sizeof(stMovimiento)) > 0){
            fseek(ArchivoMovimiento, -1*sizeof(stMovimiento), SEEK_END);
            fread(&Movimiento, sizeof(stMovimiento), 1, ArchivoMovimiento);
            ultimoIdMovimiento = Movimiento.id;
        }
        fclose(ArchivoMovimiento);
    }
    return ultimoIdMovimiento;
}

 stCuenta CuentaRandom (char NombreArchivo[]){
    int CuentaRandom;
    stCuenta Cuenta;
    FILE *ArchivoCuenta = fopen(NombreArchivo, "rb");

    if(ArchivoCuenta){
        CuentaRandom = randomRango(1, CantidadDatosArchivo(NombreArchivo, sizeof(stCuenta)));
        fseek(ArchivoCuenta, CuentaRandom - sizeof(stCuenta), SEEK_SET);
        fread(&Cuenta, sizeof(stCuenta), 1, ArchivoCuenta);
        fclose(ArchivoCuenta);
    }
    return Cuenta;
}

void MuestraMovimiento(stMovimiento Movimiento){
    if(Movimiento.id != - 1){
        printf("\n=====================================================");
        printf("\nNúmero de Cuenta: %d", Movimiento.Cuenta.nroCuenta);
        printf("\nFecha: %d/%d/%d %d:%d:%d", Movimiento.dia, Movimiento.mes, Movimiento.anio, Movimiento.hora, Movimiento.minuto, Movimiento.segundo);
        if(Movimiento.Cuenta.tipoDeCuenta != 2){
            printf("\nMonto: $%.2f", Movimiento.importe);
        }
        else{
            printf("\nMonto: US$%.2f", Movimiento.importe);
        }
        printf("\nConcepto: %s", Movimiento.detalle);
        printf("\n=====================================================");
    }else{
        printf("\nEl movimiento buscado no se encuentra en la base de datos.");
    }
}



