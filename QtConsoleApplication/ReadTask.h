#pragma once
#include <qobjectdefs.h>
#include "TileFile.h"
#include  <QVector>
#include  <QRunnable>

class ReadTask : public QRunnable
{
public:
	ReadTask(QVector<TileFile*> t_TileVector);
	~ReadTask();
protected:
	void run();
	QVector<TileFile*> TileVector;
	void ReadOSGB();
signals:
	//注意！要使用信号，采用QObejct 和 QRunnable多继承，记得QObject要放在前面
	void mySignal();
};

