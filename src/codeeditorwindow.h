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

#ifndef CODEEDITORWINDOW_H
#define CODEEDITORWINDOW_H

#include <QtWidgets>
#include "codeeditor.h"
class Code;

class CodeEditorWindow : public QMainWindow {
    Q_OBJECT
    Code *m_editCode;
    CodeEditor *m_codeEditor;
    QLineEdit m_keywordsEditor;
    virtual void closeEvent(QCloseEvent *event);
public:
    explicit CodeEditorWindow(QWidget *parent = 0, Code *m_editCode = nullptr);
    ~CodeEditorWindow();
signals:

public slots:
    void onSave();
    
    friend class CodeEditor;
};

#endif // CODEEDITORWINDOW_H
