#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

/**
* \brief El usuario ingresa una cadena con fgets
* \param pBuffer Recibe el texto ingresado en caso de exito
* \param limite Es el tamano maximo del string
* \return En caso de exito retorna 0, si no -1
*
*/
static int getString(char *pBuffer, int limite)
{
    int retorno = -1;
    int len;
    char bufferString[4096];
    if(pBuffer != NULL && limite > 0 )
    {
        fflush(stdin);
        fgets(bufferString, 4096, stdin);
        len = strlen(bufferString);
        if(len <= limite)
        {
            if(len != limite-1 || bufferString[limite-2] == '\n')
            {
                bufferString[len-1] = '\0';
            }
            strncpy(pBuffer, bufferString, limite);
            retorno = 0;
        }
        else
        {
            printf("Se admite un maximo de %d caracteres\n", limite - 1);
        }
    }
    return retorno;
}
/**
* \brief Evalua si se trata de un archivo
* \param pBuffer Es la cadena que evaluamos
* \param limite Es el tamano maximo del string
* \return En caso de exito retorna 1, si no 0
*
*/
static int isValidArchivo(char *pBuffer, int limite)
{
    int retorno = 0;
    int flagPuntoEncontrado = 0;
    int i;
    if(pBuffer != NULL && limite > 0 && strlen(pBuffer) > 0)
    {
        for(i=0; i < limite && pBuffer[i] != '\0'; i++)
        {
            if(pBuffer[i] == '.' && i != 0)
            {
                retorno = 1;
                flagPuntoEncontrado = 1;
            }
            else if((flagPuntoEncontrado == 0 &&
                     !(  (pBuffer[i] == ' ' || pBuffer[i] == '#' ||
                          pBuffer[i] == '(' || pBuffer[i] == ')' ||
                          pBuffer[i] == ';' || pBuffer[i] == '=' ||
                          pBuffer[i] == '@' || pBuffer[i] == '[')||
                         (pBuffer[i] >= '+' && pBuffer[i] <= '-') ||
                         (pBuffer[i] >= '0' && pBuffer[i] <= '9') ||
                         (pBuffer[i] >= 'A' && pBuffer[i] <= 'Z') ||
                         (pBuffer[i] >= ']' && pBuffer[i] <= 'z'))) ||
                    (flagPuntoEncontrado == 1 &&
                     !(  (pBuffer[i] >= 'A' && pBuffer[i] <= 'Z') ||
                         (pBuffer[i] >= 'a' && pBuffer[i] <= 'z'))))
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/**
* \brief Toma una cadena y evalua si es un archivo
* \param pArchivo Recibe el texto ingresado en caso de exito
* \param limite Es el tamano maximo del string
* \param mensaje Es el mensaje que se muestra al usuario antes de introducir datos
* \param mensajeError Es el mensaje que se muestra en caso de error
* \param reintentos Veces que el usuario podra volver a introducir el dato
* \return En caso de exito retorna 0, si no -1
*
*/
int utn_getArchivo( char *pArchivo, int limite, char *mensaje, char *mensajeError, int reintentos)
{
    int retorno=-1;
    char buffer[4096];
    if( pArchivo != NULL && limite > 0 && mensaje != NULL &&
        mensajeError != NULL && reintentos>=0)
    {
        do
        {
            reintentos--;
            printf("\n%s", mensaje);
            if( getString(buffer, limite) == 0 &&
                isValidArchivo(buffer, limite))
            {
                strncpy(pArchivo, buffer, limite);
                retorno = 0;
                break;
            }
            else
            {
                printf("\n%s", mensajeError);
            }
        }
        while(reintentos>=0);
    }
    return retorno;
}

/**
 * \brief 	Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
 * 			un máximo de 'longitud - 1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamaño de cadena
 * \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
 *
 */
int myGets(char* cadena, int longitud)
{
	int retorno=-1;
	char bufferString[4096]; // *****************************

	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)
		{
			if(bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n')
			{
				bufferString[strnlen(bufferString,sizeof(bufferString))-1] = '\0';
			}
			if(strnlen(bufferString,sizeof(bufferString)) <= longitud)
			{
				strncpy(cadena,bufferString,longitud);
				retorno=0;
			}
		}
	}
	return retorno;
}

/**
 * \brief Verifica si una cadena de caracteres puede o no ser convertia a numero entero
 * \param cadena Es la cadena a ser analizada
 * \return Verdadero si la cadena contiene un valor numerico entero, Falso si no
 *
 */
int esNumero(char* cadena)
{
	int retorno = 1;
	int i;
	for(i=0;cadena[i]!='\0';i++)
	{
		if(i==0 && cadena[i] == '-')
		{
			continue;
		}
		if(cadena[i]>'9' || cadena[i]<'0')
		{
			retorno = 0;
			break;
		}
		//continue
	}
	// break
	return retorno;
}

/**
 * \brief Solicita un numero al usuario, lo valida, verifica y devuelve el resultado
 * \param pResultado Puntero al resultado alli se dejara el numero ingresado por el usuario
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje a ser mostrado en caso de error
 * \param minimo Valor minimo aceptado
 * \param maximo Valor maximo aceptado
 * \param reintentos Cantidad de reintentos en el caso de error
 * \return En caso de exito (0), en caso de error (-1)
 *
 */
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;
	char bufferChar[4096];
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			scanf("%s",bufferChar);
			if(esNumero(bufferChar))
			{
				bufferInt = atoi(bufferChar);

				if(bufferInt >= minimo && bufferInt <= maximo)
				{
					*pResultado = bufferInt;
					retorno = 0;
					break;
				}
			}
			printf("%s",mensajeError);
			reintentos--;
		}while(reintentos >= 0);
	}
	return retorno;
}



/**
 * \brief Solicita un caracter al usuario, lo valida, verifica y devuelve el resultado
 * \param pResultado Puntero al resultado alli se dejara el caracter ingresado por el usuario
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje a ser mostrado en caso de error
 * \param minimo Valor minimo aceptado
 * \param maximo Valor maximo aceptado
 * \param reintentos Cantidad de reintentos en el caso de error
 * \return En caso de exito (0), en caso de error (-1)
 *
 */
int utn_getCaracter(char* pResultado, char* mensaje,char* mensajeError, char minimo,char maximo,int reintentos)
{
	int retorno = -1;
	char buffer;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			scanf("%c",&buffer);
			if(buffer >= minimo && buffer <= maximo)
			{
				*pResultado = buffer;
				retorno = 0;
				break;
			}
			printf("%s",mensajeError);
			reintentos--;
		}while(reintentos>=0);

	}
	return retorno;
}




