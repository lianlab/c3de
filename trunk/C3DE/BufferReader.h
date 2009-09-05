#ifndef BUFFER_READER_H
#define BUFFER_READER_H

class BufferReader
{
public:
	BufferReader(char *a_buffer);
	~BufferReader();
	int ReadNextInt();
	float ReadNextFloat();
	void Reset();
private:
	int m_offset;
	char *m_buffer;

};
#endif