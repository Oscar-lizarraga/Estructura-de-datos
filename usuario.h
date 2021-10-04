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
	private:
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

		int getidUsuario(){return this->_idUsuario;}
		char* getuserName(){return this->_username;}
		char* getpassword(){return this->_password;}
		char* getnombre(){return this->_nombre;}
		char* getprimerApellido(){return this->_primerApellido;}
		char* getsegundoApellido(){return this->_segundoApellido;}
		char* getemail(){return this->_email;}
		char* gettelefono(){return this->_telefono;}
		Sexo getsexo(){return this->_sexo;}


		int IngresarDatos()
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

		static user* BuscarUsuarios(int* cantidad)
		{
			FILE* file;
			user *usuario;


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
				*cantidad = ftell(file) / sizeof(user); 
						printf("%d\n",*cantidad);
				//reservamos memoria para la cantidad de usuarios que hay
				usuario = (user*)malloc((*cantidad) * sizeof(user));
				
				//posicionamos el puntero al inicio del archivo
				fseek(file, 0, SEEK_SET);
				
				int i = 0;
				while(!feof(file))
				{
					fread(&usuario[i],sizeof(user),1,file);
					i++;
				}
				fclose(file);
				return usuario;
			}
		}

		static int RegistrarUsuario(user usuario)
		{
			FILE* file;
			file = fopen("usuarios.dat","ab");

			if(file == NULL)
			{
				return 0;
			}
			else
			{
				fwrite(&usuario, sizeof(user), 1, file);
				fclose(file);
				return 1;
			}
		}		

		static user BuscarUsuario(char *username)
		{
			FILE* file;
			user *usuario, aux_usuario;
			int cantidad;

			file = fopen("usuarios.dat","rb");
			if(file == NULL)
			{
				printf("ERROR en la apertura");
			}
			else
			{
				//posicionamos el puntero al final del archivo
				fseek(file, 0, SEEK_END); 
				
				//obtenemos la cantidad de usuarios, ftell devuelve la cantidad de bits y lo dividimos entre la cantidad de usuarios
				cantidad = ftell(file) / sizeof(user); 
				
				//reservamos memoria para la cantidad de usuarios que hay
				usuario = (user*)malloc(cantidad * sizeof(user));
				
				//posicionamos el puntero al inicio del archivo
				fseek(file, 0, SEEK_SET);
				
				int i = 0;
				while (!feof(file)) {
					fread(&usuario[i], sizeof(user), 1, file);
					if (strcmp(usuario[i].getuserName(),username) == 0)
					{
						aux_usuario = usuario[i]; 
						//MostrarUsuarios(&usuario[i],1);
						break;
					}
					i++;
				}
				fclose(file);
				return aux_usuario;
			}
		}

		static void EliminarUsuario(char *username)
		{
			FILE* file;
			FILE* ax_file;
			user *usuario;
			int cantidad;

			file = fopen("usuarios.dat","rb");
			ax_file = fopen("temporal.dat","wb");

			if(file == NULL)
			{
				printf("ERROR en la apertura");
			}
			else
			{
				//posicionamos el puntero al final del archivo
				fseek(file, 0, SEEK_END); 
				
				//obtenemos la cantidad de usuarios, ftell devuelve la cantidad de bits y lo dividimos entre la cantidad de usuarios
				cantidad = ftell(file) / sizeof(user);
				printf("%d",cantidad); 
				
				//reservamos memoria para la cantidad de usuarios que hay
				usuario = (user*)malloc(cantidad * sizeof(user));
				
				//posicionamos el puntero al inicio del archivo
				fseek(file, 0, SEEK_SET);
				
				for (int i = 0; i < cantidad; i++)
				{
					fread(&usuario[i], sizeof(user), 1, file);
					if (strcmp(usuario[i].getuserName(),username) != 0)
					{				
						fwrite(&usuario[i],sizeof(user),1,ax_file);
					}
				}

				fclose(file);
				fclose(ax_file);

				remove("usuarios.dat");
				rename("temporal.dat", "usuarios.dat");
				printf("\n\tELIMINACION realizada correctamente");
			}
		}

		static void EditarUsuario(char *username)
		{
			FILE* file;
			user *usuario;
			int cantidad;

			file = fopen("usuarios.dat","rb+");
			if(file == NULL)
			{
				printf("ERROR en la apertura");
			}
			else
			{
				//posicionamos el puntero al final del archivo
				fseek(file, 0, SEEK_END); 
				
				//obtenemos la cantidad de usuarios, ftell devuelve la cantidad de bits y lo dividimos entre la cantidad de usuarios
				cantidad = ftell(file) / sizeof(user); 
				
				//reservamos memoria para la cantidad de usuarios que hay
				usuario = (user*)malloc(cantidad * sizeof(user));
				
				//posicionamos el puntero al inicio del archivo
				fseek(file, 0, SEEK_SET);
				
				for (int i = 0; i < cantidad; i++)
				{
					fread(&usuario[i], sizeof(user), 1, file);
					if (strcmp(usuario[i].getuserName(),username) == 0)
					{		
						fseek(file,ftell(file)-sizeof(user), SEEK_SET);
						usuario[i].IngresarDatos();	
						fwrite(&usuario[i],sizeof(user),1,file);
						break;
					}
				}
				fclose(file);
				printf("\n\t EDICION registrada correctamente");
			}
		}

		static bool ValidarAcceso(char *username, char *contrasena)
		{
			FILE* file;
			user *usuario, aux_usuario;
			int cantidad;

			file = fopen("usuarios.dat","rb");
			if(file == NULL)
			{
				return false;
				printf("ERROR en la apertura");
			}
			else
			{
				//posicionamos el puntero al final del archivo
				fseek(file, 0, SEEK_END); 
				
				//obtenemos la cantidad de usuarios, ftell devuelve la cantidad de bits y lo dividimos entre la cantidad de usuarios
				cantidad = ftell(file) / sizeof(user); 
				
				//reservamos memoria para la cantidad de usuarios que hay
				usuario = (user*)malloc(cantidad * sizeof(user));
				
				//posicionamos el puntero al inicio del archivo
				fseek(file, 0, SEEK_SET);
				
				int i = 0;
				while (!feof(file)) {
					fread(&usuario[i], sizeof(user), 1, file);
					if (strcmp(usuario[i].getuserName(),username) == 0 && strcmp(usuario[i].getpassword(),contrasena) == 0)
					{
						return true;
						break;
					}
					i++;
				}
				fclose(file);
				return false;
			}
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

//Limpiamos cadena porque la funcion fgets deja un espacio al final de cada read
void LimpiarCadena(char *cadena)
{
	int longitud = strlen(cadena);
	if (longitud > 0 && (cadena[longitud - 1] == '\n'))
	{
		cadena[longitud - 1] = '\0';
	}
}

