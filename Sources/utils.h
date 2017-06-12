/*
 * utils.h
 *
 *  Created on: 07/06/2017
 *      Author: Jefferson
 */

#ifndef SOURCES_UTILS_H_
#define SOURCES_UTILS_H_

//#ifdef PEX_RTOS_START
#define _malloc(size)	pvPortMalloc(size)
#define _free(ptr)		vPortFree(ptr);ptr=NULL
//#else
//#define _malloc(size)	malloc(size)
//#define _free(ptr)		free(ptr)
//#endif

typedef	char** Itens;

typedef struct{

	char**	itens;

	size_t	size;

} List;

#include "stdlib.h"

void str_split(List* result,char* a_str, const char a_delim);
void str_append(char subject[], char insert[], int pos);

#endif /* SOURCES_UTILS_H_ */
