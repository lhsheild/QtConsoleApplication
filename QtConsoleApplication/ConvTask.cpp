#include "ConvTask.h"
#include <osg/Group>
#include <osgDB/ReadFile>
#include "TextureVisitor.h"
#include <QDir>
#include <osgViewer/Viewer>

int ConvTask::aaaa = 0;
int ConvTask::bbbb = 0;
ConvTask::ConvTask(QVector<TileFile*> t_TileVector, QString t_InputPath)
{
	setAutoDelete(true);
	TileVector = t_TileVector;
	InputPath = t_InputPath;
}


ConvTask::~ConvTask()
{
}

void ConvTask::run()
{
	ConvTask::ConvOSGB2OBJ();
}

void ConvTask::ConvOSGB2OBJ()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osgViewer::Viewer> view = new osgViewer::Viewer();
	TextureVisitor tv;
	QString savePath; QString saveName; QString lodName;
	savePath = InputPath.append("\\output\\");

	for (int i=0;i<TileVector.size();i++)
	{
		try
		{
			saveName = TileVector[i]->tileFileInfo.fileName().left(14);
			osgDB::Options  *a = new osgDB::Options(std::string("noTriStripPolygons"));
			osg::Node* node = osgDB::readNodeFile(TileVector[i]->tileFileInfo.absoluteFilePath().toStdString(), a);
			root->addChild(node);

			if (TileVector[i]->tileLOD == 1)
			{
				lodName = "_lod_01";
			}
			if (TileVector[i]->tileLOD == 2)
			{
				lodName = "_lod_02";
			}
			if (TileVector[i]->tileLOD == 3)
			{
				lodName = "_lod_03";
			}
			if (TileVector[i]->tileLOD == 4)
			{
				lodName = "_lod_04";
			}
		}
		catch (...)
		{
			std::cout << "crushed" << std::endl;
		}
	}
	root->accept(tv);
	savePath = savePath + lodName+"\\";
	QDir dir;
	if (!dir.exists(savePath))
	{
		dir.mkpath(savePath);
	}
	osgDB::writeNodeFile(*root.get(), (savePath+saveName+ lodName +".obj").toStdString());

	//ÌùÍ¼Ó³Éä±í
	std::map<std::string, osg::Image*>imageList = tv.getImages();
	//ÌùÍ¼Ó³Éä±íµü´úÆ÷
	std::map<std::string, osg::Image*>::iterator iter = imageList.begin();
	for (; iter != imageList.end(); iter++)
	{
		osgDB::writeImageFile(*(iter->second), savePath.toStdString() + iter->first);
	}

	root.release();
	aaaa++;
	if(aaaa==bbbb)
	{
		std::cout << "Íê³É£¡" << std::endl;
	}
	
}

