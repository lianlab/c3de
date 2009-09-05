#include "BufferReader.h"
#include <fstream>

BufferReader::BufferReader(char *a_buffer)
{
	m_offset = 0;
	m_buffer = a_buffer;
}

BufferReader::~BufferReader()
{

}

void BufferReader::Reset()
{
	m_offset = 0;
}

int BufferReader::ReadNextInt()
{
	int * buffer = (int*)malloc(sizeof(int));
	memcpy(buffer,&m_buffer[m_offset],sizeof(int));
	m_offset += sizeof(int);
	int returned = buffer[0];
	free(buffer);
	buffer = NULL;
	return returned;
}

float BufferReader::ReadNextFloat()
{
	float * buffer = (float*)malloc(sizeof(float));
	memcpy(buffer,&m_buffer[m_offset],sizeof(float));
	m_offset += sizeof(float);
	float returned = buffer[0];
	free(buffer);
	buffer = NULL;
	return returned;
}