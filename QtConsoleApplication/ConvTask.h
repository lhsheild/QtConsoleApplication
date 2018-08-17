#pragma once
#include <QRunnable>
#include <QVector>
#include "TileFile.h"

class ConvTask :public QRunnable
{
public:
	ConvTask(QVector<TileFile*> t_TileVector,QString t_InputPath);
	static int aaaa; 
	static int bbbb;
	~ConvTask();
protected:
	void run();
	QVector<TileFile*> TileVector;
	QString InputPath;
	void ConvOSGB2OBJ();
};

