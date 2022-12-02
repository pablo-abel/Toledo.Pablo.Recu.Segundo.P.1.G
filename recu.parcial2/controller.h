#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

int controller_cargarPostDesdeTexto(char* path , LinkedList* pArrayListPosteo);
int controller_cargarPostDesdeBinario(char* path , LinkedList* pArrayListPosteo);
int controller_ordenarPost(LinkedList* pArrayListPosteo);
int controller_guardarPostModoTexto(char* path , LinkedList* pArrayListPosteo);
int controller_guardarPostModoBinario(char* path , LinkedList* pArrayListPosteo);

#endif // CONTROLLER_H_INCLUDED
