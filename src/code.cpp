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

#include "code.h"
#include <QtWidgets>

Code::Code(QString html, QString keywords): m_html(html), m_keywords(keywords)
{
    setTextFromHTML(html);
}

Code::Code()
{
    m_id = -1;
    m_createTime = -1;
    m_copyCounter = 0;
}

void Code::setTextFromHTML(QString html)
{
    //convert html to plain text. Long way, but simple
    QTextBrowser doc;
    doc.setHtml(html);
    m_text = doc.toPlainText();
    
    m_lenght = m_text.length();
}

void Code::setCreateTime(qint64 createTime)
{
    m_createTime = createTime;
}

/**
 * @brief Code::getProperties - for use on msgBox - from context menu
 * @return
 */
QString Code::getProperties()
{
    QString str;
    str += "id = " + QString("%1").arg(m_id) + "\n";

    if(m_createTime != -1) {
        QDateTime dateTime;
        dateTime.setMSecsSinceEpoch(m_createTime);
        str += "createData = " + dateTime.toString() + "\n";
    }

    str += "keywords = " + m_keywords + "\n";
    str += "copyCounter = " + QString("%1").arg(m_copyCounter) + "\n";
    return str;
}

void Code::copyMembers(Code *code)
{
    m_createTime = code->m_createTime;
    m_copyCounter = code->m_copyCounter;
}

QDomElement Code::getXML(QDomDocument *domDoc)
{
    QDomElement domCode = domDoc->createElement("code");
    QDomText domTextData = domDoc->createTextNode(m_html);
    domCode.setAttribute("keywords", m_keywords);
    domCode.setAttribute("copyCounter", m_copyCounter);

    if(m_createTime != -1) {
        domCode.setAttribute("createTime", QString().number(m_createTime));
    }

    domCode.appendChild(domTextData);
    return domCode;
}

void Code::buildFromXML(QDomElement xml)
{
    m_keywords = xml.attribute("keywords");
    m_copyCounter = xml.attribute("copyCounter").toInt();
    m_html = xml.childNodes().at(0).toText().data();
    setTextFromHTML(m_html);

    if(xml.attribute("createTime") != "") {
        m_createTime = qint64(xml.attribute("createTime").toLongLong());
    } else {
        m_createTime = QDateTime::currentMSecsSinceEpoch();
    }
}
