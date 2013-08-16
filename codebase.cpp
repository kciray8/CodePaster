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

#include "codebase.h"
#include "code.h"
#include "searchwindow.h"

struct BlockText;

CodeBase::CodeBase()
{
}

/**
 * @brief CodeBase::add
 * @param pNewCode
 * @param id if id = -1 or not set, code will be get new id and register in base
 */
void CodeBase::add(Code *pNewCode, int id)
{
    if(id == -1) {
        pNewCode->setId(m_base.size());
        m_base << pNewCode;
    } else {
        m_base.replace(id, pNewCode);
        pNewCode->setId(id);
    }
}

QString CodeBase::searchSolidHTML(QString queryStr, SearchWindow *pSearchEngine)
{
    QString res;
    QStringList queryList = queryStr.split(" ");
    bool firstElem = true;
    int length = 0;
    pSearchEngine->m_mapText.clear();

    for(Code * code : m_base) {
        bool allWordInCode = true;

        for(QString queryWord : queryList) {
            bool codeContainWord = code->getText()->contains(queryWord, Qt::CaseInsensitive);
            bool keywordsContainWord = code->getKeywords()->contains(queryWord, Qt::CaseInsensitive);
            bool someContainWord = codeContainWord | keywordsContainWord;

            if(!someContainWord) {
                allWordInCode = false;
                break;
            }
        }

        if(allWordInCode) {
            if(!firstElem) {
                QString splitter = "---------------";
                res += splitter;
                length += splitter.length();
                length += 2;
            }

            BlockText *pBlockText =  new BlockText();
            pBlockText->begin = length;
            pBlockText->end = length + code->getLenght();
            pBlockText->pCode = code;
            pSearchEngine->m_mapText << pBlockText;
            res += code->getHtml();
            length += code->getText()->length();
            firstElem = false;
        }
    }

    return res;
}

QDomDocument CodeBase::getXMLDoc()
{
    QDomDocument domDoc;
    QDomElement root = domDoc.createElement("codeBase");
    domDoc.appendChild(root);

    for(Code *code: m_base) {
        root.appendChild(code->getXML(&domDoc));
    }

    return domDoc;
}

void CodeBase::buildFromDoc(QDomDocument pDomDoc)
{
    QDomElement IronBrainXML = pDomDoc.documentElement();
    QDomNode node = IronBrainXML.firstChild();

    while (!node.isNull()) {
        QDomElement codeDomEl = node.toElement();
        Code *pCode = new Code();
        pCode->buildFromXML(codeDomEl);
        add(pCode);
        node = node.nextSibling();
    }
}

void CodeBase::deleteFromBase(Code *code)
{
    m_base.removeOne(code);
}
