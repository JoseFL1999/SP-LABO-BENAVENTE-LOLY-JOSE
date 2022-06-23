/*
 ============================================================================
 Name        : PARCIAL.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListP.h"
#include "BiblioPersonal.h"
#include "Controller.h"
#include "Service.h"
int main(void) {
	setbuf(stdout,NULL);
	LinkedList* listService=ll_newLinkedList();
	LinkedList* listServiceMinorista=ll_newLinkedList();
	LinkedList* listServiceMayorista=ll_newLinkedList();
	LinkedList* listServiceExportar=ll_newLinkedList();
	int option;
	do{
		if(!getMenuForInt(&option,"1)Cargar archivo \n2)Imprimir lista "
				"\n3)Asignar totales \n4)Filtrar por tipo \n5)Mostrar servicios"
				"\n6)Guardar servicios \n7)Salir",7,1))
		{
			switch(option)
			{
				case 1:
					if(controller_loadArchive(listService)!=0)
					{
						printf("ERROR, no se pudo cargar el archivo.\n");
						system("pause");
					}
					break;
				case 2:
					if(controller_thereAreServices(listService))
					{
						if(!controller_listService(listService))
						{
							system("pause");
						}
						else
						{
							system("cls");
							printf("ERROR, no se pudo mostrar la lista.\n");
							system("pause");
						}
					}
					else
					{
						system("cls");
						printf("No hay servicios a mostrar.\n");
						system("pause");
					}
					break;
				case 3:
					if(controller_thereAreServices(listService))
					{
						if(controller_toAssignTotal(listService)!=0)
						{
							system("cls");
							printf("ERROR, no se pudo asignar el total servicio.\n");
							system("pause");
						}
					}
					else
					{
						system("cls");
						printf("No hay servicios para asignar total.\n");
						system("pause");
					}
					break;
				case 4:
					if(controller_thereAreServices(listService))
					{
						if(controller_filterForType(listService)!=0)
						{
							system("cls");
							printf("ERROR, no se pudo filtrar los servicios.\n");
							system("pause");
						}
					}
					else
					{
						system("cls");
						printf("No hay servicios cargados .\n");
						system("pause");
					}
					break;
				case 5:
					if(controller_thereAreServices(listService))
					{
						if(!controller_showAService(listService,listServiceMinorista, listServiceMayorista, listServiceExportar))
						{
							system("pause");
						}
						else
						{
							system("cls");
							printf("ERROR, no se pudo mostrar la lista.\n");
							system("pause");
						}
					}
					else
					{
						system("cls");
						printf("No hay servicios cargados.\n");
						system("pause");
					}
					break;
				case 6:
					if(controller_thereAreServices(listServiceMinorista) && controller_thereAreServices(listServiceMayorista) && controller_thereAreServices(listServiceExportar))
					{
						if(!controller_saveListTypeServiceAsText(listServiceMinorista, listServiceMayorista, listServiceExportar))
						{
							system("cls");
							printf("Lista de tipo de servicio guardada.\n");
							system("pause");
						}
					}
					else
					{
						system("cls");
						printf("No hay tipo de servicios cargados.\n");
						system("pause");
					}
					break;
				case 7:
					if(controller_deleteLists(listService, listServiceMinorista, listServiceMayorista, listServiceExportar)!=0)
					{
						system("cls");
						printf("ERROR DELETE LISTS.\n");
						system("pause");
					}
					break;
			}
		}
	}while(option!=7);
	return 0;
}
