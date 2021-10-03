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

void ImprimirMenu();
void LeerEntero(int *a);
void LimpiarCadena(char *cadena);


enum Sexo
{
	MASCULINO,
	FEMENINO
};

typedef struct user 
{
	private:
		int idUsuario;
		char username[64];
		char password[16];
		char nombre[32];
		char primerApellido[128];
		char segundoApellido[128];
		char email[128];
		char telefono[16];
		enum Sexo sexo;

	public:
		int Registrar()
		{
			printf("\n\t Ingrese el id: ");
			LeerEntero(&idUsuario);

			printf("\t Ingrese su nombre de usuario: ");
			fgets(username,sizeof(username),stdin);
			LimpiarCadena(username);

			printf("\t Ingrese su contrasena: ");
			fgets(password,sizeof(password),stdin);
			LimpiarCadena(username);

			printf("\t Ingrese su nombre: ");
			fgets(nombre,sizeof(nombre),stdin);
			LimpiarCadena(nombre);

			printf("\t Ingrese su primer apellido: ");
			fgets(primerApellido,sizeof(primerApellido),stdin);
			LimpiarCadena(primerApellido);
			
			printf("\t Ingrese su segundo apellido: ");
			fgets(segundoApellido,sizeof(segundoApellido),stdin);
			LimpiarCadena(segundoApellido);

			printf("\t Ingrese su e-mail: ");
			fgets(email,sizeof(email),stdin);
			LimpiarCadena(email);

			printf("\t Ingrese su numero telefonico");
			fgets(telefono,sizeof(telefono),stdin);
			LimpiarCadena(telefono);

			int aux_sexo;
			do{
				aux_sexo = 0;
				printf("\t Sexo: \n\t [0] masculino \n\t [1] femenino \n\t Ingrese su tipo de sexo:");
				LeerEntero(&aux_sexo);
				if (aux_sexo == 0) sexo = MASCULINO;
				if (aux_sexo == 1) sexo = FEMENINO;
			}while(aux_sexo != 0 || aux_sexo != 1);

			printf("%d",sexo);
		}

}Usuario;

int main(int argc, char const *argv[])
{
	Usuario usuario;
	usuario.Registrar();

	return 0;
}

void ImprimirMenu()
{
	printf("\n\t --- Sistema de control de usuarios --- ");
	printf("\n\n\t [1] Registrar nuevo usuario ");
	printf("\n\n\t [1] Buscar datos de usuario ");
	printf("\n\n\t [1] Eliminar usuario ");
	printf("\n\n\t [1] Eliminar usuario ");
	printf("\n\n\t [1] Modificar usuario ");
	printf("\n\n\t [1] Mostrar todos los usuarios ");
}

void LeerEntero(int *a)
{
	char b;
	while(scanf("%d%c",a,&b) != 2 || b != '\n' || *a < 0)
	{
		printf("\t Ingreso mal el dato solicitado!, Vuelva a ingresarlo: ");
		fflush(stdin);
	}
}


//https://stackoverflow.com/questions/22065675/get-text-from-user-input-using-c
//fgets will also pick-up the newline character \n at the end of input
void LimpiarCadena(char *cadena)
{
	int longitud = strlen(cadena);
	if (longitud > 0 && (cadena[longitud - 1] == '\n'))
	{
		cadena[longitud - 1] = '\0';
	}
}




