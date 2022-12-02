#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include <time.h>
#include "post.h"
#include "parser.h"
#include "controller.h"
#include "utn.h"

int main()
{
    srand(time(NULL));
    int opcion = 0;
    char archivoCarga[20];
	int respuesta;
	char confirmar;
    char archivoGuardar[20];
	char confirmarSobrescribir;


    LinkedList* listaPosts = ll_newLinkedList();
    LinkedList* listaFiltrada;

    do
    {
         system("cls");
        respuesta = utn_getNumero(&opcion, "      Peliculas    \n---------------------\n1 - Carga de archivos\n"
                                           "2 - Imprimir lista\n3 - Asignar estadistica\n4 - filtrar por mejores posts \n"
                                           "5 - filtrar por haters\n6 - Ordenar por nivel de cantidad de followers\n"
                                           "7 - mostrar mas populares\n8 - SALIR \n"
                                           "Ingrese opcion:\n", "No es una opcion valida\n", 1, 9, 4);

        if(!respuesta)
        {
            switch(opcion)
            {
              case 1:
                  utn_getArchivo(archivoCarga, 20, "Ingrese nombre del archivo(.csv):\n", "no es un archivo\n", 4);
                  if(controller_cargarPostDesdeTexto(archivoCarga,listaPosts))
                  {
                      printf("carga de archivos exitosa!\n");
                  }
                  else
                  {
                     printf("No se pudo cargar el archivo de jugadores\n");
                  }
              break;
              case 2:
                  mostrarPosteos(listaPosts);
              break;
              case 3:
                  ll_map(listaPosts, valorLikes);
                  ll_map(listaPosts, valorDislikes);
                  ll_map(listaPosts, valorFollowers);
                  mostrarPosteos(listaPosts);
              break;
              case 4:
                  listaFiltrada = ll_filter(listaPosts, mejoresPost);
            	  mostrarPosteos(listaFiltrada);
            	  do{
                        utn_getArchivo(archivoGuardar, 20, "Ingrese nombre del nuevo archivo(.csv) con la nueva lista:\n", "no es un archivo\n", 4);
                        confirmarSobrescribir = 's';
                        if(!strcmp(archivoCarga, archivoGuardar))
                        {
                            printf("El nombre del archivo ya existe!\n");
                            confirmarReemplazo(&confirmarSobrescribir);
                        }
                         printf("confirmar! %c\n", confirmarSobrescribir);
                  }while(confirmarSobrescribir != 's');

                  if(controller_guardarPostModoTexto(archivoGuardar, listaFiltrada))
                  {
                      printf("guardado del archivos exitosa!\n");
                  }
                  else
                  {
                     printf("No se pudo guardar el archivo de peliculas\n");
                  }
              break;
              case 5:
                  listaFiltrada = ll_filter(listaPosts, heaters);
            	  mostrarPosteos(listaFiltrada);
            	  listaFiltrada = ll_filter(listaPosts, mejoresPost);
            	  mostrarPosteos(listaFiltrada);
            	  do{
                        utn_getArchivo(archivoGuardar, 20, "Ingrese nombre del nuevo archivo(.csv) con la nueva lista:\n", "no es un archivo\n", 4);
                        confirmarSobrescribir = 's';
                        if(!strcmp(archivoCarga, archivoGuardar))
                        {
                            printf("El nombre del archivo ya existe!\n");
                            confirmarReemplazo(&confirmarSobrescribir);
                        }
                         printf("confirmar! %c\n", confirmarSobrescribir);
                  }while(confirmarSobrescribir != 's');

                  if(controller_guardarPostModoTexto(archivoGuardar, listaFiltrada))
                  {
                      printf("guardado del archivos exitosa!\n");
                  }
                  else
                  {
                     printf("No se pudo guardar el archivo de peliculas\n");
                  }
              break;
              case 6:
                  controller_ordenarPost(listaPosts);
              break;
              case 7:
                  printf("7");
              break;
              case 8:
                  if(!confirmarSalida(&confirmar))
                  {
                      opcion = 0;
                  }
              break;

            }
        }
     system("pause");
    }while(opcion != 8);

    return 0;
}
