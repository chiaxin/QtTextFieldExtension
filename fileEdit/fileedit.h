//
// @ fileedit.h
// @ Describe -
// This Qt extension lib can process with drop/drag/double-click action
// inherit from QLineEdit class
// 
// Copyright 2016 Chia Xin Lin <nnnight@gmail.com>
//
#ifndef FILEEDIT_H
#define FILEEDIT_H
#include "fileedit_global.h"
#include <QString>
#include <QStringList>
#include <QLineEdit>
#include <QDropEvent>
#include <QMouseEvent>
#include <QDragEnterEvent>

class FILEEDIT_EXPORT FileEdit :public QLineEdit
{
public:
	explicit FileEdit(QWidget * parent = 0);
	virtual ~FileEdit();
	virtual void mouseDoubleClickEvent(QMouseEvent *)override;
	virtual void dragEnterEvent(QDragEnterEvent *)override;
	virtual void dropEvent(QDropEvent *)override;
	void setDropFilter(bool);
	void setAllowed(const QStringList &);
private:
	QStringList * allowedExts;
	bool withDropFilter;
};

#endif // FILEEDIT_H
