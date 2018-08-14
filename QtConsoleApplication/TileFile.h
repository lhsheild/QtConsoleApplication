#pragma once
#include <qstring.h>
#include <QFileInfoList>

class TileFile
{
public:
	TileFile();
	~TileFile();
	int tileLOD;
	QFileInfo tileFileInfo;
};

