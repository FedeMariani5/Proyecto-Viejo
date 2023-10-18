#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

typedef struct{
    int id; /// campo único y autoincremental
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30];
    char domicilio[45];
    char telefono[12];
    int EstadoDeCliente; /// 0 si está activo - 1 si está eliminado

}stCliente;

stCliente cargaCliente();
void muestraClientes(stCliente cliente);
int Id(char nombrearchivo[]);
int validarDni(char DNICliente[], char nombrearchivo[]);
int validarEmail(char EmailCliente[], char NombreArchivo[]);
int validarTelefono(char Telefono[], char NombreArchivo[]);

#endif // CLIENTES_H_INCLUDED
