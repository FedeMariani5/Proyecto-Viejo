#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "cuentas.h"
#include "archivoClientes.h"
#include "conio.h"
#define ARCHI_CLIENTES "clientes.dat"
#define ARCHI_CUENTAS "cuentas.dat"
#define ARCHI_MOVIMIENTOS "movimientos.dat"
#define ESC 27

///13087
int main(){
    //cargaArchivoCliente(ARCHI_CLIENTES);
    //cargaArchivoCuenta(ARCHI_CUENTAS,ARCHI_CLIENTES);
    CargaMasivaArchivoMovimientos(ARCHI_MOVIMIENTOS);
    MuestraArchivoDeMovimientos(ARCHI_MOVIMIENTOS);
    busquedaPorFecha (ARCHI_MOVIMIENTOS);

    return 0;
}
