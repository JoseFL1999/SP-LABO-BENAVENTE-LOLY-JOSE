/*
 * BiblioPersonal.c
 *
 *  Created on: 4 jun 2022
 *      Author: --
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LinkedListP.h"

int isNum(char* string)
{
	int i;
	int haveWord;
	int haveNum;
	int haveSpace;
	int ret;
	haveSpace = 0;
	haveNum = 0;
	haveWord = 0;
	ret=0;
	if(string!=NULL)
	{
		for (i = 0; i < strlen(string); i++)
		{
			char word = string[i];
			if(isalpha(word))
			{
				haveWord = 1;
			}
			if(isdigit(word))
			{
				haveNum = 1;
			}
			if(word==32)
			{
				haveSpace = 1;
			}
		}
		if(haveWord==0 && haveNum==1 && haveSpace==0)
		{
			ret=1;
		}
	}
	return ret;// retorna 1 si es numero o 0 si no es numero
}

int isFloat(char* string)

{
	int i;
	int haveWord;
	int haveNum;
	int havePoint;
	int haveSpace;
	int flagNum;
	int flagPoint;
	int ret;
	havePoint = 0;
	haveNum = 0;
	haveWord = 0;
	haveSpace = 0;
	flagPoint = 0;
	flagNum = 0;
	ret=0;
	if(string!=NULL)
	{
		for (i = 0; i < strlen(string); i++)
		{
			char word = string[i];
			if(isalpha(word))
			{
				haveWord = 1;
			}
			if(isdigit(word))
			{
				haveNum = 1;
				flagNum++;
			}
			if(word==32)// ASCII 32 -> SPACE
			{
				haveSpace = 1;
			}
			if (word==46 && flagNum!=0)// ASCII 46 -> .
			{
				havePoint = 1;
				flagPoint++;
			}
		}
		if(haveWord==0 && haveNum==1 && havePoint == 1 && flagPoint == 1 && haveSpace == 0)
		{
			ret=1;
		}
	}
	return ret;// retorna 1 si es flotante o 0 si no es flotante
}

int isText(char* string)
{
	int ret;
	int i;
	int tieneLetra = 0;
	int tieneNumero = 0;
	ret=0;
	if(string!=NULL)
	{
		for (i = 0; i < strlen(string); i++)
		{
			char letra = string[i];
			if (isalpha(letra))
			{
				tieneLetra = 1;
			}
			if (isdigit(letra))
			{
				tieneNumero = 1;
			}
		}
		if(tieneLetra==1 && tieneNumero==0)
		{
			ret=1;
		}
	}
	return ret; //retorna 1 si es Texto o 0 si no es texto

}

int isAlphanumeric(char *string)
{
	int ret;
	int i;
	int haveWord = 0;
	int haveNum = 0;
	ret=0;
	if(string!=NULL)
	{
		for (i = 0; i < strlen(string); i++)
		{
			char word = string[i];
			if (isalpha(word))
			{
				haveWord = 1;
			}
			if (isdigit(word))
			{
				haveNum = 1;
			}
		}
		if(haveWord==1 && haveNum==1)
		{
			ret=1;
		}
		else
		{
			ret=0;
		}
	}
	return ret;
}

int convertWordFirstUppAndRestLower(char* string)
{
	int ret;
	int i;
	char convertMayus;
	char convertMinus;
	int countSpace;
	countSpace=1;
	ret=-1;
	if(string!=NULL)
	{
		for(i=0;i<strlen(string);i++)
		{
			if(isalpha(*(string+i)) && countSpace==1)
			{
				convertMayus = toupper(string[i]);
				string[i]=convertMayus;
				countSpace=0;
			}
			else if(isalpha(*(string+i)))
			{
				convertMinus=tolower(string[i]);
				string[i]=convertMinus;
			}
			if(*(string+i)==32)
			{
				countSpace=1;
			}
		}
		ret=0;
	}
	return ret;
}

int getMenuForInt(int* option, char* message, int maxOption, int minOption)
{
	char bufferOption[2];
	int ret;
	ret=-1;
	if(option!=NULL && message!=NULL)
	{
		system("cls");
		printf(message);
		printf("\nElija una opcion: ");
		fflush(stdin);
		gets(bufferOption);
		while(isNum(bufferOption)==0 || atoi(bufferOption)<minOption || atoi(bufferOption)>maxOption)
		{
			system("cls");
			printf(message);
			printf("\nError, elija una opcion valida:");
			fflush(stdin);
			gets(bufferOption);
		}
		*option = atoi(bufferOption);
		ret=0;
	}
	return ret;
}

int convertStringMayus(char* string)
{
	int ret;
	int i;
	char convertMayus;
	ret=-1;
	if(string!=NULL)
	{
		for(i=0;i<strlen(string);i++)
		{
			if(isalpha(string[i])!=0)
			{
				convertMayus = toupper(string[i]);
				string[i]=convertMayus;
			}
		}
		ret=0;
	}
	return ret;
}

int getText(char* text,char* message, char* messageError, int retry)
{
	int ret;
	char bufferText[50];
	ret=-1;
	if(text!=NULL && message!=NULL && messageError!=NULL && retry>0)
	{
		system("cls");
		printf(message);
		fflush(stdin);
		gets(bufferText);
		while(isText(bufferText)==0 || strlen(bufferText)<1 || strlen(bufferText)>50)
		{
			system("cls");
			printf(messageError);
			fflush(stdin);
			gets(bufferText);
			retry--;
			if(retry==0)
			{
				break;
			}
		}
		if(isText(bufferText)!=0)
		{
			if(convertWordFirstUppAndRestLower(bufferText)==0)
			{
				strcpy(text, bufferText);
				ret=0;
			}
		}
	}
	return ret; // return -1
}

int getFloat(float* numFloat, char* message, char* messageError, int retry)
{
	int ret;
	char bufferFloat[1024];
	ret=-1;
	if(numFloat!=NULL && message!=NULL && messageError!=NULL)
	{
		system("cls");
		printf(message);
		fflush(stdin);
		gets(bufferFloat);
		while(isFloat(bufferFloat)==0 || atof(bufferFloat)<100)
		{
			if(isNum(bufferFloat)!=0)
			{
				break;
			}
			system("cls");
			printf(messageError);
			fflush(stdin);
			gets(bufferFloat);
			retry--;
			if(retry==0)
			{
				break;
			}
		}
		if((isFloat(bufferFloat)!=0 && atof(bufferFloat)>99)||isNum(bufferFloat)!=0)
		{
			*numFloat=atof(bufferFloat);
			ret=0;
		}
		else
		{
			ret=-1;
		}
	}
	return ret;
}

int getAlphanumeric(char* alphanumeric,char* message, char* messageError, int retry)
{
	int ret;
	char bufferAlphanumeric[9];
	ret=-1;
	if(alphanumeric!=NULL && message!=NULL && messageError!=NULL && retry>0)
	{
		system("cls");
		printf(message);
		fflush(stdin);
		gets(bufferAlphanumeric);
		while(isAlphanumeric(bufferAlphanumeric)==0 || strlen(bufferAlphanumeric)!=7)
		{
			system("cls");
			printf(messageError);
			fflush(stdin);
			gets(bufferAlphanumeric);
			retry--;
			if(retry==0)
			{
				break;
			}
		}
		if(isAlphanumeric(bufferAlphanumeric)!=0 && strlen(bufferAlphanumeric)==7)
		{
			if(convertStringMayus(bufferAlphanumeric)==0)
			{
				strcpy(alphanumeric, bufferAlphanumeric);
				ret=0;
			}
		}
		}
		return ret;
}

/*int findId(LinkedList* list, int id)
{
	Passenger* aux;
	aux=Passenger_new();
	int index;
	int i;
	index=-1;
	if(list!=NULL && id>0 && aux!=NULL)
	{
		for(i=0;i<ll_len(list);i++)
		{
			aux=ll_get(list, i);
			if(aux->id == id)
			{
				index=i;
				break;
			}
		}
	}
	return index;
}

int getId(LinkedList* list, char* message, char* messageError, int* index)
{
	int ret;
	int countError;
	char id[10];
	countError=0;
	ret=-1;
	if(list!=NULL && index!=NULL)
	{
		do
		{
			if(countError==0)
			{
				printf(message);
				fflush(stdin);
				gets(id);
				countError++;
			}
			else
			{
				printf(messageError);
				fflush(stdin);
				gets(id);
			}
		}while(isNum(id)==0 || findId(list,atoi(id))==-1 || strlen(id)<1);
		if(isNum(id)==1 && findId(list,atoi(id))!=-1 && strlen(id)>=1)
		{
			*index=findId(list,atoi(id));
			ret=0;
		}
	}
	return ret;
}*/
