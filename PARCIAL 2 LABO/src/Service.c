/*
 * Services.c
 *
 *  Created on: 16 jun 2022
 *      Author: --
 */

#include "Service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BiblioPersonal.h"
eService* Service_new()
{
	eService* newService;
	newService=NULL;
	newService= (eService*) malloc(sizeof(eService));
	if(newService!=NULL)
	{
		newService->id=0;
		strcpy(newService->description," ");
		newService->type=0;
		newService->priceUnit=0;
		newService->amount=0;
		newService->fullService=0;
	}
	return newService;
}

eService* Service_newParam(char* idStr, char* descriptionStr, char* typeStr, char* priceUnitStr, char* amountStr, char* fullServiceStr)
{
	eService* newService;
	newService=Service_new();
	if(newService!=NULL && idStr!=NULL && descriptionStr!=NULL && typeStr!=NULL && priceUnitStr!=NULL && amountStr!=NULL && fullServiceStr!=NULL)
	{
		if(Service_setId(newService, atoi(idStr))!=0
				||Service_setDescription(newService,descriptionStr)!=0
				||Service_setType(newService,atoi(typeStr))!=0
				||Service_setPriceUnit(newService,atof(priceUnitStr))!=0
				||Service_setAmount(newService,atoi(amountStr))!=0
				||Service_setFullService(newService,atof(fullServiceStr))!=0)
		{
			free(newService);
			newService=NULL;
		}
	}
	return newService;
}

int Service_setId(eService* this, int id)
{
	int ret;
	ret=-1;
	if(this!=NULL && id>0)
	{
		this->id=id;
		ret=0;
	}
	return ret;
}

int Service_getId(eService* this, int* id)
{
	int ret;
	ret=-1;
	if(this!=NULL && id!=NULL)
	{
		*id=this->id;
		ret=0;
	}
	return ret;
}

int Service_setDescription(eService* this, char* description)
{
	int ret;
	ret=-1;
	if(this!=NULL && description!=NULL && strlen(description)>1 && isText(description)==1)
	{
		strcpy(this->description,description);
		ret=0;
	}
	return ret;
}

int Service_getDescription(eService* this, char* description)
{
	int ret;
	ret=-1;
	if(this!=NULL && description!=NULL)
	{
		strcpy(description,this->description);
		ret=0;
	}
	return ret;
}

int Service_setType(eService* this, int type)
{
	int ret;
	ret=-1;
	if(this!=NULL && type>0 && type<4)
	{
		this->type=type;
		ret=0;
	}
	return ret;
}

int Service_getType(eService* this, int* type)
{
	int ret;
	ret=-1;
	if(this!=NULL && type!=NULL)
	{
		*type=this->type;
		ret=0;
	}
	return ret;
}

int Service_getTypeStr(eService* thisA, char* typeStr)
{
	int ret;
	ret=-1;
	if(thisA!=NULL && typeStr!=NULL)
	{
		switch(thisA->type)
		{
			case 1:
				strcpy(typeStr,"MINORISTA");
				ret=0;
				break;
			case 2:
				strcpy(typeStr,"MAYORISTA");
				ret=0;
				break;
			case 3:
				strcpy(typeStr,"EXPORTAR");
				ret=0;
				break;
			default:
				ret=0;
				break;
		}
	}
	return ret;
}

/*int Service_typeService(typeService* thisB, int typeId, char* description)
{
	int ret;
	int i;
	if(thisB!=NULL && description!=NULL)
	{
		for(i=0;i<ll_len(thisB);i++)
		{
			if((thisB+i)->idType==typeId)
			{
				strcpy(description,(thisB+i)->description);
				ret=0;
				break;

			}
		}
	}
	return ret;
}*/


int Service_setPriceUnit(eService* this, float priceUnit)
{
	int ret;
	ret=-1;
	if(this!=NULL && priceUnit>0 )
	{
		this->priceUnit=priceUnit;
		ret=0;
	}
	return ret;
}

int Service_getPriceUnit(eService* this, float* priceUnit)
{
	int ret;
	ret=-1;
	if(this!=NULL && priceUnit!=NULL)
	{
		*priceUnit=this->priceUnit;
		ret=0;
	}
	return ret;
}

int Service_setAmount(eService* this, int amount)
{
	int ret;
	ret=-1;
	if(this!=NULL && amount>-1)
	{
		this->amount=amount;
		ret=0;
	}
	return ret;
}

int Service_getAmount(eService* this, int* amount)
{
	int ret;
	ret=-1;
	if(this!=NULL && amount!=NULL)
	{
		*amount=this->amount;
		ret=0;
	}
	return ret;
}

int Service_setFullService(eService* this, float fullService)
{
	int ret;
	ret=-1;
	if(this!=NULL && fullService>-1)
	{
		this->fullService=fullService;
		ret=0;
	}
	return ret;
}

int Service_getFullService(eService* this, float* fullService)
{
	int ret;
	ret=-1;
	if(this!=NULL && fullService!=NULL)
	{
		*fullService=this->fullService;
		ret=0;
	}
	return ret;
}

void Service_calculateFullService(void* pElement)
{
	((eService*)pElement)->fullService = ((eService*)pElement)->priceUnit * ((eService*)pElement)->amount;
}

int Service_filterForTypeMinorista(void* pElement)
{
	int ret;
	ret=-1;
	if(pElement!=NULL)
	{
		ret=0;
		if(((eService*)pElement)->type==1)
		{
			ret=1;
		}
	}
	return ret;
}

int Service_filterForTypeMayorista(void* pElement)
{
	int ret;
	ret=-1;
	if(pElement!=NULL)
	{
		ret=0;
		if(((eService*)pElement)->type==2)
		{
			ret=1;
		}
	}
	return ret;
}
int Service_filterForTypeExportar(void* pElement)
{
	int ret;
	ret=-1;
	if(pElement!=NULL)
	{
		ret=0;
		if(((eService*)pElement)->type==3)
		{
			ret=1;
		}
	}
	return ret;
}

int Service_sortForType(void* itemA, void* itemB)
{
	eService* auxServiceA;
	eService* auxServiceB;
	int typeServiceA;
	int typeServiceB;
	int ret;
	ret=0;
	if(itemA!=NULL && itemB!=NULL)
	{
		auxServiceA = (eService*)itemA;
		auxServiceB = (eService*)itemB;
		if(!Service_getType(auxServiceA, &typeServiceA)
				&&!Service_getType(auxServiceB, &typeServiceB))
		{
			if(typeServiceA>typeServiceB)
			{
				ret=1;
			}
			else if(typeServiceA<typeServiceB)
			{
				ret=-1;
			}
		}
	}
	return ret;
}

int Service_sortForDescription(void* itemA, void* itemB)
{
	eService* auxServiceA;
	eService* auxServiceB;
	char descriptionA[30];
	char descriptionB[30];
	int ret;
	ret=0;
	if(itemA!=NULL && itemB!=NULL)
	{
		auxServiceA = (eService*)itemA;
		auxServiceB = (eService*)itemB;
		if(!Service_getDescription(auxServiceA, descriptionA)
				&&!Service_getDescription(auxServiceB, descriptionB))
		{
			if(strcmp(descriptionA,descriptionB)>0)
			{
				ret=1;
			}
			else if(strcmp(descriptionA,descriptionB)<0)
			{
				ret=-1;
			}
		}
	}
	return ret;
}
