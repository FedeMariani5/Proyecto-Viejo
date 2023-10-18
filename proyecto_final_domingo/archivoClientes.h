#ifndef ARCHIVOCLIENTES_H_INCLUDED
#define ARCHIVOCLIENTES_H_INCLUDED

stCliente BusquedaClientePorID(char nombreArchivo[], int IDCliente);
void cargaArchivoCliente(char nombreArchivo[]);
void muestraArchivoDeClientes(char nombreArchivo[]);
int CantidadDatosArchivo(char archivo[], int PesoTipodeDato);
stCliente BusquedaClienteInteraccionUsuario(char nombreArchivo[]);
stCliente BusquedaClienteParametro(char nombreArchivo[], int NumeroDeCliente);
void DesactivarCliente(char ArchivoCliente[], char ArchivoCuenta[]);

#endif // ARCHIVOCLIENTES_H_INCLUDED
