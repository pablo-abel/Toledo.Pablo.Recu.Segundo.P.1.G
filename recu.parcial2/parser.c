#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "post.h"
#include "controller.h"

/** \brief Parsea los datos de los posteos desde el archivo.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPosteo LinkedList*
 * \return int
 */
int parser_PostFromText(FILE* pFile, LinkedList* pArrayListPosteo)
{
    int retorno = -1;
    int cant;
    char buffer[5][100];
    ePost* auxPosteo = NULL;

    if(pFile != NULL)
    {
        cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]", buffer[0], buffer[1],buffer[2], buffer[3], buffer[4]);

        do{
            cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]", buffer[0], buffer[1],buffer[2], buffer[3], buffer[4]);
            if(cant != 5)
            {
                break;
            }
            auxPosteo = new_PosteoParam(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
            if(auxPosteo != NULL)
            {
                ll_add(pArrayListPosteo, auxPosteo);
                auxPosteo = NULL;
            }

        }while(!feof(pFile));
        retorno = 0;
    }
    return retorno;
}

/** \brief Parsea los datos de los posteos desde el archivo binario.
 *
 * \param path char*
 * \param pArrayListPosteo LinkedList*
 * \return int
 *
 */
int parser_PostFromBinary(FILE* pFile , LinkedList* pArrayListPosteo)
{
    int retorno = -1;
    int cant;
    ePost* auxPosteo = NULL;

    if(pFile != NULL)
    {

        do{
            auxPosteo = new_Posteo();
            if(auxPosteo != NULL)
            {
                cant = fread(auxPosteo, sizeof(ePost), 1, pFile);
                if(cant != 1)
                {
                    break;
                }
                ll_add(pArrayListPosteo, auxPosteo);
                auxPosteo = NULL;
            }

        }while(!feof(pFile));
        retorno = 0;
    }
    return retorno;
}
