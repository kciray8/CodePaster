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

#include "codeeditorwindow.h"
#include "codebase.h"
#include "code.h"
#include <QtCore>
#include <QtWidgets>
#include "codepaster.h"

extern CodeBase *pCodeBase;
extern CodePaster *codePaster;

CodeEditorWindow::CodeEditorWindow(QWidget *parent, Code *pEditCode) :
    QMainWindow(parent), m_editCode(pEditCode)
{
    QWidget *pCentralWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    bool autoPaste = (pEditCode)?false:true;
    
    m_codeEditor = new CodeEditor(this,autoPaste);
    m_codeEditor->setStyleSheet("font: 10pt \"Courier\";");

    if (pEditCode)
        m_codeEditor->insertHtml(*pEditCode->getHtml());

    layout->addWidget(m_codeEditor);
    QLabel *pLabelKeywords = new QLabel("Keywords:");
    layout->addWidget(pLabelKeywords);
    m_keywordsEditor.setText("c++,qt");

    if (pEditCode)
        m_keywordsEditor.setText(*pEditCode->getKeywords());

    layout->addWidget(&m_keywordsEditor);
    QPushButton *pSaveButton = new QPushButton("OK");
    QObject::connect(pSaveButton, SIGNAL(clicked()), this, SLOT(onSave()));
    layout->addWidget(pSaveButton);
    pCentralWidget->setLayout(layout);
    setCentralWidget(pCentralWidget);
    resize(600, 500);

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    setWindowTitle("Code snippet editor");
}

CodeEditorWindow::~CodeEditorWindow()
{
    delete m_codeEditor;
}

void CodeEditorWindow::closeEvent(QCloseEvent * event){
    Q_UNUSED(event)
    delete this;
}

void CodeEditorWindow::onSave()
{
    Code *pNewCode = new Code(m_codeEditor->toHtml(), m_keywordsEditor.text());
    
    if (m_editCode == nullptr) {
        pNewCode->setCreateTime(QDateTime::currentMSecsSinceEpoch());
        pCodeBase->add(pNewCode);
    } else {
        pNewCode->copyMembers(m_editCode);
        pCodeBase->add(pNewCode, m_editCode->getId());
    }
    
    close();
    codePaster->save();
}
