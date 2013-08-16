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

#include "searchbrowser.h"
#include <QtGui>
#include "searchwindow.h"
#include "code.h"
#include "codeeditorwindow.h"
#include "codebase.h"

extern CodeBase *pCodeBase;
extern SearchWindow *pSearchWindow;

SearchBrowser::SearchBrowser(SearchWindow *parent) :
    QTextBrowser(parent), pSearchEngine(parent)
{
    setStyleSheet("font: 10pt \"Courier\";");
    setMouseTracking(true);
    connect(this, SIGNAL(selectionChanged()), SLOT(onSelectionShanged()));
}

void SearchBrowser::editCodeSlot()
{
    if (m_selectedCode != nullptr) {
        CodeEditorWindow *pCodeEditor = new CodeEditorWindow(nullptr, m_selectedCode);
        pCodeEditor->move(pSearchWindow->x()-pCodeEditor->width()-20,pSearchWindow->y());
        pCodeEditor->show();
        pCodeEditor->activateWindow();
    }
}

void SearchBrowser::deleteCodeSlot()
{
    if (m_selectedCode != nullptr) {
        QString title = "Warning";
        QString question = "Would you like to delete this snippet?";
        QMessageBox msgBox(QMessageBox::Warning, title, question, QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            pCodeBase->deleteFromBase(m_selectedCode);
        }
    }
}

void SearchBrowser::showPropertiesSlot()
{
    if (m_selectedCode != nullptr) {
        QMessageBox msgBox;
        msgBox.setText(m_selectedCode->getProperties());
        msgBox.exec();
    }
}

void SearchBrowser::onCopySlot()
{
    copy();

    if (m_selectedCode != nullptr) {
        m_selectedCode->incCopyCounter();
    }
}

void SearchBrowser::onSelectionShanged()
{
    m_selectedCode = pSearchEngine->getCodeByPos(cursorPositionUnderMouse());
}

void SearchBrowser::contextMenuEvent(QContextMenuEvent *event)
{
    m_selectedCode = pSearchEngine->getCodeByPos(cursorPositionUnderMouse());
    QMenu menu;
    menu.addAction("Copy", this, SLOT(onCopySlot()), Qt::CTRL + Qt::Key_C);

    if (m_selectedCode != nullptr) {
        menu.addSeparator();
        menu.addAction("Edit code", this, SLOT(editCodeSlot()), Qt::CTRL + Qt::Key_E);
        menu.addAction("Delele code", this, SLOT(deleteCodeSlot()), Qt::CTRL + Qt::Key_D);
        menu.addSeparator();
        menu.addAction("Properties", this, SLOT(showPropertiesSlot()));
    }

    menu.exec(event->globalPos());
}

int SearchBrowser::cursorPositionUnderMouse()
{
    QPoint localCursorPos = mapFromGlobal(QCursor::pos());
    QTextCursor textCursorUnderMouse = cursorForPosition(localCursorPos);
    return textCursorUnderMouse.position();
}

void SearchBrowser::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if ((event->modifiers() & Qt::CTRL) && (key == Qt::Key_C)) {
        if (m_selectedCode != nullptr) {
            m_selectedCode->incCopyCounter();
        }
    }

    QTextBrowser::keyPressEvent(event);
}
