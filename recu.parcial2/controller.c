#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "post.h"
#include "LinkedList.h"
#include "parser.h"

/** \brief Carga los datos de los posteos desde el archivo.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPosteo LinkedList*
 * \return int
 *
 */
int controller_cargarPostDesdeTexto(char* path , LinkedList* pArrayListPosteo)
{
    int retorno = -1;
    FILE* pFile;

    if(path != NULL && pArrayListPosteo != NULL)
    {
        retorno = 0;
        pFile = fopen(path, "r");
        if(pFile != NULL)
        {
            parser_PostFromText(pFile, pArrayListPosteo);
            retorno = 1;
        }
        fclose(pFile);

    }

    return retorno;
}

/** \brief Ordenar post
 *
 * \param path char*
 * \param pArrayListPost LinkedList*
 * \return int
 *
 */
int controller_ordenarPost(LinkedList* pArrayListPost)
{
    int todoOk = -1;
    if(pArrayListPost != NULL)
    {
        for(int i = 0; i < ll_len(pArrayListPost); i ++)
        {
             ll_sort(pArrayListPost, post_CmCanFollowers, 0);
        }
        mostrarPosteos(pArrayListPost);
        todoOk = 0;
    }
    return todoOk;
}

/** \brief Guarda los datos de los posteos en el archivo.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPosteo LinkedList*
 * \return int
 *
 */
int controller_guardarPostModoTexto(char* path , LinkedList* pArrayListPosteo)
{
    int retorno = -1;
    int i;
    FILE* pFile;
    ePost* posteo;
    int id;
    char user[20];
    int likes;
    int dislikes;
    int followers;

    if(path != NULL && pArrayListPosteo != NULL)
    {
        pFile = fopen(path, "w");
        if(pFile != NULL)
        {
            fprintf(pFile, "Id,Users,Likes,Dislikes,Followers\n");
            for(i = 0; i < ll_len(pArrayListPosteo); i ++)
            {
                posteo = (ePost*) ll_get(pArrayListPosteo, i);
                if(posteo!= NULL)
                {

                       if(postGetId(posteo, &id) &&
                          postGetUser(posteo, user) &&
                          postGetLikes(posteo, &likes) &&
                          postGetDislikes(posteo, &dislikes) &&
                          postGetFollowers(posteo, &followers))
                       {
                           fprintf(pFile, "%d,%s,%d,%d,%d\n", id, user, likes, dislikes, followers);
                           retorno = 1;
                       }
                       else
                       {
                           posteo = NULL;
                           free(posteo);
                           retorno = 0;
                       }
                }
            }
            fclose(pFile);
        }
    }
    return retorno;
}

/** \brief Guarda los datos de los posteos en el archivo binario.
 *
 * \param path char*
 * \param pArrayListPosteo LinkedList*
 * \return int
 *
 */
int controller_guardarPostModoBinario(char* path , LinkedList* pArrayListPosteo)
{
    int retorno = -1;
    int i;
    FILE* pFile;
    ePost* posteo;

    if(path != NULL && pArrayListPosteo != NULL)
    {
        pFile = fopen(path, "wb");
        if(pFile != NULL)
        {
            retorno = 0;
            for(i = 0; i < ll_len(pArrayListPosteo); i ++)
            {
                posteo = (ePost*) ll_get(pArrayListPosteo, i);
                if(posteo!= NULL)
                {
                    fwrite(posteo, sizeof(ePost), 1, pFile);
                    retorno = 1;
                }
            }
            fclose(pFile);

        }
    }
    return retorno;
}

/** \brief Carga los datos de los posteos desde el archivo generado en modo binario.
 *
 * \param path char*
 * \param pArrayListPosteo LinkedList*
 * \return int
 *
 */
int controller_cargarPostDesdeBinario(char* path , LinkedList* pArrayListPosteo)
{
    int retorno = -1;
    FILE* pFile;

    if(path != NULL && pArrayListPosteo != NULL)
    {
        retorno = 0;
        pFile = fopen(path, "rb");
        if(pFile != NULL)
        {
            parser_PostFromBinary(pFile, pArrayListPosteo);
            retorno = 1;
        }
         fclose(pFile);
    }
    return retorno;
}
