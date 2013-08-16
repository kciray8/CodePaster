/****************************************************************************
**
** CodePaster is program to simple and quick copy/paste snippets of code and organize it
** Copyright (C) 2013 Yaroslaw Baranow(aka KciRay).
** Contact: Yaroslaw Baranow (kciray8@gmail.com)
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
*****************************************************************************/

#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "searchbrowser.h"
#include "code.h"

struct BlockText {
    int begin;
    int end;
    Code *pCode;
};

class SearchWindow : public QMainWindow {
    Q_OBJECT
    QWidget centralWidget;
    QVBoxLayout layout;
    QHBoxLayout hLayout;
    QList<BlockText *> m_mapText;
    QLineEdit m_lineQuery;
    SearchBrowser *m_searchBrowser;
    void closeEvent(QCloseEvent *event);
public:
    explicit SearchWindow(QWidget *parent = 0);
    Code *getCodeByPos(int pos);
    void activate();
signals:

public slots:
    void onSearch();

    friend class CodeBase;
};

#endif // SEARCHWINDOW_H
