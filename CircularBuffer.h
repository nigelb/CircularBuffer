/*
 * CircularBuffer.h
 *
 *  Created on: 4 Oct 2015
 *      Author: eng-nbb
 */

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"
#include "Stream.h"

class CircularBuffer
{
private:
	uint8_t *buffer;
	size_t size;
	size_t pos;
	bool full = false;
	Stream* debug;

public:
	CircularBuffer(size_t size, Stream* debug);
	~CircularBuffer();
	void insert(uint8_t value);
	uint8_t insert(uint8_t* source, size_t offset, size_t length);
	uint8_t operator[](int pos);
	size_t getBytes(uint8_t* destination, size_t offset, size_t length);
	bool endsWith(const char *buf, size_t buf_size);
	bool endsWith(uint8_t *buf, size_t buf_size);
	size_t getSize();
	size_t getPos();
	bool isFull();

};


#endif /* CIRCULARBUFFER_H_ */
