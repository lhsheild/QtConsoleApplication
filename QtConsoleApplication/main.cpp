#include <QtCore/QCoreApplication>

#include <QDir>
#include <QVector>
#include <QString>
#include <QThreadPool>
#include <QMap>

#include <iostream>

#include <osgDB/ReaderWriter>
#include <osgViewer/Viewer>

#include "TextureVisitor.h"
#include "TileFile.h"
#include "TileFolder.h"
#include "ReadTask.h"
#include "ConvTask.h"

QVector<TileFolder> ClassifyTileModelByFolder(QString TilePath);
void ClassifyTileModelByLOD(QFileInfo TileInfo, QVector<TileFile*>& TileVector1, QVector<TileFile*>& TileVector2, QVector<TileFile*>& TileVector3, QVector<TileFile*>& TileVector4);
void ReadOSGB(QVector<TileFile*> TileVector);


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QThreadPool pool;
	pool.setMaxThreadCount(20);

	QVector<TileFolder> tileModelVectorByFolder;
	std::cout << "请输入目录" << std::endl;
	std::string folderPath;
	std::cin >> folderPath;

	tileModelVectorByFolder = ClassifyTileModelByFolder(QString::fromStdString(folderPath)); //按文件夹分类倾斜模型信息
	ConvTask::bbbb = tileModelVectorByFolder.size()*4;
	ConvTask::aaaa = 0;
	for each(TileFolder tileFolder in tileModelVectorByFolder)
	{
		QVector<TileFile> tileModelVectorByLOD;
		QVector<TileFile*> TileVector1;
		QVector<TileFile*> TileVector2;
		QVector<TileFile*> TileVector3;
		QVector<TileFile*> TileVector4;

		for each(QFileInfo qf in tileFolder.folderFileInfoList)
		{
			//std::cout << qf.absoluteFilePath().toStdString() << std::endl; //当前文件夹中的倾斜文件
			ClassifyTileModelByLOD(qf, TileVector1, TileVector2, TileVector3,TileVector4);			
		}
		
		//std::cout << "debug"<<std::endl;
		//QString q = TileVector1[1]->tileFileInfo.fileName();
		pool.start(new ConvTask(TileVector1, QString::fromStdString(folderPath)));
		pool.start(new ConvTask(TileVector2, QString::fromStdString(folderPath)));
		pool.start(new ConvTask(TileVector3, QString::fromStdString(folderPath)));
		pool.start(new ConvTask(TileVector4, QString::fromStdString(folderPath)));

		TileVector1.clear(); TileVector2.clear(); TileVector3.clear(); TileVector4.clear();
	}



	return a.exec();
}

QVector<TileFolder> ClassifyTileModelByFolder(QString TilePath)
{
	QVector<TileFolder> TileModelVectorByFolder;
	QDir dir(TilePath);
	QFileInfoList allFolderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
	for (int i=0;i<allFolderList.size();i++)
	{
		//std::cout << allFolderList.at(i).fileName().toStdString()<<std::endl; //当前文件夹
		TileFolder tileFolder;
		if (allFolderList.at(i).fileName().contains("Tile_"))
		{
			tileFolder.folderName = allFolderList.at(i).fileName();
			QDir folderDir(allFolderList.at(i).absoluteFilePath());
			QFileInfoList tempFileInfoList = folderDir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
			for (int j=0;j<tempFileInfoList.size();j++)
			{
				//std::cout << tempFileInfoList.at(j).fileName().toStdString() << std::endl; //当前文件
				tileFolder.folderFileInfoList.append(tempFileInfoList.at(j));
			}
			TileModelVectorByFolder.append(tileFolder);
		}
	}
	return TileModelVectorByFolder;
}

/*QVector<TileFile> ClassifyTileModelByLOD(QFileInfo TileInfo)
{
	QVector<TileFile> TileModelVectorByLOD;	
	if (TileInfo.fileName().contains("L15"))
	{
		TileFile tileFile;
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 5;
		TileModelVectorByLOD.append(tileFile);
	}
	if (TileInfo.fileName().contains("L16"))
	{
		TileFile tileFile;
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 4;
		TileModelVectorByLOD.append(tileFile);
	}
	if (TileInfo.fileName().contains("L17"))
	{
		TileFile tileFile;
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 3;
		TileModelVectorByLOD.append(tileFile);
	}
	if (TileInfo.fileName().contains("L18"))
	{
		TileFile tileFile;
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 2;
		TileModelVectorByLOD.append(tileFile);
	}
	if (TileInfo.fileName().contains("L18"))
	{
		TileFile tileFile;
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 1;
		TileModelVectorByLOD.append(tileFile);
	}
	return TileModelVectorByLOD;
}*/

void ClassifyTileModelByLOD(QFileInfo TileInfo,QVector<TileFile*>& TileVector1, QVector<TileFile*>& TileVector2, QVector<TileFile*>& TileVector3, QVector<TileFile*>& TileVector4)
{
	TileFile* tileFile = new TileFile;
	if (TileInfo.fileName().contains("L15"))
	{
		tileFile->tileLOD = 4;
		tileFile->tileFileInfo = TileInfo;
		TileVector4.append(tileFile);
		//delete tileFile;
	}
	if (TileInfo.fileName().contains("L16"))
	{
		tileFile->tileLOD = 3;
		tileFile->tileFileInfo = TileInfo;
		TileVector3.append(tileFile);
		//delete tileFile;
	}
	if (TileInfo.fileName().contains("L17"))
	{
		tileFile->tileLOD = 2;
		tileFile->tileFileInfo = TileInfo;
		TileVector2.append(tileFile);
		//delete tileFile;
	}

	if (TileInfo.fileName().contains("L18"))
	{
		tileFile->tileLOD = 1;
		tileFile->tileFileInfo = TileInfo;
		TileVector1.append(tileFile);
		//delete tileFile;
	}

}

void ReadOSGB(QVector<TileFile*> TileVector)
{
	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osgViewer::Viewer> view = new osgViewer::Viewer();
		for (int i = 0; i<TileVector.size(); i++)
		{
			try
			{
				QString q = TileVector[i]->tileFileInfo.filePath();
				osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(q.toStdString());
				root->addChild(node);
				node.release();
			}
			catch(_exception e)
			{
				std::cout << "异常..." << std::endl;
				continue;		
			}
		}	
	view->setSceneData(root.get());
	view->setUpViewInWindow(800, 300, 1920, 1080);
	view->realize();
	view->run();
	root.release();
}
