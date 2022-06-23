/*
 * Controller.c
 *
 *  Created on: Jun 16, 2022
 *      Author: DellG5
 */
#include <stdlib.h>
#include <stdio.h>
#include "LinkedListP.h"
#include "Parser.h"
#include "Service.h"
#include "BiblioPersonal.h"
#include "Controller.h"
int controller_loadArchive(LinkedList* pArrayListService)
{
	FILE* pFile;
	int ret;
	char path[20];
	ret=-1;
	if(pArrayListService!=NULL)
	{
		printf("Ingrese el nombre del archivo a abrir: ");
		fflush(stdin);
		gets(path);
		pFile = fopen(path,"r");
		if(pFile != NULL)
		{
			if(parser_ServiceFromText(pFile, pArrayListService)==0)
			{
				ret=0;
				system("cls");
				printf("Archivo %s cargado con exito.\n",path);
				system("pause");
			}
		}
	}
	fclose(pFile);
	return ret;
}

int controller_listService(LinkedList* pArrayListService)
{
	eService* auxService;
	int ret;
	int auxId;
	char auxDescription[20];
	char typeServiceStr[10];
	float priceUnit;
	int amount;
	float fullService;
	int i;
	ret=-1;
	if(pArrayListService!=NULL)
	{
		printf("|ID|   | DESCRIPCION |     | TIPO SERVICIO |      | PRECIO U. |   | CANTIDAD |  | TOTAL SERVICIO |\n");
		for(i=0;i<ll_len(pArrayListService);i++)
		{
			auxService= Service_new();
			auxService = ll_get(pArrayListService,i);
			if(!Service_getId(auxService, &auxId)
					&&!Service_getDescription(auxService, auxDescription)
					&&!Service_getTypeStr(auxService,typeServiceStr)
					&&!Service_getPriceUnit(auxService, &priceUnit)
					&&!Service_getAmount(auxService, &amount)
					&&!Service_getFullService(auxService, &fullService))
			{
				printf(" %-3d    %-17s      %-10s            %-6.2f            %-3d           %-6.2f\n", auxId, auxDescription, typeServiceStr, priceUnit, amount, fullService);
			}

		}
		ret=0;
	}
	return ret;
}

int controller_toAssignTotal(LinkedList* pArrayListService)
{
	int ret;
	ret=-1;
	if(pArrayListService!=NULL)
	{
		ll_map(pArrayListService, Service_calculateFullService);
		ret=0;
		system("cls");
		printf("Servicio total asignado con exito.\n");
		system("pause");

	}
	return ret;
}

int controller_filterForType(LinkedList* pArrayListService)
{
	LinkedList* filterList;
	filterList=ll_newLinkedList();
	int ret;
	int option;
	ret=-1;
	if(pArrayListService!=NULL && filterList!=NULL)
	{
		if(!getMenuForInt(&option, "FILTRAR POR:\n1)MINORISTA \n2)MAYORISTA \n3)EXPORTAR", 3, 1))
		{
			switch(option)
			{
				case 1:
					filterList = ll_filter(pArrayListService, Service_filterForTypeMinorista);
					if(filterList!=NULL)
					{
						if(!controller_saveAsText("dataMinorista.csv", filterList))
						{
							ret=0;
							system("cls");
							printf("dataMinorista.csv creado con exito.\n");
							system("pause");
						}
						else
						{
							system("cls");
							printf("Error no se pudo crear el archivo minorista.\n");
							system("pause");
						}
					}
					break;
				case 2:
					filterList = ll_filter(pArrayListService, Service_filterForTypeMayorista);
					if(filterList!=NULL)
					{
						if(!controller_saveAsText("dataMayorista.csv", filterList))
						{
							ret=0;
							system("cls");
							printf("dataMayorista.csv creado con exito.\n");
							system("pause");
						}
						else
						{
							system("cls");
							printf("Error no se pudo crear el archivo mayorista.\n");
							system("pause");
						}
					}
					break;
				case 3:
					filterList = ll_filter(pArrayListService, Service_filterForTypeExportar);
					if(filterList!=NULL)
					{
						if(!controller_saveAsText("dataExportar.csv", filterList))
						{
							ret=0;
							system("cls");
							printf("dataExportar.csv creado con exito.\n");
							system("pause");
						}
						else
						{
							system("cls");
							printf("Error no se pudo crear el archivo exportar.\n");
							system("pause");
						}
					}
					break;
				default:
					break;

			}
		}
	}
	if(ll_deleteLinkedList(filterList)<0)
	{
		ret=-1;
	}
	return ret;
}

int controller_saveAsText(char* path , LinkedList* pArrayListService)
{
	FILE* pFile;
	eService* auxService;
	auxService=Service_new();
	int ret;
	int i;
	int auxId;
	char auxDescription[30];
	int auxType;
	float auxPriceUnit;
	int auxAmount;
	float auxFullService;
	ret=-1;
	if(path!=NULL && pArrayListService!=NULL)
	{
		pFile = fopen(path,"w");
		if(pFile!=NULL)
		{
			fprintf(pFile,"id_servicio,descripcion,tipo,precioUnitario,cantidad,totalServicio\n");
			for(i=0;i<ll_len(pArrayListService);i++)
			{
				auxService=ll_get(pArrayListService,i);
				if(auxService!=NULL)
				{
					if(!Service_getId(auxService, &auxId)
							&&!Service_getDescription(auxService, auxDescription)
							&&!Service_getType(auxService,&auxType)
							&&!Service_getPriceUnit(auxService, &auxPriceUnit)
							&&!Service_getAmount(auxService, &auxAmount)
							&&!Service_getFullService(auxService, &auxFullService))
					{
						fprintf(pFile,"%d,%s,%d,%.2f,%d,%.2f\n",auxId,auxDescription,auxType,auxPriceUnit,auxAmount,auxFullService);
					}
				}
			}
			ret=0;
		}
		fclose(pFile);
	}
    return ret;
}

int controller_showAService(LinkedList* pArrayListService, LinkedList* pListServiceMinorista, LinkedList* pListServiceMayorista , LinkedList* pListServiceExportar)
{
	int ret;
	int type;
	LinkedList* auxListService;
	auxListService=ll_newLinkedList();
	auxListService=ll_clone(pArrayListService);
	eService* auxService;
	auxService=Service_new();
	ret=-1;
	if(pArrayListService!=NULL && auxListService!=NULL)
	{
		if(!ll_sort(auxListService, Service_sortForDescription,1))
		{
			if(ll_len(pListServiceMinorista)<1 && ll_len(pListServiceMayorista)<1 && ll_len(pListServiceExportar)<1)
			{
				for(int i=0;i<ll_len(auxListService);i++)
				{
					auxService = ll_get(auxListService,i);
					if(!Service_getType(auxService, &type))
					{
						if(type==1 )
						{
							ll_add(pListServiceMinorista,auxService);
						}
						else if(type==2 )
						{
							ll_add(pListServiceMayorista,auxService);
						}
						else if(type==3 )
						{
							ll_add(pListServiceExportar,auxService);
						}
					}
				}
			}
			printf("LISTA MINORISTA\n");
			if(!controller_listService(pListServiceMinorista))
			{
				printf("LISTA MAYORISTA\n");
				if(!controller_listService(pListServiceMayorista))
				{
					printf("LISTA EXPORTAR\n");
					if(!controller_listService(pListServiceExportar))
					{
						ret=0;
					}
				}
			}

		}

	}
	free(auxListService);
	return ret;
}

int controller_saveListTypeServiceAsText(LinkedList* pListServiceMinorista, LinkedList* pListServiceMayorista , LinkedList* pListServiceExportar)
{
	int ret;
	FILE* pFile;
	ret=-1;
	if(pListServiceMinorista!=NULL && pListServiceMayorista!=NULL && pListServiceExportar!=NULL)
	{
		pFile = fopen("dataListForTypeService.txt","w");
		if(pFile!=NULL)
		{
			fprintf(pFile,"SERVICIO MINORISTA\n");
			if(!controller_saveListServiceAsText(pListServiceMinorista, pFile))
			{
				fprintf(pFile,"SERVICIO MAYORISTA\n");
				if(!controller_saveListServiceAsText(pListServiceMayorista, pFile))
				{
					fprintf(pFile,"SERVICIO EXPORTAR\n");
					if(!controller_saveListServiceAsText(pListServiceExportar, pFile))
					{
						ret=0;
					}
				}
			}
		}
		fclose(pFile);
	}
	return ret;
}

int controller_saveListServiceAsText(LinkedList* pArrayService, FILE* pFile)
{
	eService* auxService;
	auxService=Service_new();
	int ret;
	int i;
	int auxId;
	char auxDescription[30];
	int auxType;
	float auxPriceUnit;
	int auxAmount;
	float auxFullService;
	ret=-1;
	if(pArrayService!=NULL && pFile!=NULL&& auxService!=NULL)
	{
		fprintf(pFile,"|ID|   | DESCRIPCION |     | TIPO SERVICIO |      | PRECIO U. |   | CANTIDAD |  | TOTAL SERVICIO |\n");
		for(i=0;i<ll_len(pArrayService);i++)
		{
			auxService=ll_get(pArrayService,i);
			if(auxService!=NULL)
			{
				if(!Service_getId(auxService, &auxId)
						&&!Service_getDescription(auxService, auxDescription)
						&&!Service_getType(auxService,&auxType)
						&&!Service_getPriceUnit(auxService, &auxPriceUnit)
						&&!Service_getAmount(auxService, &auxAmount)
						&&!Service_getFullService(auxService, &auxFullService))
				{
					fprintf(pFile," %-3d    %-17s      %-10d            %-6.2f            %-3d           %-6.2f\n",auxId,auxDescription,auxType,auxPriceUnit,auxAmount,auxFullService);
				}
			}
		}
		free(auxService);
		ret=0;
	}
	return ret;
}

int controller_thereAreServices(LinkedList* pArrayListService)
{
	int ret;
	ret=0;
	if(pArrayListService!=NULL)
	{
		if(ll_len(pArrayListService)>0)
		{
			ret=1;
		}
	}
	return ret;
}

int controller_deleteLists(LinkedList* pListService, LinkedList* pListServiceMinorista, LinkedList* pListServiceMayorista, LinkedList* pListServiceExportar)
{
	int ret;
	ret=0;
	if(pListService!=NULL && pListServiceMinorista!=NULL && pListServiceMayorista!=NULL && pListServiceExportar!=NULL)
	{
		if(controller_thereAreServices(pListService) && ll_deleteLinkedList(pListService)<0)
		{
			ret=-1;
		}
		if(controller_thereAreServices(pListServiceMinorista) && ll_deleteLinkedList(pListServiceMinorista)<0)
		{
			ret=-1;
		}
		if(controller_thereAreServices(pListServiceMayorista) && ll_deleteLinkedList(pListServiceMayorista)<0)
		{
			ret=-1;
		}
		if(controller_thereAreServices(pListServiceExportar) && ll_deleteLinkedList(pListServiceExportar)<0)
		{
			ret=-1;
		}
	}
	return ret;
}
