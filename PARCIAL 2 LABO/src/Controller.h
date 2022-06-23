/*
 * Controller.h
 *
 *  Created on: Jun 16, 2022
 *      Author:
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "LinkedListP.h"

int controller_loadArchive(LinkedList* pArrayListService);
int controller_listService(LinkedList* pArrayListService);
int controller_toAssignTotal(LinkedList* pArrayListService);
int controller_filterForType(LinkedList* pArrayListService);
int controller_saveAsText(char* path , LinkedList* pArrayListService);
int controller_showAService(LinkedList* pArrayListService, LinkedList* pListServiceMinorista, LinkedList* pListServiceMayorista , LinkedList* pListServiceExportar);
int controller_saveListTypeServiceAsText(LinkedList* pListServiceMinorista, LinkedList* pListServiceMayorista , LinkedList* pListServiceExportar);
int controller_saveListServiceAsText(LinkedList* pArrayService, FILE* pFile);
int controller_thereAreServices(LinkedList* pArrayListService);
int controller_deleteLists(LinkedList* pListService, LinkedList* pListServiceMinorista, LinkedList* pListServiceMayorista, LinkedList* pListServiceExportar);
#endif /* CONTROLLER_H_ */
