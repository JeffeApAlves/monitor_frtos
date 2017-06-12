/*
 * CircularBuffer.h
 *
 *  Created on: 04/06/2017
 *      Author: Jefferson
 */

#ifndef SOURCES_RINGBUFFER_H_
#define SOURCES_RINGBUFFER_H_

#include "PE_Types.h"

#define BUFFER_SIZE		64

typedef struct{

	unsigned char	data[BUFFER_SIZE];
	unsigned char	index_producer;
	unsigned char	index_consumer;
	unsigned char	count;

} RingBuffer;

bool getData(RingBuffer* buffer,char* ch);
bool putData(RingBuffer* buffer,char ch);
bool hasData(RingBuffer* buffer);
void initBuffer(RingBuffer* buffer);
bool isFull(RingBuffer* buffer);
unsigned char getCount(RingBuffer* buffer);


#endif /* SOURCES_RINGBUFFER_H_ */
