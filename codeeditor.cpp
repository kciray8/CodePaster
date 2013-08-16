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

#include "codeeditor.h"
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include "codeeditorwindow.h"

CodeEditor::CodeEditor(CodeEditorWindow *parent, bool autoPaste) :
    m_codeEditorWindow(parent)
{
    if(autoPaste) {
        paste();
        deleteCharInEachString(getMinLeftSpace());
        QTextCursor copyCursor = textCursor();
        copyCursor.setPosition(0);
        copyCursor.insertHtml("//<br>");
        copyCursor.setPosition(2);
        setTextCursor(copyCursor);
    }
}

void CodeEditor::deleteCharInEachString(int count)
{
    QString plainText = toPlainText();
    QTextCursor copyCursor = textCursor();
    int numStr = 0;
    bool beginStr = true;

    for(int i = 0; i < plainText.length(); i++) {
        if(beginStr) {
            if(plainText[i] == '\n'){
                continue;
            }
            plainText.remove(i, count);
            copyCursor.setPosition(i);
            
            for(int j = 0; j < count; j++)
                copyCursor.deleteChar();
            
            beginStr = false;
        }
        
        if (plainText[i] == '\n') {
            beginStr = true;
            numStr++;
        }
    }
}

int CodeEditor::getMinLeftSpace()
{
    QString plainText = toPlainText();
    bool beginStr = true;
    int numStr = 0;
    int minSpaceNum = 100;
    int tempSpaceNum = 0;
    
    for(int i = 0; i <= plainText.length(); i++) {
        if ((plainText[i] == '\n')&&(beginStr))
            continue;
        
        if (plainText[i] == ' ') {
            if(beginStr) {
                tempSpaceNum++;
                continue;
            }
        } else {
            beginStr = false;
        }

        if ((plainText[i] == '\n') || (i == plainText.length())) {
            numStr++;
            beginStr = true;

            if(tempSpaceNum < minSpaceNum) {
                minSpaceNum = tempSpaceNum;
            }

            tempSpaceNum = 0;
        }
    }

    return minSpaceNum;
}
