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
 khknn
 * 
 * *********************************************************/

#include <stdio.h>

void ImprimirMenu();
void LeerCadena();
int LeerEntero();


enum Sexo
{
	masculino,
	femenino
};

typedef struct user 
{
	private:
		int idUsuario;
		char username[32];
		char password[16];
		char nombre[128];
		char primerApellido[128];
		char segundoApellido[128];
		char email[128];
		char telefono[16];
		enum Sexo sexo;

	public:
		int registrar()
		{
			printf("\n\t Ingrese el id: ");
			idUsuario = LeerEntero();
			printf("\n\t Ingrese su nombre de usuario");
			fgets(username, sizeof(username), stdin);

		}

}Usuario;

int main(int argc, char const *argv[])
{
	/* code */
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

int LeerEntero()
{
	int n; char a;
	while(scanf("%d%c",&n,&a) != 2 || a != '\n' || n < 0)
	{
		printf("\n\t Ingreso mal el dato solicitado!");
		fflush(stdin);
	}
	return n;
}


