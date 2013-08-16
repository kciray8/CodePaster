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

#include "searchwindow.h"
#include "codebase.h"

extern CodeBase *pCodeBase;
extern SearchWindow *pSearchWindow;

SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QObject::connect(&m_lineQuery, SIGNAL(returnPressed()), this, SLOT(onSearch()));
    hLayout.addWidget(&m_lineQuery);
    
    QPushButton *pSearchButton = new QPushButton("Search");
    QObject::connect(pSearchButton, SIGNAL(clicked()), this, SLOT(onSearch()));
    hLayout.addWidget(pSearchButton);
    
    layout.addLayout(&hLayout);
    m_searchBrowser = new SearchBrowser(this);
    
    layout.addWidget(m_searchBrowser);
    centralWidget.setLayout(&layout);
    setCentralWidget(&centralWidget);
    resize(600, 500);
    
    QWidget *scr = QApplication::desktop()->screen(0);
    move(scr->width() - width() - 20, scr->height() / 2 - height() / 2);
    
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    setWindowTitle("Search browser");
}

void SearchWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    pSearchWindow = nullptr;
    delete m_searchBrowser;
    delete this;
}

Code *SearchWindow::getCodeByPos(int pos)
{
    for(BlockText * pBlockText : m_mapText) {
        if((pos >= pBlockText->begin) && (pos <= pBlockText->end)) {
            return pBlockText->pCode;
        }
    }

    return nullptr;
}

void SearchWindow::activate()
{
    activateWindow();
    m_lineQuery.setFocus();
}

void SearchWindow::onSearch()
{
    m_searchBrowser->setHtml(pCodeBase->searchSolidHTML(m_lineQuery.text(), this));
}