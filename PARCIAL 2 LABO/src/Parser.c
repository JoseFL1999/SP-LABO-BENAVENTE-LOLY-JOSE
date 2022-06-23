/*
 * Parser.c
 *
 *  Created on: Jun 16, 2022
 *      Author: DellG5
 */
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include "Service.h"
int parser_ServiceFromText(FILE* pFile , LinkedList* pArrayListService)
{
	eService* auxService;
	int ret;
	int r;
	char id[5];
	char description[20];
	char type[2];
	char priceUnit[15];
	char amount[5];
	char fullService[16];
	ret=-1;
	r=0;
	if(pFile!=NULL && pArrayListService!=NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",id,description,type,priceUnit,amount,fullService);
		while(!feof(pFile))
		{
			r=fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",id,description,type,priceUnit,amount,fullService);
			if(r<6)
			{
				break;
			}
			auxService = Service_newParam(id,description,type,priceUnit,amount,fullService);
			if(auxService!=NULL /*&& findId(pArrayListService,atoi(id))==-1*/)
			{
				if(ll_add(pArrayListService, auxService)==0)
				{
					ret=0;
				}
			}
		}
	}
    return ret;
}
