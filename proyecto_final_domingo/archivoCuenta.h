#ifndef ARCHIVOCUENTA_H_INCLUDED
#define ARCHIVOCUENTA_H_INCLUDED

stCuenta BusquedaCuentaParametro (char archivocuenta[], int NumeroDeCliente, int TipodeCuenta);
void cargaArchivoCuenta(char ArchivoCuenta[], char ArchivoClientes[]);
void BusquedaCuentaInteraccionUsuario(char archivocuenta[]);
stCuenta BusquedaCuentaPorID (char archivocuenta[], int IDCuentaBuscada);
void MuestraArchivoDeCuentas(char ArchivoCuenta[], char ArchivoCliente[]);
stCuenta BusquedaCuentaPorNumero (char ArchivoCuenta[], int NumeroDeCuenta);
void DesactivarCuentaInteraccionUsuario(char ArchivoCuenta[]);
int DesactivarCuentaAutomatico (char ArchivoCuentas[], int NumeroCliente);

#endif // ARCHIVOCUENTA_H_INCLUDED
