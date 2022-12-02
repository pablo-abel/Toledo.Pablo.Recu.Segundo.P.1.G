#include "LinkedList.h"
#ifndef POST_H_INCLUDED
#define POST_H_INCLUDED

typedef struct
{
    int id;
    char user[20];
    int likes;
    int dislikes;
    int followers;

}ePost;

ePost* new_Posteo();

ePost* new_PosteoParam(char* idStr, char* user, char* dislikesStr, char* likesStr, char* followersStr);

int postSetId(ePost* pPosteo, int id);
int postGetId(ePost* pPosteo, int* pId);

int postSetUser(ePost* pPosteo, char* user);
int postGetUser(ePost* pPosteo, char* pUser);

int postSetDislikes(ePost* pPosteo, int dislike);
int postGetDislikes(ePost* pPosteo, int* pDislike);

int postSetLikes(ePost* pPosteo, int like);
int postGetLikes(ePost* pPosteo, int* pLike);

int postSetFollowers(ePost* pPosteo, int follower);
int postGetFollowers(ePost* pPosteo, int* pFollower);

#endif // POST_H_INCLUDED

int mostrarPosteo(ePost* pelicula);
void mostrarPosteos(LinkedList* lista);

int confirmarSalida(char *pControl);
int confirmarReemplazo(char *pControl);

void* valorLikes(void* like);
void* valorDislikes(void* dislike);
void* valorFollowers(void* follower);

int heaters(void* dislikes);
int mejoresPost(void* likes);

int post_CmCanFollowers(void* a, void* b);
