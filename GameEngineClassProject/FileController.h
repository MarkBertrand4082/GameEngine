#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include "StandardIncludes.h"

class FileController : public Singleton<FileController>
{
public:
	FileController();
	virtual ~FileController();

	string GetCurDirectory();
	int GetFileSize(string _filePath);
	bool ReadFile(string _filePath, unsigned char* _buffer, unsigned int _buffersize);

private:
	FILE* m_handle;
};

#endif