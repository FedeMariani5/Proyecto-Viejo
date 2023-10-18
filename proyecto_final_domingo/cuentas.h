#ifndef CUENTAS_H_INCLUDED
#define CUENTAS_H_INCLUDED

typedef struct{
    int id; /// campo �nico y autoincremental
    int idCliente; /// Id del Cliente due�o de la Cuenta;
    int nroCuenta;
    int tipoDeCuenta; /// 1. Caja de Ahorro en Pesos, 2. Caja de Ahorro en D�lares, 3. Cta Cte en $
    float costoMensual; /// Costo de mantenimiento del producto;
    float Saldo;
    int EstadodeCuenta; /// 0 si est� activo - 1 si est� eliminado
}stCuenta;

stCuenta cargaCuenta(char ArchivoCuentas[], char ArchivoClientes[]);
void muestraCuentas(stCuenta cuenta, stCliente Cliente);
int IdCuenta(char nombrearchivo[]);
int NroDeCuenta (char nombrearchivo[]);



#endif // CUENTAS_H_INCLUDED
