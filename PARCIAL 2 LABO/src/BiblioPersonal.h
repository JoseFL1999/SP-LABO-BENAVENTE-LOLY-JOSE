/*
 * BiblioPersonal.h
 *
 *  Created on: 4 jun 2022
 *      Author: --
 */

#include "LinkedListP.h"
#ifndef BIBLIOPERSONAL_H_
#define BIBLIOPERSONAL_H_

int isNum(char* string);

int isFloat(char* string);

int isText(char* string);

int isAlphanumeric(char *string);

int convertWordFirstUppAndRestLower(char* string);

int convertStringMayus(char* string);

int getMenuForInt(int* option, char* message, int maxOption, int minOption);

int getText(char* text,char* message, char* messageError, int retry);

int getFloat(float* numFloat, char* message, char* messageError, int retry);

int getAlphanumeric(char* alphanumeric,char* message, char* messageError, int retry);

int findId(LinkedList* list, int id);
int getId(LinkedList* list, char* message, char* messageError, int* index);
#endif /* BIBLIOPERSONAL_H_ */
