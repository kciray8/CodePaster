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

#ifndef SEARCHBROWSER_H
#define SEARCHBROWSER_H

#include <QTextBrowser>

class SearchWindow;
class Code;

class SearchBrowser: public QTextBrowser {
    Q_OBJECT
    SearchWindow *pSearchEngine;
    Code *m_selectedCode;
    void contextMenuEvent(QContextMenuEvent *event);
    void keyPressEvent(QKeyEvent *event);
    int cursorPositionUnderMouse();
public:
    explicit SearchBrowser(SearchWindow *parent);

signals:

public slots:

private slots:
    void editCodeSlot();
    void deleteCodeSlot();
    void showPropertiesSlot();
    void onCopySlot();
    void onSelectionShanged();
};

#endif // SEARCHBROWSERWIDGET_H
