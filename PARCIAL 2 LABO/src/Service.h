/*
 * Services.h
 *
 *  Created on: 16 jun 2022
 *      Author: --
 */

#ifndef SERVICE_H_
#define SERVICE_H_
typedef struct
{
	int idType;
	char description[10];
}typeService;

typedef struct
{
	int id;
	char description[20];
	int type;
	float priceUnit;
	int amount;
	float fullService;
}eService;

eService* Service_new();
eService* Service_newParam(char* idStr, char* descriptionStr, char* typeStr, char* priceUnitStr, char* amountStr, char* fullServiceStr);

int Service_setId(eService* this, int id);
int Service_getId(eService* this, int* id);

int Service_setDescription(eService* this, char* description);
int Service_getDescription(eService* this, char* description);

int Service_setType(eService* this, int type);
int Service_getType(eService* this, int* type);
int Service_getTypeStr(eService* thisA, char* typeStr);

int Service_setPriceUnit(eService* this, float priceUnit);
int Service_getPriceUnit(eService* this, float* priceUnit);

int Service_setAmount(eService* this, int amount);
int Service_getAmount(eService* this, int* amount);

int Service_setFullService(eService* this, float amount);
int Service_getFullService(eService* this, float* amount);

void Service_calculateFullService(void* pElement);
int Service_filterForTypeMinorista(void* pElement);
int Service_filterForTypeMayorista(void* pElement);
int Service_filterForTypeExportar(void* pElement);

int Service_sortForType(void* itemA, void* itemB);
int Service_sortForDescription(void* itemA, void* itemB);
#endif /* SERVICE_H_ */
