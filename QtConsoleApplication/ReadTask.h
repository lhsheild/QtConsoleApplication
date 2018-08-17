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
	//ע�⣡Ҫʹ���źţ�����QObejct �� QRunnable��̳У��ǵ�QObjectҪ����ǰ��
	void mySignal();
};

