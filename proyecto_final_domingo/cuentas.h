#ifndef CUENTAS_H_INCLUDED
#define CUENTAS_H_INCLUDED

typedef struct{
    int id; /// campo único y autoincremental
    int idCliente; /// Id del Cliente dueño de la Cuenta;
    int nroCuenta;
    int tipoDeCuenta; /// 1. Caja de Ahorro en Pesos, 2. Caja de Ahorro en Dólares, 3. Cta Cte en $
    float costoMensual; /// Costo de mantenimiento del producto;
    float Saldo;
    int EstadodeCuenta; /// 0 si está activo - 1 si está eliminado
}stCuenta;

stCuenta cargaCuenta(char ArchivoCuentas[], char ArchivoClientes[]);
void muestraCuentas(stCuenta cuenta, stCliente Cliente);
int IdCuenta(char nombrearchivo[]);
int NroDeCuenta (char nombrearchivo[]);



#endif // CUENTAS_H_INCLUDED
