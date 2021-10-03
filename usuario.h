#include <stdio.h>
#include <string.h>

void LeerEntero(int *a);
void LimpiarCadena(char *cadena);

enum Sexo
{
	MASCULINO,
	FEMENINO
};


typedef struct user 
{
	public:
		int _idUsuario;
		char _username[64];
		char _password[16];
		char _nombre[32];
		char _primerApellido[128];
		char _segundoApellido[128];
		char _email[128];
		char _telefono[16];
		enum Sexo _sexo;

	public:

		int idUsuario(){return this->_idUsuario;}
		char* userName(){return this->_username;}
		char* password(){return this->_password;}
		char* nombre(){return this->_nombre;}
		char* primerApellido(){return this->_primerApellido;}
		char* segundoApellido(){return this->_segundoApellido;}
		char* email(){return this->_email;}
		char* telefono(){return this->_telefono;}
		Sexo sexo(){return this->_sexo;}



		int DatosUsuario()
		{
			printf("\n\t Ingrese el id: ");
			LeerEntero(&_idUsuario);

			printf("\t Ingrese su nombre de usuario: ");
			fgets(_username,sizeof(_username),stdin);
			LimpiarCadena(_username);

			printf("\t Ingrese su contrasena: ");
			fgets(_password,sizeof(_password),stdin);
			LimpiarCadena(_password);

			printf("\t Ingrese su nombre: ");
			fgets(_nombre,sizeof(_nombre),stdin);
			LimpiarCadena(_nombre);

			printf("\t Ingrese su primer apellido: ");
			fgets(_primerApellido,sizeof(_primerApellido),stdin);
			LimpiarCadena(_primerApellido);
			
			printf("\t Ingrese su segundo apellido: ");
			fgets(_segundoApellido,sizeof(_segundoApellido),stdin);
			LimpiarCadena(_segundoApellido);

			printf("\t Ingrese su e-mail: ");
			fgets(_email,sizeof(_email),stdin);
			LimpiarCadena(_email);

			printf("\t Ingrese su numero telefonico");
			fgets(_telefono,sizeof(_telefono),stdin);
			LimpiarCadena(_telefono);

			int aux_sexo;
			do{
				aux_sexo = 0;
				printf("\t Sexo: \n\t [0] masculino \n\t [1] femenino \n\t Ingrese su tipo de sexo:");
				LeerEntero(&aux_sexo);
				if (aux_sexo == 0) _sexo = MASCULINO;
				if (aux_sexo == 1) _sexo = FEMENINO;
			}while(aux_sexo != 0 && aux_sexo != 1);

			return 0;
		}

}Usuario;


void LeerEntero(int *a)
{
	char b;
	while(scanf("%d%c",a,&b) != 2 || b != '\n' || *a < 0)
	{
		printf("\t Ingreso mal el dato solicitado!, Vuelva a ingresarlo: ");
		fflush(stdin);
	}
}

void LimpiarCadena(char *cadena)
{
	int longitud = strlen(cadena);
	if (longitud > 0 && (cadena[longitud - 1] == '\n'))
	{
		cadena[longitud - 1] = '\0';
	}
}