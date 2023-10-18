#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED
#include "cuentas.h"
typedef struct{
    int id; /// campo único y autoincremental
    stCuenta Cuenta;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int hora; /// 0 a 23
    int minuto; /// 0 a 59
    int segundo; /// 0 a 59
    char detalle[100];///AGREGAR
    float importe;///AGREGAR
}stMovimiento;

stMovimiento cargaMovimientoAutomatico();
int getNowMes();
int getNowDia();
int maximodia (int MovimientoMes);
int getNowAnio();
int getNowHora();
int maximohora(int MovimientoDia);
int getNowMinuto();
int maximominuto(int MovimientoHora);
int getNowSegundo();
int maximosegundo(int MovimientoMinuto);
int IdMovimiento(char NombreArchivo[]);
stCuenta CuentaRandom (char NombreArchivo[]);
void MuestraMovimiento(stMovimiento Movimiento);
#endif // MOVIMIENTO_H_INCLUDED
