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

#include "codepaster.h"
#include "codeeditorwindow.h"
#include "searchwindow.h"
//#include <windows.h>
#include <QtCore>
#include "codebase.h"

extern CodeBase *pCodeBase;
extern SearchWindow *pSearchWindow;

CodePaster::CodePaster():
   // m_settings(QSettings::IniFormat, QSettings::UserScope,"KciRay", "CodePaster")
  m_settings(QApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat)
{
    copy = new QxtGlobalShortcut(QKeySequence("Ctrl+D"));
    paste = new QxtGlobalShortcut(QKeySequence("Meta+V"));

    connect(copy, SIGNAL(activated()), this, SLOT(onAddSnippet()));
    connect(paste, SIGNAL(activated()), this, SLOT(onSearch()));

    m_tray.setIcon(QIcon(":/images/tray.png"));
    if(m_settings.value("basePath").isValid()){
        m_basePath = m_settings.value("basePath").toString();
    }else{
        m_basePath = QApplication::applicationDirPath() + "/base.xml";//default path
        m_settings.setValue("basePath",m_basePath);
    }
    
    if(m_tray.isSystemTrayAvailable()) {
        QMenu *pTrayMenu = new QMenu();
        pTrayMenu->addAction("Add snippet", this, SLOT(onAddSnippet()),Qt::ControlModifier + Qt::Key_D);
        pTrayMenu->addAction("Search", this, SLOT(onSearch()),Qt::MetaModifier + Qt::Key_V);
        pTrayMenu->addSeparator();
        pTrayMenu->addAction("Save", this, SLOT(save()));
        pTrayMenu->addSeparator();
        pTrayMenu->addAction("Exit", this, SLOT(exit()));
        m_tray.setContextMenu(pTrayMenu);
        m_tray.show();
    }
    
    QApplication::setQuitOnLastWindowClosed(false);
    load();
    connect(&autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));
    autoSaveTimer.start(1000*60*5);//Every 5 minutes
    QApplication::setWindowIcon(QIcon(":/images/tray.png"));
}

void CodePaster::autoSave()
{
    save();
}

void CodePaster::saveInFile(QString filePatch)
{
    QString xmlStr;
    QDomDocument xmlDoc = pCodeBase->getXMLDoc();
    xmlStr = xmlDoc.toString();
    saveStrInFile(xmlStr, filePatch);
}

void CodePaster::saveStrInFile(QString &str, QString filePatch)
{
    QFile fileXML;
    QTextStream out(&fileXML);
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    fileXML.setFileName(filePatch);
    fileXML.open(QIODevice::WriteOnly | QIODevice::Text);
    out << str;
}

void CodePaster::load()
{
    QFile fileXML;
    QString xmlStr;
    QDomDocument domDoc;
    QTime time;
    time.start();
    fileXML.setFileName(m_basePath);

    if(fileXML.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&fileXML)) {
            pCodeBase->buildFromDoc(domDoc);
        }

        fileXML.close();
    }
}


CodePaster::~CodePaster()
{
}

void CodePaster::exit()
{
    save();
    m_tray.hide();
    QApplication::exit();
}

void CodePaster::save()
{
    saveInFile(m_basePath);
}

void CodePaster::onAddSnippet()
{
    CodeEditorWindow *pCodeEditor = new CodeEditorWindow();
    pCodeEditor->show();
    pCodeEditor->activateWindow();
}

void CodePaster::onSearch()
{
    if(pSearchWindow != nullptr){
        pSearchWindow->activate();
    }else{
        pSearchWindow = new SearchWindow();
        pSearchWindow->show();
        pSearchWindow->activate();
    }
}
