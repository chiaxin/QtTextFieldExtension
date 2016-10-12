//
// @ fileedit.cpp
// @ Describe -
// This Qt extension lib can process with drop/drag/double-click action
// inherit from QLineEdit class
// 
// Copyright 2016 Chia Xin Lin <nnnight@gmail.com>
//
#include "fileedit.h"
#include <QLineEdit>
#include <QMimeData>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDebug>
#include <QDir>

FileEdit::FileEdit(QWidget * parent) :
	QLineEdit(parent),
	withDropFilter(false),
	allowedExts(new QStringList)
{
	this->setAcceptDrops(true);
	this->setDragEnabled(true);
}

FileEdit::~FileEdit()
{

}

void FileEdit::dragEnterEvent(QDragEnterEvent * event)
{
	if (event->mimeData()->hasText())
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void FileEdit::mouseDoubleClickEvent(QMouseEvent * event)
{
	if (this->text().isEmpty())
	{
		return;
	}
	if (event->button() == Qt::LeftButton)
	{
		QFileInfo fileinfo(this->text());
		if (!fileinfo.exists())
		{
			event->ignore();
			return;
		}
		QString path = QDir::toNativeSeparators(fileinfo.absoluteDir().path());
		QProcess::startDetached("explorer.exe", QStringList() << path);
		event->accept();
	}
	event->ignore();
}

void FileEdit::dropEvent(QDropEvent * event)
{
	// If mimeData has text, set context, otherwise set it to empty.
	QString context = event->mimeData()->hasText() ?
		event->mimeData()->text() : "";
	if (context.isEmpty())
	{
		event->ignore();
		return;
	}
	event->acceptProposedAction();
	QString dropped_text = context.startsWith("file:///") ?
		context.remove("file:///") : context;
	QFileInfo fileinfo(dropped_text);

	// If the file is not exists or not a file, ignore.
	if (!fileinfo.isFile())
	{
		event->ignore();
		return;
	}
	if (withDropFilter)
	{
		for (QStringList::size_type idx = 0; 
			idx < allowedExts->length(); 
			idx++)
		{
			if (dropped_text.endsWith(allowedExts->at(idx)))
			{
				setText(dropped_text);
				event->accept();
			}
		}
	}
	else
	{
		setText(dropped_text);
		event->accept();
	}
}

void FileEdit::setDropFilter(bool hasFilter)
{
	withDropFilter = hasFilter;
}

void FileEdit::setAllowed(const QStringList & allowed)
{
	// Reset allowed extensions.
	allowedExts->clear();
	allowedExts->append(allowed);
	
	// If no any allowed extensions, turn drop filter off. 
	if (allowedExts->isEmpty())
	{
		setDropFilter(false);
	}
}