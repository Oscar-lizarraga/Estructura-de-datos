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
void MostrarUsuarios(Usuario *usuario, int cantidad);

int RegistrarUsuario(Usuario usuario);
int EliminarUsuario(char *username);
int ModificarUsuario(char *username);
int BuscarUsuarios();
int BuscarUsuario(char* username);
int EditarUsuario(char* username);


int main(int argc, char const *argv[])
{
	Usuario usuario;
	char aux_username[64];
	int opcion;
	do
	{
		ImprimirMenu();
		LeerEntero(&opcion);
		switch(opcion)
		{
			case 1:
				usuario.IngresarDatos();
				ImprimirResultado(RegistrarUsuario(usuario));
				break;
			case 2:
				ImprimirResultado(BuscarUsuarios());
				break;
			case 3:
				printf("\t Ingrese el username a buscar: ");
				fgets(aux_username,sizeof(aux_username),stdin);
				LimpiarCadena(aux_username);
				BuscarUsuario(aux_username);
				break;
			case 4:
				printf("\t Ingrese el username a editar: ");
				fgets(aux_username,sizeof(aux_username),stdin);
				LimpiarCadena(aux_username);
				EditarUsuario(aux_username);
				break;
			case 5:
				printf("\t Ingrese el username a eliminar: ");
				fgets(aux_username,sizeof(aux_username),stdin);
				LimpiarCadena(aux_username);
				EliminarUsuario(aux_username);
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
		fwrite(&usuario, sizeof(Usuario), 1, file);
		fclose(file);
		return 1;
	}
}

int BuscarUsuarios()
{
	FILE* file;
	Usuario *usuario;
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
				printf("%d\n",cantidad);
		//reservamos memoria para la cantidad de usuarios que hay
		usuario = (Usuario*)malloc(cantidad * sizeof(Usuario));
		
		//posicionamos el puntero al inicio del archivo
		fseek(file, 0, SEEK_SET);
		
		int i = 0;
		while(!feof(file))
		{
			fread(&usuario[i],sizeof(Usuario),1,file);
			i++;
		}
		fclose(file);
		MostrarUsuarios(usuario, cantidad);
		return 1;
	}
}

int BuscarUsuario(char *username)
{
	FILE* file;
	Usuario *usuario;
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
		while (!feof(file)) {
			fread(&usuario[i], sizeof(Usuario), 1, file);
			if (strcmp(usuario[i].getuserName(),username) == 0)
			{
				MostrarUsuarios(&usuario[i],1);
				break;
			}
			i++;
		}

		fclose(file);
		return 1;
	}
}

int EliminarUsuario(char *username)
{

	FILE* file;
	FILE* ax_file;
	Usuario *usuario;
	int cantidad;

	file = fopen("usuarios.dat","rb");
	ax_file = fopen("temporal.dat","wb");

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
		printf("%d",cantidad); 
		
		//reservamos memoria para la cantidad de usuarios que hay
		usuario = (Usuario*)malloc(cantidad * sizeof(Usuario));
		
		//posicionamos el puntero al inicio del archivo
		fseek(file, 0, SEEK_SET);
		
		for (int i = 0; i < cantidad; i++)
		{
			fread(&usuario[i], sizeof(Usuario), 1, file);
			if (strcmp(usuario[i].getuserName(),username) != 0)
			{				
				fwrite(&usuario[i],sizeof(Usuario),1,ax_file);
			}
		}

		fclose(file);
		fclose(ax_file);

		remove("usuarios.dat");
		rename("temporal.dat", "usuarios.dat");
		return 1;
	}
}

int EditarUsuario(char *username)
{
	FILE* file;
	Usuario *usuario;
	int cantidad;

	file = fopen("usuarios.dat","rb+");
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
		
		for (int i = 0; i < cantidad; i++)
		{
			fread(&usuario[i], sizeof(Usuario), 1, file);
			if (strcmp(usuario[i].getuserName(),username) == 0)
			{		
				fseek(file,ftell(file)-sizeof(Usuario), SEEK_SET);
				usuario[i].IngresarDatos();	
				fwrite(&usuario[i],sizeof(Usuario),1,file);
				break;
			}
		}
		fclose(file);
		return 1;
	}
}


void MostrarUsuarios(Usuario *usuario, int cantidad)
{
	printf("\n\t\t    ==> Listado de usuarios registrados <==\n");
	printf("     ---------------------------------------------------------------------------------------\n");
	printf("\t%s %s %s %8s %10s %10s %10s %10s %10s \n", 
			"idUsuario", "userName", "password", "nombre", "primerApellido", "segundoApellido", "e-mail", "telefono", "sexo");
	printf("     ---------------------------------------------------------------------------------------\n");
	for (int i = 0; i < cantidad; i++)
	{
		printf("\t%d %s %s %8s %15s %10s %10s %10s\n",usuario[i].getidUsuario(), usuario[i].getuserName(), usuario[i].getpassword(), 
			usuario[i].getnombre(), usuario[i].getprimerApellido(),usuario[i].getsegundoApellido(), usuario[i].getemail(), usuario[i].gettelefono());
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

void ImprimirResultado(int a)
{
	if (a)
	{
		printf("\n\t La operacion se realizo con exito");
	}
	else
	{
		printf("\n\t No se encontro el archivo");
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

	fread
	https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm

	ftell
	https://www.tutorialspoint.com/c_standard_library/c_function_ftell.htm
*/





