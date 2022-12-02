#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LinkedList.h"
#include "post.h"

int mostrarPosteo(ePost* posteo)
{
    int todoOk = 0;
    int id;
    char user[20];
    int likes;
    int dislikes;
    int followers;

    if(posteo != NULL)
    {
        if(postGetId(posteo, &id) &&
           postGetUser(posteo, user) &&
           postGetLikes(posteo, &likes) &&
           postGetDislikes(posteo, &dislikes) &&
           postGetFollowers(posteo, &followers))
        {
            printf(" %3d   %-15s     %-4d      %-4d         %-5d\n", id, user, likes, dislikes, followers);
            todoOk = 1;
        }

    }
    return todoOk;
}

void mostrarPosteos(LinkedList* lista)
{
    printf("-------------------------------------------------------------\n");
    printf(" Id      Users           Likes      Dislikes      Followers\n");
    printf("-------------------------------------------------------------\n");
    for(int i = 0; i < ll_len(lista); i ++)
    {
        mostrarPosteo((ePost*) ll_get(lista, i));
    }
    if(ll_isEmpty(lista))
    {
        printf("\n                 Lista vacia!                   \n");
    }
    printf("\n-------------------------------------------------------\n");
    printf("\n\n");
}

int confirmarSalida(char *pControl)
{
    int todoOk = 0;
    char confirma;
    if(pControl != NULL)
    {
        printf("confirmar salida s/n:");
        fflush(stdin);
        confirma = tolower(getchar());
        if(confirma == 's')
        {
            *pControl = 's';
            todoOk = 1;
        }
    }
    return todoOk;
}
int confirmarReemplazo(char *pControl)
{
    int todoOk = -1;
    char confirma;
    if(pControl != NULL)
    {
        printf("Quiere reemplazarlo? s/n:");
        fflush(stdin);
        confirma = tolower(getchar());
        if(confirma == 's')
        {
            *pControl = 's';
            todoOk = 1;
        }
        else
        {
            *pControl = 'n';
            todoOk = 0;
        }
    }
    return todoOk;
}

void* valorLikes(void* like)
{
    ePost* unPosteo = NULL;
    if(like != NULL)
    {
        unPosteo = (ePost*) like;
        if(unPosteo->likes == 0)
        {
            unPosteo->likes = rand() % 4401 + 600;
        }
    }
    return 0;
}
void* valorDislikes(void* dislike)
{
    ePost* unPosteo = NULL;
    if(dislike != NULL)
    {
        unPosteo = (ePost*) dislike;
        if(unPosteo->dislikes == 0)
        {
            unPosteo->dislikes = rand() % 3201 + 300;
        }
    }
    return 0;
}
void* valorFollowers(void* follower)
{
    ePost* unPosteo = NULL;
    if(follower != NULL)
    {
        unPosteo = (ePost*) follower;
        if(unPosteo->followers == 0)
        {
            unPosteo->followers = rand() % 10001 + 10000;
        }
    }
    return 0;
}


int heaters(void* dislikes)
{
    int ok = 0;
    ePost* unPosteo = NULL;
    if(dislikes != NULL)
    {
        unPosteo = (ePost*) dislikes;
        if(unPosteo->dislikes > unPosteo->likes)
        {
            ok = 1;
        }
    }
    return ok;
}

int mejoresPost(void* likes)
{
    int ok = 0;
    ePost* unPosteo = NULL;
    if(likes != NULL)
    {
        unPosteo = (ePost*) likes;
        if(unPosteo->likes > 4000)
        {
            ok = 1;
        }
    }
   // printf("%d\n", ok);// me fijo si esta todo ok con el rotorno de la fincion
    return ok;
}

int post_CmCanFollowers(void* a, void* b)
{
     int retorno = 0;
     ePost* post1 = NULL;
     ePost* post2 = NULL;
     if(a != NULL && b != NULL)
     {
         post1 = (ePost*) a;
         post2 = (ePost*) b;
         if(post1 ->followers > post2 ->followers)
         {
             retorno = 1;
         }
         else  if(post1 ->followers < post2 ->followers)
         {
             retorno = -1;
         }
     }
     return retorno;
}

ePost* new_Posteo()
{
    ePost* auxP = NULL;
    auxP = (ePost*) malloc(sizeof(ePost));
    return auxP;
}

ePost* new_PosteoParam(char* idStr, char* user, char* dislikesStr, char* likesStr, char* followersStr)
{
    ePost* nuevoPost;
    nuevoPost = new_Posteo();
    if(nuevoPost != NULL)
    {
        if(!(postSetId(nuevoPost, atoi(idStr)) &&
             postSetUser(nuevoPost, user) &&
             postSetDislikes(nuevoPost,atoi(dislikesStr)) &&
             postSetLikes(nuevoPost,atoi(likesStr)) &&
             postSetFollowers(nuevoPost, atoi(followersStr))))
        {
            free(nuevoPost);
            nuevoPost = NULL;
        }
    }
    return nuevoPost;
}
int postSetId(ePost* pPosteo, int id)
{
    int todoOk = 0;
    if(pPosteo != NULL)
    {
        pPosteo->id = id;
        todoOk = 1;
    }
    return todoOk;
}
int postGetId(ePost* pPosteo, int* pId)
{
    int todoOk = 0;
    if(pPosteo != NULL && pId != NULL)
    {
        *pId = pPosteo->id;
        todoOk = 1;
    }
    return todoOk;
}
int postSetUser(ePost* pPosteo, char* user)
{
    int todoOk = 0;
    char auxCadena[20];
    if(pPosteo != NULL && user != NULL && strlen(user) < 20 && strlen(user) > 2)
    {
        strcpy(auxCadena, user);
        strlwr(auxCadena);
        auxCadena[0] = toupper(auxCadena[0]);
        strcpy(pPosteo->user, auxCadena);
        todoOk = 1;
    }
    return todoOk;
}

int postGetUser(ePost* pPosteo, char* pUser)
{
    int todoOk = 0;

    if(pPosteo!= NULL && pUser != NULL)
    {
        strcpy(pUser, pPosteo->user);
        todoOk = 1;
    }
    return todoOk;
}


int postSetDislikes(ePost* pPosteo, int dislike)
{
    int todoOk = 0;
    if(pPosteo != NULL)
    {
        pPosteo->dislikes = dislike;
        todoOk = 1;
    }
    return todoOk;
}
int postGetDislikes(ePost* pPosteo, int* pDislike)
{
    int todoOk = 0;
    if(pPosteo != NULL && pDislike != NULL)
    {
        *pDislike = pPosteo->dislikes;
        todoOk = 1;
    }
    return todoOk;
}
int postSetLikes(ePost* pPosteo, int like)
{
    int todoOk = 0;
    if(pPosteo != NULL)
    {
        pPosteo->likes = like;
        todoOk = 1;
    }
    return todoOk;
}
int postGetLikes(ePost* pPosteo, int* pLike)
{
    int todoOk = 0;
    if(pPosteo != NULL && pLike != NULL)
    {
        *pLike = pPosteo->likes;
        todoOk = 1;
    }
    return todoOk;
}
int postSetFollowers(ePost* pPosteo, int follower)
{
    int todoOk = 0;
    if(pPosteo != NULL)
    {
        pPosteo->followers = follower;
        todoOk = 1;
    }
    return todoOk;
}
int postGetFollowers(ePost* pPosteo, int* pFollower)
{
    int todoOk = 0;
    if(pPosteo != NULL && pFollower != NULL)
    {
        *pFollower = pPosteo->followers;
        todoOk = 1;
    }
    return todoOk;
}
