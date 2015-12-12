#include "CircularBuffer.h"


CircularBuffer::CircularBuffer(size_t size, Stream* debug)
{
	this->buffer = (uint8_t*)calloc(size, sizeof(uint8_t));

	this->size = size;
	this->pos = 0;
	this->debug = debug;

}

CircularBuffer::~CircularBuffer()
{
	free(this->buffer);
}

void CircularBuffer::insert(uint8_t value)
{
	this->buffer[this->pos++] = value;
	if (this->pos % size == 0)
	{
		if(pos > 0){this->pos = 0;}
		full = true;
	}
}

uint8_t CircularBuffer::insert(uint8_t* source, size_t offset, size_t length)
{
	for(size_t i = 0; i < length; i++)
	{
		insert(source[offset+i]);
	}
}

uint8_t CircularBuffer::operator[](int pos)
{
	int val = (this->size + pos + this->pos) % this->size;
	if(!full)
	{
		val = pos;
	}
	return this->buffer[val];
}

size_t CircularBuffer::getBytes(uint8_t* destination, size_t offset, size_t length)
{
	debug->print("First: ");
	debug->print(this->operator[](0), HEX);
	debug->print(" ");
	debug->println(this->operator[](0));

	for(size_t i = 0; i < length; i++)
	{
		destination[i + offset] = this->operator[](i);
	}
	return length;
}

bool CircularBuffer::endsWith(const char *buf, size_t buf_size)
{
	return this->endsWith((uint8_t*) buf, buf_size);
}

bool CircularBuffer::endsWith(uint8_t *buf, size_t buf_size)
{
	if(buf_size > this->size)
	{
		return false;
	}
	bool result = true;
	for(int i = buf_size * -1; i < 0; i++)
	{
		result = (*this)[i] == buf[i + buf_size];

		if(!result)
		{
			break;
		}
	}
	return result;
}

size_t CircularBuffer::getSize()
{
	if(isFull())
	{
		return size;
	}else
	{
		return getPos();
	}
}

size_t CircularBuffer::getPos()
{
	return pos;
}

bool CircularBuffer::isFull()
{
	return full;
}
