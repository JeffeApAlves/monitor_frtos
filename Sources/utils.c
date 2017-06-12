/*
 * utils.c
 *
 *  Created on: 07/06/2017
 *      Author: Jefferson
 */

#include <string.h>
#include <assert.h>
#include "utils.h"

void str_split(List* result,char* str, const char a_delim){

    char delim[2];
    delim[0]			= a_delim;
    delim[1]			= 0;

    char*	tmp			= str;
    char*	sptr		= str;
    result->size		= 0;
    char*	last_comma	= NULL;
    result->itens		= NULL;
    char*	token		= NULL;

    if(str!=NULL){

		while (*tmp){

			if (a_delim == *tmp){

				result->size++;
	            last_comma = tmp;
			}

			tmp++;
		}

		result->size += last_comma < (str + strlen(str) - 1);

		if(result->size>0){

			result->itens = _malloc(sizeof(char*) * result->size);

			if (result->itens) {

				size_t idx = 0;

				*(result->itens + idx) = NULL;

				while ((token = strtok_r(sptr, delim, &sptr)) != NULL) {

					assert(idx < result->size);

					 //Equivalente a *(result->itens + idx++) = strdup(token);

					tmp = _malloc((strlen(token) + 1)*sizeof(char));

					memset(tmp,0,strlen(token) + 1);

					strcpy(tmp, token);

					*(result->itens + idx++) = tmp;
				}
			}
		}
    }
}
//------------------------------------------------------------------------

void str_append(char subject[], char insert[], int pos) {

	size_t size = (strlen(subject)-pos) + (strlen(insert) + 1);

	if(size>0){

		char* buf	= (char*) _malloc(sizeof(char)*size);

		if(buf!=NULL){

			memset(buf,0,size);

			strcpy(buf, insert);
			strcpy(buf+strlen(insert), subject + pos);
			strcpy(subject + pos , buf);

			_free(buf);
		}
	}
}
//------------------------------------------------------------------------
