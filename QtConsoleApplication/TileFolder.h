#pragma once
#include <qstring.h>
#include <QFileInfoList>

class TileFolder
{
public:
	TileFolder();
	~TileFolder();

	QFileInfoList folderFileInfoList;
	QString folderName;

};

