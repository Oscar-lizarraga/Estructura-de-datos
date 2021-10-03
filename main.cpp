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

void ImprimirResultado(int a);
void ImprimirMenu();
int RegistrarUsuario(Usuario usuario);
int EliminarUsuario();
int ModificarUsuario();
int MostrarUsuarios();




int main(int argc, char const *argv[])
{
	Usuario usuario;

	int opcion;
	do
	{
		ImprimirMenu();
		LeerEntero(&opcion);
		switch(opcion)
		{
			case 1:
				usuario.DatosUsuario();
				ImprimirResultado(RegistrarUsuario(usuario));
				break;
			case 2:
				MostrarUsuarios();
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			default:
				break;
		}
	} while (opcion < 1 || opcion >5);

	return 0;
}


int RegistrarUsuario(Usuario usuario)
{
	FILE* file;
	file = fopen("usuarios.dat","ab");

	if(file == NULL)
	{
		return 0;
	}
	else
	{
		fwrite(&usuario, sizeof(usuario), 1, file);
		fclose(file);
		return 1;
	}
}

int MostrarUsuarios()
{
	FILE* file;
	Usuario *usuario;
	Usuario aux_usuario;
	int cantidad;

	file = fopen("usuarios.dat","rb");
	if(file == NULL)
	{
		return 0;
	}
	else
	{
		//posicionamos el puntero al final del archivo
		fseek(file, 0, SEEK_END); 
		
		//obtenemos la cantidad de usuarios, ftell devuelve la cantidad de bits y lo dividimos entre la cantidad de usuarios
		cantidad = ftell(file) / sizeof(Usuario); 
		
		//reservamos memoria para la cantidad de usuarios que hay
		usuario = (Usuario*)malloc(cantidad * sizeof(Usuario));
		
		//posicionamos el puntero al inicio del archivo
		fseek(file, 0, SEEK_SET);
		
		int i = 0;
		while(!feof(file))
		{
			fread(&usuario[i],sizeof(usuario[i]),1,file);
			i++;
		}
		printf("%s",usuario[0].nombre());
		fclose(file);

		return 1;
	}
}








void ImprimirMenu()
{
	printf("\n\t --- Sistema de control de usuarios --- ");
	printf("\n\t [1] Registrar nuevo usuario ");
	printf("\n\t [1] Buscar datos de usuario ");
	printf("\n\t [1] Eliminar usuario ");
	printf("\n\t [1] Modificar usuario ");
	printf("\n\t [1] Mostrar todos los usuarios ");
}

void ImprimirResultado(int a)
{
	if (a)
	{
		printf("\n\t La operacion se realizo con exito");
	}
	else
	{
		printf("\n\t La operacion no se realizo correctamente");
	}
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
*/





