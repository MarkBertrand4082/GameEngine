#ifndef TGA_READER_H
#define TGA_READER_H

#include "StandardIncludes.h"

class Asset;

#pragma pack(push, 1)
typedef struct
{
	char IDLength;
	char ColourMapType;
	char DataTypeCode;
	short ColourMapStart;
	short ColourMapLength;
	char ColourMapDepth;
	short x_Origin;
	short y_Origin;
	short Width;
	short Height;
	char BitsPerPixel;
	char ImageDescriptor;
} TGAHeader;
#pragma pack(pop)


typedef struct
{
	short Width;
	short Height;
	short BitsPerPixel;
	short DataOffset;
}ImageInfo;

class TGAReader
{
public:
	TGAReader();
	virtual ~TGAReader() {};

	void ProcessAsset(Asset* _rawTGA, ImageInfo* _imageInfo);
	Asset* LoadTGAFromFile(string _file, ImageInfo* _imageInfo);

private:
	TGAHeader m_header;
	Asset* m_data;
};
#endif