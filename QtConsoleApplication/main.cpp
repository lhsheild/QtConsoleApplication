#include <QtCore/QCoreApplication>
#include <QFileInfoList>
#include <QDir>
#include <QVector>
#include <QMap>
#include "TileFolder.h"
#include <iostream>
#include "TileFile.h"
#include <osgDB/ReaderWriter>
#include <osgDB/readfile>
#include <osgDB/writefile>
#include "TextureVisitor.h"

QVector<TileFolder> ClassifyTileModelByFolder(QString TilePath);
TileFile ClassifyTileModelByLOD(QFileInfo TileInfo);
void Conv(TileFile TileFile, osg::ref_ptr<osg::Group> root1, osg::ref_ptr<osg::Group> root2, osg::ref_ptr<osg::Group> root3, osg::ref_ptr<osg::Group> root4, osg::ref_ptr<osg::Group> root5, osg::ref_ptr<osg::Group> root6);

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QVector<TileFolder> tileModelVectorByFolder;


	tileModelVectorByFolder = ClassifyTileModelByFolder("D:\QXOsgb"); //按文件夹分类倾斜模型信息

	for each(TileFolder tileFolder in tileModelVectorByFolder)
	{
		QVector<TileFile> tileModelVectorByLOD;
		QVector<TileFile> TileVector1;
		QVector<TileFile> TileVector2;
		QVector<TileFile> TileVector3;
		QVector<TileFile> TileVector4;
		QVector<TileFile> TileVector5;
		QVector<TileFile> TileVector6;

		for each(QFileInfo qf in tileFolder.folderFileInfoList)
		{
			//std::cout << qf.absoluteFilePath().toStdString() << std::endl; //当前文件夹中的倾斜文件
			TileFile tileFile = ClassifyTileModelByLOD(qf);
			tileModelVectorByLOD.append(tileFile);

		}
		for each(TileFile tileFile in tileModelVectorByLOD)
		{
			//std::cout << "LOD:" << std::to_string(tileFile.tileLOD) << "  文件：" << tileFile.tileFileInfo.absoluteFilePath().toStdString() << std::endl; //当前文件信息
			if (tileFile.tileLOD == 1)
			{
				TileVector1.append(tileFile);
			}
			if (tileFile.tileLOD == 2)
			{
				TileVector2.append(tileFile);
			}
			if (tileFile.tileLOD == 3)
			{
				TileVector3.append(tileFile);
			}
			if (tileFile.tileLOD == 4)
			{
				TileVector4.append(tileFile);
			}
			if (tileFile.tileLOD == 5)
			{
				TileVector5.append(tileFile);
			}
			if (tileFile.tileLOD == 6)
			{
				TileVector6.append(tileFile);
			}
		}

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

TileFile ClassifyTileModelByLOD(QFileInfo TileInfo)
{
	TileFile tileFile;
	if (TileInfo.fileName().contains("L15"))
	{
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 6;
	}
	if (TileInfo.fileName().contains("L16"))
	{
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 5;
	}
	if (TileInfo.fileName().contains("L17"))
	{
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 4;
	}
	if (TileInfo.fileName().contains("L18"))
	{
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 3;
	}
	if (TileInfo.fileName().contains("L18"))
	{
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 5;
	}
	if (TileInfo.fileName().contains("L19"))
	{
		tileFile.tileFileInfo = TileInfo;
		tileFile.tileLOD = 1;
	}
	return tileFile;
}

/*void Conv(TileFile TileFile, osg::ref_ptr<osg::Group> root1, osg::ref_ptr<osg::Group> root2, osg::ref_ptr<osg::Group> root3, osg::ref_ptr<osg::Group> root4, osg::ref_ptr<osg::Group> root5, osg::ref_ptr<osg::Group> root6)
{
	if (TileFile.tileLOD == 1)
	{
		root1->addChild(osgDB::readNodeFile(TileFile.tileFileInfo.absoluteFilePath().toStdString()));
	}
	if (TileFile.tileLOD == 2)
	{
		root2->addChild(osgDB::readNodeFile(TileFile.tileFileInfo.absoluteFilePath().toStdString()));
	}
	if (TileFile.tileLOD == 3)
	{
		root3->addChild(osgDB::readNodeFile(TileFile.tileFileInfo.absoluteFilePath().toStdString()));
	}
	if (TileFile.tileLOD == 4)
	{
		root4->addChild(osgDB::readNodeFile(TileFile.tileFileInfo.absoluteFilePath().toStdString()));
	}
	if (TileFile.tileLOD == 5)
	{
		root5->addChild(osgDB::readNodeFile(TileFile.tileFileInfo.absoluteFilePath().toStdString()));
	}
	if (TileFile.tileLOD == 6)
	{
		root6->addChild(osgDB::readNodeFile(TileFile.tileFileInfo.absoluteFilePath().toStdString()));
	}
}*/

