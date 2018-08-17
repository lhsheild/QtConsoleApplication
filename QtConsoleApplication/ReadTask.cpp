#include <osg/ref_ptr>
#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include "ReadTask.h"


ReadTask::ReadTask(QVector<TileFile*> t_TileVector)
{
	setAutoDelete(true);
	TileVector = t_TileVector;
}


ReadTask::~ReadTask()
{
}

void ReadTask::run()
{
	ReadOSGB();
}

void ReadTask::ReadOSGB()
{
	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osgViewer::Viewer> view = new osgViewer::Viewer();
	for (int i = 0; i<TileVector.size(); i++)
	{
		QString q = TileVector[i]->tileFileInfo.absoluteFilePath();
		try
		{
			osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(q.toStdString());
			root->addChild(node);
			node.release();
		}
		catch (...)
		{
			int t = 0;
			return;
		}
		
	}
	view->setSceneData(root.get());

	view->setUpViewInWindow(300, 300, 1280, 720);
	view->realize();
	view->run();
	root.release();
}