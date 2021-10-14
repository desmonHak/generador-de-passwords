#ifndef __MAX_VALUE_CHAR

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define __MAX_VALUE_CHAR 128
#define __LOW_VALUE_CHAR 33

struct complex1
{

	uint16_t longitud;
	uint8_t *password;

} typedef complex1;

class Password
{
public:
	Password()
	{
		if (longitud == 0x0)
		{
			longitud = 10;
		}
		generarPassword();
	}
	Password(uint16_t longitud)
	{
		this->longitud = longitud;
		generarPassword();
	}
	~Password()
	{
		if (password != NULL)
		{
			password = NULL;
			free(password);
		}
	}

	bool esFuerte()
	{
		if (strlen((const char *)password) <= 8)
		{
			return false;
		}
		else
		{
			uint8_t rangos[3][2] = {
				0x41, 0x5a, // "A", "Z" == rango mayusculas
				0x30, 0x39, // "0", "9" == rango numerico
				0x61, 0x7a	// "a", "z" == rango minusculas
			};
			uint8_t cantidadDeCondiciones[3];
			/*
			* posicion 0 = numero de mayusculas = 0
			* posicion 1 = numero de minuscula  = 1
			* posicion 2 = numero de numeros    = 5
			* retorna true si posicion 0 == 2 &&
			* posicion 1 == 1 && posicion 2 == 5
			*/
			for (int i = 0; i <= longitud; i++)
			{
				if (password[i] >= rangos[0][0] && password[i] <= rangos[0][1])
				{
					cantidadDeCondiciones[0]++;
				}
				else if (password[i] >= rangos[1][0] && password[i] <= rangos[1][1])
				{
					cantidadDeCondiciones[2]++;
				}
				else if (password[i] >= rangos[2][0] && password[i] <= rangos[2][1])
				{
					cantidadDeCondiciones[1]++;
				}
			}

			if (cantidadDeCondiciones[0] >= 2 &&
				cantidadDeCondiciones[1] >= 1 &&
				cantidadDeCondiciones[2] >= 5)
			{
				return true;
			}
		}
	}

	void generarPassword()
	{
		password = (uint8_t *)malloc(sizeof(uint8_t) * longitud);
		time_t t;
		srand((unsigned)time(&t));

		for (uint8_t i = 0; i < longitud; i++)
		{
			password[i] = rand() % (__MAX_VALUE_CHAR + 1 - __LOW_VALUE_CHAR) + __LOW_VALUE_CHAR;
		}
	}

	complex1 getLongitudAndPassword()
	{
		complex1 structDatosComplex = {longitud, password};
		return structDatosComplex;
	}

	void setLongitudPassword(uint16_t longitud)
	{
		this->longitud = longitud;
	}

private:
	uint16_t longitud;
	uint8_t *password;
};

class Ejecutable
{
public:
	Password *array;
	bool *arrayBoolean;
	Ejecutable() {}

	~Ejecutable()
	{
		if (array != NULL)
		{
			array = NULL;
			free(array);
		}
	}
	void exec()
	{
		uint16_t sizeArray;

		printf("ingresa la cantidad de passwords a generar: ");
		scanf("%hd", &sizeArray);
		puts("");

		array = (Password *)malloc(sizeof(Password) * sizeArray);
		arrayBoolean = (bool *)malloc(sizeof(bool) * sizeArray);
		for (int i = 0; i <= sizeArray; i++)
		{
			uint16_t longitud;
			printf("ingresa la longitud de la passwords %d a generar: ", i);
			scanf("%hd", &longitud);
			puts("");
			Password Password(longitud);
			array[i] = Password;
			arrayBoolean[i] = Password.esFuerte();
			complex1 datos = array[i].getLongitudAndPassword();
			printf("Password numero %d generada: %s fuerza de la password: %d\n", i, datos.password, arrayBoolean[i]);
		}
	}
};

int main()
{

	Ejecutable Ejecutable;
	Ejecutable.exec();

	//printf("longitud %d %d, password: %s\n", result.longitud, Password.esFuerte(), result.password);
	return 0;
}

#endif
