/***********************************************************
 * Estructura de datos, practica 1,2.
 * 
 * Fecha de ultima revision: 02/10/21
 * 
 * Colaboradores:
 * Lizarraga Pelayo Oscar
 * Valades Herrera Elisa
 * Ferrer Flores Ximena Mailyn
 * Cruz Mendez Yuliana Vianney 
 * 
 * *********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usuario.h"

void ImprimirMenu();
void MostrarUsuarios(Usuario *usuario, int cantidad);


int main(int argc, char const *argv[])
{
	Usuario usuario;
	Usuario *mostrar;
	char aux_username[64];
	char aux_password[16];
	int opcion, cantidad;
	bool acceso = false;	
	do
	{
		printf("\n\t Ingrese username: ");
		fgets(aux_username,sizeof(aux_username),stdin);
		LimpiarCadena(aux_username);
		printf("\n\t Ingrese contrasena: ");
		fgets(aux_password,sizeof(aux_password),stdin);
		LimpiarCadena(aux_password);		
		acceso = user::ValidarAcceso(aux_username,aux_password);
		if (!acceso)
		{
			printf("\n\t Datos incorrectos");
		}
	}while(acceso == 0);

	do
	{
		ImprimirMenu();
		LeerEntero(&opcion);
		switch(opcion)
		{
			case 1:
				usuario.IngresarDatos();
				user::RegistrarUsuario(usuario);
				break;
			case 2:
				mostrar = user::BuscarUsuarios(&cantidad);
				MostrarUsuarios(mostrar,cantidad);
				break;
			case 3:
				printf("\t Ingrese el username a buscar: ");
				fgets(aux_username,sizeof(aux_username),stdin);
				LimpiarCadena(aux_username);
				usuario = user::BuscarUsuario(aux_username);
				MostrarUsuarios(&usuario,1);
				break;
			case 4:
				printf("\t Ingrese el username a editar: ");
				fgets(aux_username,sizeof(aux_username),stdin);
				LimpiarCadena(aux_username);
				user::EditarUsuario(aux_username);
				break;
			case 5:
				printf("\t Ingrese el username a eliminar: ");
				fgets(aux_username,sizeof(aux_username),stdin);
				LimpiarCadena(aux_username);
				user::EliminarUsuario(aux_username);
				break;
			default:
				break;
		}
	} while (opcion < 1 || opcion >5);

	return 0;
}

void MostrarUsuarios(Usuario *usuario, int cantidad)
{
	char s[20];
	printf("\n\t\t    ==> Listado de usuarios registrados <==\n");
	printf("     ---------------------------------------------------------------------------------------\n");
	printf("\t%s %s %s %8s %10s %10s %10s %10s %10s \n", 
			"idUsuario", "userName", "password", "nombre", "primerApellido", "segundoApellido", "e-mail", "telefono", "sexo");
	printf("     ---------------------------------------------------------------------------------------\n");
	for (int i = 0; i < cantidad; i++)
	{
		if (usuario[i].getsexo() == 0)
		{
			strcpy(s,"Masculino");
		}
		else
		{
			strcpy(s,"Femenino");
		}
		printf("\t%d %s %s %8s %15s %10s %10s %10s %10s\n",usuario[i].getidUsuario(), usuario[i].getuserName(), usuario[i].getpassword(), 
			usuario[i].getnombre(), usuario[i].getprimerApellido(),usuario[i].getsegundoApellido(), usuario[i].getemail(), usuario[i].gettelefono(), s);
	}
}

void ImprimirMenu()
{
	printf("\n\t --- Sistema de control de usuarios --- ");
	printf("\n\t [1] Registrar nuevo usuario ");
	printf("\n\t [2] Mostrar todos los usuarios ");
	printf("\n\t [3] Buscar datos de usuario ");
	printf("\n\t [4] Modificar usuario ");
	printf("\n\t [5] Eliminar usuario ");
}



/*Consultas
	Que es un enum 
	https://www.geeksforgeeks.org/enumeration-enum-c/

	fgets clean buffer
	https://stackoverflow.com/questions/22065675/get-text-from-user-input-using-c

	fwrite
	https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm

	fseek
	https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm

	fread
	https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm

	ftell
	https://www.tutorialspoint.com/c_standard_library/c_function_ftell.htm
*/





